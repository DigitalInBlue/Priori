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
performance, priori_cast<> costs 85% less than dynamic_cast<>.  When 
casting from a derived type to a base class, priori_cast<> costs about 4x more than
dynamic_cast, so the performance benefit should be weighed prior to utilization.

(Given the later case of casting from a derived type to a base type, I would suggest
using static_cast<> anyway.)

![Image](https://d2weczhvl823v0.cloudfront.net/DigitalInBlue/Priori/trend.png?raw=true)
