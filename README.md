# SYCL: Memcpy(Device2Device) Latency

## Build & Run

```sh
# Fix compiler flag
$ make
$ ./main
```

## Result

- CPU: 11th Gen Intel(R) Core(TM) i7-11700K @ 3.60GHz
- GPU: Intel(R) UHD Graphics 750
- Memory: Crucial Technology CT16G4DFRA32A.M16FR
  - Array Handle: 0x003B
  - Error Information Handle: Not Provided
  - Total Width: 64 bits
  - Data Width: 64 bits
  - Size: 16384 MB
  - Form Factor: DIMM
  - Set: None
  - Locator: Controller0-ChannelA-DIMM1
  - Bank Locator: BANK 0
  - Type: DDR4
  - Type Detail: Synchronous
  - Speed: 3200 MT/s
  - Manufacturer: Crucial Technology
  - Serial Number: *******
  - Asset Tag: *******
  - Part Number: CT16G4DFRA32A.M16FR
  - Rank: 2
  - Configured Memory Speed: 3200 MT/s
  - Minimum Voltage: 1.2 V
  - Maximum Voltage: 1.2 V
  - Configured Voltage: 1.2 V
  - Memory Technology: DRAM
  - Memory Operating Mode Capability: Volatile memory
  - Firmware Version: Not Specified
  - Module Manufacturer ID: Bank 6, Hex 0x9B
  - Module Product ID: Unknown
  - Memory Subsystem Controller Manufacturer ID: Unknown
  - Memory Subsystem Controller Product ID: Unknown
  - Non-Volatile Size: None
  - Volatile Size: 16 GB
  - Cache Size: None
  - Logical Size: None

```tsv
Running on device: Intel(R) UHD Graphics 750 [0x4c8a]

sub: submission time(elapsed time by chrono)
exe: execution time(sycl::event.command_end - sycl::event.command_start)

size  MB  memcpy(sub)  ms  memcpy(exe)  ms  memcpy(sub)  GB/s  kernel(sub)  ms  kerenel(exe)  ms  kerenel(sub)  GB/s
1     MB  0.809795     ms  0.040006     ms  24.4104      GB/s  0.130729     ms  0.044322      ms  22.0334       GB/s
2     MB  0.578274     ms  0.064408     ms  30.3243      GB/s  0.0913       ms  0.061752      ms  31.6285       GB/s
4     MB  1.27648      ms  0.131472     ms  29.7116      GB/s  0.12729      ms  0.092296      ms  42.3231       GB/s
8     MB  2.23178      ms  0.300958     ms  25.9588      GB/s  0.27348      ms  0.222772      ms  35.0695       GB/s
16    MB  4.47386      ms  0.686244     ms  22.7689      GB/s  1.04915      ms  0.887104      ms  17.6135       GB/s
32    MB  9.64813      ms  1.43424      ms  21.7885      GB/s  1.84347      ms  1.72408       ms  18.1257       GB/s
64    MB  18.9782      ms  3.23086      ms  19.3447      GB/s  3.55251      ms  3.404         ms  18.3608       GB/s
128   MB  36.5769      ms  6.68299      ms  18.7042      GB/s  6.95571      ms  6.76998       ms  18.4639       GB/s
256   MB  72.9654      ms  13.3278      ms  18.7578      GB/s  13.6568      ms  13.5129       ms  18.5008       GB/s
512   MB  145.823      ms  27.4664      ms  18.2041      GB/s  27.4479      ms  27.2429       ms  18.3534       GB/s

```

queue.memcpy(d_to_d) is very slow since JIT may be running(?).

Intel Integrated GPUの場合、CPUとDRAMをシェアするはずだからDtoDのコピーもC/C++のmemcpyを使ってもよいはず?
DtoDでmemcpyが遅くなるのはJITでKernelを起動しているから?(仕方ないが)
JITによるoverheadだとしてもサイズに比例するのはなんでなんだ?
