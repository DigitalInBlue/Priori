# Priori

## C++ Fast dynamic_cast<> Alternative

Copyright 2013-2021 John Farrier
Apache 2.0 License

## Overview

Priori is a special base class which facilitates a very fast `dynamic_cast<>` alternative when `dynamic_cast<>` itself has shown to be a bottleneck. Specifically in the case where `dynamic_cast<>` from a base class to a derived class is impacting performance.

Priori is interesting, but not a wholesale replacement for `dynamic_cast`.  There are very specific use cases when Priori should be considered to relieve a quantified bottle-neck.  Benchmarking shows that the following scenarios show measurable improvements for non-threaded applications.  Review the benchmark tables below to see if there is a measurable performance improvement for your specific use case.  (There are several use cases which are slower than `dynamic_cast`, so consider this a highly-specialized micro-optimization.)

Priori uses [CMake](https://github.com/Kitware/CMake) to provide cross-platform builds. It does require a modern compiler due to its use of C++11.

## Benchmark

Given 10 levels of inheritance and benchmarked using [Celero](https://github.com/DigitalInBlue/Celero).

For the non-thread-safe implementation:

```
Celero
Timer resolution: 0.100000 us
|     Group      |   Experiment    |   Prob. Space   |     Samples     |   Iterations    |    Baseline     |  us/Iteration   | Iterations/sec  |
|:--------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|
|priori_deep_fro | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.01781 |     56143502.79 |
|priori_wide_fro | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.01614 |     61973227.57 |
|priori_deep_toB | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00464 |    215331610.68 |
|priori_wide_toB | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00458 |    218150087.26 |
|priori_deep_toS | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00498 |    200702458.61 |
|priori_wide_toS | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00492 |    203417412.53 |
|rttiCosts       | typeinfo        |            Null |             128 |         2000000 |         1.00000 |         0.00459 |    217983651.23 |
|priori_deep_fro | priori_cast     |            Null |             128 |         2000000 |         0.78115 |         0.01391 |     71872641.68 |
|priori_wide_fro | priori_cast     |            Null |             128 |         2000000 |         1.05311 |         0.01699 |     58847760.84 |
|priori_deep_toB | priori_cast     |            Null |             128 |         2000000 |         0.97782 |         0.00454 |    220215811.50 |
|priori_wide_toB | priori_cast     |            Null |             128 |         2000000 |         0.99247 |         0.00455 |    219804374.11 |
|priori_deep_toS | priori_cast     |            Null |             128 |         2000000 |         0.91159 |         0.00454 |    220167327.17 |
|priori_wide_toS | priori_cast     |            Null |             128 |         2000000 |         0.88314 |         0.00434 |    230335137.63 |
|rttiCosts       | typeinfoHash    |            Null |             128 |         2000000 |         2.48262 |         0.01139 |     87804021.42 |
|rttiCosts       | typeinfoName    |            Null |             128 |         2000000 |         1.39401 |         0.00639 |    156372165.75 |
```

For the thread-safe implementation:

```
Celero
Timer resolution: 0.100000 us
|     Group      |   Experiment    |   Prob. Space   |     Samples     |   Iterations    |    Baseline     |  us/Iteration   | Iterations/sec  |
|:--------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|
|priori_deep_fro | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.01781 |     56154537.29 |
|priori_wide_fro | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.01612 |     62034739.45 |
|priori_deep_toB | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00455 |    219973603.17 |
|priori_wide_toB | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00457 |    219034059.80 |
|priori_deep_toS | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00503 |    198925800.68 |
|priori_wide_toS | dynamic_cast    |            Null |             128 |         2000000 |         1.00000 |         0.00488 |    204918032.79 |
|rttiCosts       | typeinfo        |            Null |             128 |         2000000 |         1.00000 |         0.00454 |    220312844.24 |
|priori_deep_fro | priori_cast     |            Null |             128 |         2000000 |         1.46114 |         0.02602 |     38431975.40 |
|priori_wide_fro | priori_cast     |            Null |             128 |         2000000 |         1.94498 |         0.03135 |     31894874.49 |
|priori_deep_toB | priori_cast     |            Null |             128 |         2000000 |         0.99890 |         0.00454 |    220215811.50 |
|priori_wide_toB | priori_cast     |            Null |             128 |         2000000 |         0.99660 |         0.00455 |    219780219.78 |
|priori_deep_toS | priori_cast     |            Null |             128 |         2000000 |         0.90302 |         0.00454 |    220288578.04 |
|priori_wide_toS | priori_cast     |            Null |             128 |         2000000 |         0.88648 |         0.00433 |    231160425.34 |
|rttiCosts       | typeinfoHash    |            Null |             128 |         2000000 |         2.49251 |         0.01131 |     88389976.58 |
|rttiCosts       | typeinfoName    |            Null |             128 |         2000000 |         1.41683 |         0.00643 |    155496812.32 |
```


![Image](https://d2weczhvl823v0.cloudfront.net/DigitalInBlue/Priori/trend.png?raw=true)
