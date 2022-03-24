# SYCL: memcpy(d to d)

## Build & Run

```sh
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

size  MB  memcpy(sub)  ms  memcpy(exe)  ms  memcpy(sub)  GB/s  kernel(sub)  ms  kerenel(exe)  ms  kerenel(sub)  GB/s
1     MB  0.971305  ms  0.04482   ms  21.7885  GB/s  0.156854  ms  0.044654  ms  21.8695  GB/s
2     MB  0.619945  ms  0.079182  ms  24.6663  GB/s  0.093691  ms  0.061918  ms  31.5437  GB/s
4     MB  1.25683   ms  0.152554  ms  25.6057  GB/s  0.156751  ms  0.12284   ms  31.7995  GB/s
8     MB  2.36453   ms  0.333162  ms  23.4496  GB/s  0.334329  ms  0.268256  ms  29.1233  GB/s
16    MB  4.92213   ms  0.763268  ms  20.4712  GB/s  0.887305  ms  0.798294  ms  19.573   GB/s
32    MB  9.51546   ms  1.51558   ms  20.6192  GB/s  1.74429   ms  1.66481   ms  18.7709  GB/s
64    MB  18.032    ms  3.19367   ms  19.5699  GB/s  3.60381   ms  3.49198   ms  17.8982  GB/s
128   MB  37.7931   ms  7.15095   ms  17.4802  GB/s  7.13208   ms  7.0296    ms  17.7819  GB/s
256   MB  73.5095   ms  13.7229   ms  18.2177  GB/s  14.0961   ms  13.9594   ms  17.909   GB/s
512   MB  147.409   ms  28.7092   ms  17.416   GB/s  27.5531   ms  27.3467   ms  18.2838  GB/s
1024  MB  289.175   ms  55.4838   ms  18.0233  GB/s  55.7034   ms  55.4017   ms  18.05    GB/s
2048  MB  583.512   ms  113.84    ms  17.5684  GB/s  111.616   ms  111.054   ms  18.0093  GB/s
4096  MB  1278.29   ms  226.082   ms  17.6927  GB/s  223.95    ms  222.971   ms  17.9395  GB/s
```

