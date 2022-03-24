#include <CL/sycl.hpp>
#include <cstddef>
#include <iomanip>
#include <iostream>

using namespace cl::sycl;
using namespace std;

using ITEM_T = int;
constexpr int NUM_THREADS_PER_GROUP = 64;

class Event {
public:
  event memcpy_event;
  double memcpy_elapsed_ms;
  event kernel_event;
  double kernel_elapesed_ms;
};

double get_submission_ms(event e) {
  auto end = e.get_profiling_info<sycl::info::event_profiling::command_end>();
  auto start =
      e.get_profiling_info<sycl::info::event_profiling::command_start>();
  return (end - start) / 1.0e6;
};

double elaspsed_ms(std::chrono::steady_clock::time_point &start,
                   std::chrono::steady_clock::time_point &end) {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
             .count() /
         1e6;
};

template <typename T> Event run_kernel(queue &q, size_t num_items) {
  assert(num_items % NUM_THREADS_PER_GROUP == 0);
  T *DEVICE_READ = static_cast<T *>(malloc_device(num_items * sizeof(T), q));
  T *DEVICE_WRITE = static_cast<T *>(malloc_device(num_items * sizeof(T), q));

  auto memcpy_start = std::chrono::steady_clock::now();
  event memcpy_event =
      q.memcpy(DEVICE_WRITE, DEVICE_READ, sizeof(T) * num_items);
  memcpy_event.wait();
  auto memcpy_end = std::chrono::steady_clock::now();
  auto memcpy_elapsed_ms = elaspsed_ms(memcpy_start, memcpy_end);

  auto kernel_start = std::chrono::steady_clock::now();
  event kernel_event = q.submit([&](handler &cgh) {
    auto localRange = range<1>(NUM_THREADS_PER_GROUP);
    auto kernel = [=](nd_item<1> it) {
      auto localX = it.get_local_id(0);
      auto globalX = it.get_global_id(0);
      T x = globalX;
      x = DEVICE_READ[globalX];
      DEVICE_WRITE[globalX] = x;
    };
    cgh.parallel_for<class pm>(nd_range<1>{range<1>(num_items), localRange},
                               kernel);
  });
  kernel_event.wait();
  auto kernel_end = std::chrono::steady_clock::now();
  auto kernel_elapsed_ms = elaspsed_ms(kernel_start, kernel_end);
  free(DEVICE_READ, q);
  free(DEVICE_WRITE, q);

  return Event{
      .memcpy_event = memcpy_event,
      .memcpy_elapsed_ms = memcpy_elapsed_ms,
      .kernel_event = kernel_event,
      .kernel_elapesed_ms = kernel_elapsed_ms,
  };
}

void copy(queue &q, size_t bytes) {
  size_t mbytes = bytes / 1024 / 1024;
  size_t num_items = bytes / sizeof(ITEM_T);
  auto result = run_kernel<ITEM_T>(q, num_items);
  cout << mbytes << ",MB,"
       << result.memcpy_elapsed_ms << ",ms,"
       << get_submission_ms(result.memcpy_event) << ",ms,"
       << mbytes / get_submission_ms(result.memcpy_event) * 1e3 / 1024 << ",GB/s,"

       << result.kernel_elapesed_ms << ",ms,"
       << get_submission_ms(result.kernel_event) << ",ms,"
       << mbytes / get_submission_ms(result.kernel_event) * 1e3 / 1024 << ",GB/s,"
       << "\n";
}

int main(int argc, char *argv[]) {

  gpu_selector d_selector;
  queue q(d_selector);
  cout << "device to device memory copy latency" << "\n";
  cout << "Running on device: " << q.get_device().get_info<info::device::name>()
       << "\n";

  cout << "size" << ",MB,"
       << "memcpy(sub)" << ",ms,"
       << "memcpy(exe)" << ",ms,"
       << "memcpy(sub)" << ",GB/s,"
       << "kernel(sub)" << ",ms,"
       << "kerenel(exe)" << ",ms,"
       << "kerenel(sub)" << ",GB/s,"
       << "\n";
  for(size_t mb = 1 ; mb <= 4096; mb = mb << 1 ){
    copy(q, mb * 1024 * 1024);
  }
  return 0;
}
