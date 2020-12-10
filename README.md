# sysfs_benchmark
A sysfs read write close benchmark

Open+Read+Close /sys/devices/system/cpu/cpu0/topology/core_id 1000 times and measure the time consumption.

## Usage

Compile it

```
$ make
```

Run it

```
$ ./bin_sysbm
```

Run with options

```
$ ./bin_sysbm [single|concurrent]
```

single mode - spawn only one thread  
concurent mode - spawn cpu cores number of threads and set up cpu affinity(bind each thread to a distinct cpu core).

## Output

```
single: total 9.951305ms per 9.951305us
concur: total 11.897490ms per 11.897490us  CPU 1
concur: total 12.016886ms per 12.016886us  CPU 0
times: 1000 threads: 2 cpus: 2
```

single - benchmark result printed by a thread running in single mode  
concurr - benchmark result printed by a thread running in concurr mode

total - total time spent on running open+read+close cycles on that thread  
per - time of each open+read+close cycle  
CPU - which cpu core the thread running on (only applicable to concurrent mode)

times: how many open+read+close cycles to run  
threads: how many threads spawned in concurrent mode  
cpus: the number of cpu cores on the machine  
