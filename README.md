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
1     MB  0.829011     ms  0.040338     ms  24.2095      GB/s  0.11962      ms  0.033034      ms  29.5623       GB/s
2     MB  0.583678     ms  0.062748     ms  31.1265      GB/s  0.101806     ms  0.070716      ms  27.6193       GB/s
4     MB  1.19333      ms  0.160024     ms  24.4104      GB/s  0.137361     ms  0.10209       ms  38.2628       GB/s
8     MB  2.21423      ms  0.30793      ms  25.371       GB/s  0.265103     ms  0.21912       ms  35.654        GB/s
16    MB  4.72037      ms  0.70384      ms  22.1996      GB/s  0.924081     ms  0.837304      ms  18.6611       GB/s
32    MB  9.43056      ms  1.47325      ms  21.2116      GB/s  2.15085      ms  2.06006       ms  15.1695       GB/s
64    MB  19.4352      ms  3.27535      ms  19.082       GB/s  3.57155      ms  3.47139       ms  18.0043       GB/s
128   MB  39.642       ms  6.89332      ms  18.1335      GB/s  7.22887      ms  7.11161       ms  17.5769       GB/s
256   MB  76.1264      ms  14.0592      ms  17.7819      GB/s  13.9         ms  13.7433       ms  18.1907       GB/s
512   MB  149.831      ms  28.208       ms  17.7254      GB/s  28.4484      ms  28.2457       ms  17.7018       GB/s
1024  MB  297.392      ms  55.9339      ms  17.8783      GB/s  55.1564      ms  54.8527       ms  18.2306       GB/s
2048  MB  591.187      ms  110.26       ms  18.139       GB/s  111.164      ms  110.641       ms  18.0765       GB/s
4096  MB  1142.15      ms  219.21       ms  18.2474      GB/s  219.74       ms  218.773       ms  18.2838       GB/s
```

queue.memcpy(d_to_d) is very slow since JIT may be running(?).

Intel Integrated GPUの場合、CPUとDRAMをシェアするはずだからDtoDのコピーもC/C++のmemcpyを使ってもよいはず?

DtoDでmemcpyが遅くなるのはJITでKernelを起動しているから?(仕方ないが)

JITによるoverheadだとしてもサイズに比例するのはなんでなんだ?
