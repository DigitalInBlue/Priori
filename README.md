#Priori

##C++ Fast dynamic_cast<> Alternative

Copyright 2013 John Farrier 
Apache 2.0 License

##Overview

Priori uses CMake to provide cross-platform builds. It does require a modern 
compiler (Visual C++ 2012 or GCC 4.7+) due to its use of C++11.

Priori is a special base class which facilitates a very fast dynamic_cast<>
alternative when dynamic_cast<> itself has shown to be a bottleneck. Specifically 
in the case where dynamic_cast<> from a base class to a derived class is impacting
performance.

## Benchmark 

Given ten levels of inheritance and benchmarked using Celero...

Base Class to Derived Class
- dynamic_cast 0.374372 us/call (1.0 Baseline Multiple)
- priori_cast 0.116727 us/call (0.311794 Baseline Multiple)

Derived Class to Base Class
- dynamic_cast 0.014044 us/call (1.0 Baseline Multiple)
- priori_cast 0.014007 us/call (0.997365 Baseline Multiple)

Cast to Self
- dynamic_cast 0.014930 us/call (1.0 Baseline Multiple)
- priori_cast 0.013988  us/call (0.999536 Baseline Multiple)

Complete Results:
<pre>
[==========] 
[  CELERO  ]
[==========] 
[ STAGE    ] Baselining
[==========] 
[ RUN      ] priori_deep_fromBase.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_fromBase.dynamic_cast  (0.748744 sec) [2000000 calls in 748744 usec] [0.374372 us/call] [2671139.935679 calls/sec]
[ RUN      ] priori_wide_fromBase.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_fromBase.dynamic_cast  (0.748687 sec) [2000000 calls in 748687 usec] [0.374344 us/call] [2671343.298334 calls/sec]
[ RUN      ] priori_deep_toBase.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_toBase.dynamic_cast  (0.028087 sec) [2000000 calls in 28087 usec] [0.014044 us/call] [71207320.112508 calls/sec]
[ RUN      ] priori_wide_toBase.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_toBase.dynamic_cast  (0.027999 sec) [2000000 calls in 27999 usec] [0.014000 us/call] [71431122.540091 calls/sec]
[ RUN      ] priori_deep_toSelf.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_toSelf.dynamic_cast  (0.029860 sec) [2000000 calls in 29860 usec] [0.014930 us/call] [66979236.436705 calls/sec]
[ RUN      ] priori_wide_toSelf.dynamic_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_toSelf.dynamic_cast  (0.027990 sec) [2000000 calls in 27990 usec] [0.013995 us/call] [71454090.746695 calls/sec]
[ RUN      ] rttiCosts.typeinfo -- 70 samples, 2000000 calls per run.
[     DONE ] rttiCosts.typeinfo  (0.027991 sec) [2000000 calls in 27991 usec] [0.013995 us/call] [71451537.994355 calls/sec]
[==========] 
[ STAGE    ] Benchmarking
[==========] 
[ RUN      ] priori_deep_fromBase.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_fromBase.priori_cast  (0.233454 sec) [2000000 calls in 233454 usec] [0.116727 us/call] [8566998.209497 calls/sec]
[ BASELINE ] priori_deep_fromBase.priori_cast 0.311794
[ RUN      ] priori_wide_fromBase.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_fromBase.priori_cast  (0.286413 sec) [2000000 calls in 286413 usec] [0.143206 us/call] [6982923.261165 calls/sec]
[ BASELINE ] priori_wide_fromBase.priori_cast 0.382554
[ RUN      ] priori_deep_toBase.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_toBase.priori_cast  (0.028013 sec) [2000000 calls in 28013 usec] [0.014007 us/call] [71395423.553350 calls/sec]
[ BASELINE ] priori_deep_toBase.priori_cast 0.997365
[ RUN      ] priori_wide_toBase.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_toBase.priori_cast  (0.028008 sec) [2000000 calls in 28008 usec] [0.014004 us/call] [71408169.094544 calls/sec]
[ BASELINE ] priori_wide_toBase.priori_cast 1.000321
[ RUN      ] priori_deep_toSelf.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_deep_toSelf.priori_cast  (0.028051 sec) [2000000 calls in 28051 usec] [0.014026 us/call] [71298705.928487 calls/sec]
[ BASELINE ] priori_deep_toSelf.priori_cast 0.939417
[ RUN      ] priori_wide_toSelf.priori_cast -- 70 samples, 2000000 calls per run.
[     DONE ] priori_wide_toSelf.priori_cast  (0.027977 sec) [2000000 calls in 27977 usec] [0.013988 us/call] [71487293.133646 calls/sec]
[ BASELINE ] priori_wide_toSelf.priori_cast 0.999536
[ RUN      ] rttiCosts.typeinfoHash -- 70 samples, 2000000 calls per run.
[     DONE ] rttiCosts.typeinfoHash  (0.319687 sec) [2000000 calls in 319687 usec] [0.159844 us/call] [6256119.266658 calls/sec]
[ BASELINE ] rttiCosts.typeinfoHash 11.421064
[ RUN      ] rttiCosts.typeinfoName -- 70 samples, 2000000 calls per run.
[     DONE ] rttiCosts.typeinfoName  (0.054207 sec) [2000000 calls in 54207 usec] [0.027103 us/call] [36895603.888797 calls/sec]
[ BASELINE ] rttiCosts.typeinfoName 1.936587
[==========] 
[ STAGE    ] Completed.  15 tests complete.
[==========] 
</pre>

![Image](https://d2weczhvl823v0.cloudfront.net/DigitalInBlue/Priori/trend.png?raw=true)
