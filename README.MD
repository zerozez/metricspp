# Metricspp Library
[![Build Status](https://travis-ci.org/zerozez/metricspp.svg?branch=master)](https://travis-ci.org/zerozez/metricspp)
[![Coverage Status](https://coveralls.io/repos/github/zerozez/metricspp/badge.svg?branch=master)](https://coveralls.io/github/zerozez/metricspp?branch=master)

Metricscpp is a c++ library for sending metrics data in a time series databases. It makes 
easier to collect data from inside of your applications about critical parts of the execution.

## Simple Usage
Create the metrics connector object using database's api url as the input parameter

```cpp
    auto metrics = metricspp::MetricsConnector("http://influx.example.com:8086/write?db=test");
```

and you are ready to go! Now you can send your data via this object:

```cpp
    std::queue<...> data_queue;
    ...

    metrics << "queue" << data_queue.size();
```

More examples you can find in [examples](examples) folder.

## Build steps
To simple build the library you need to run:

```bash
    cmake .
    make
```

Additionaly, if you want to build example applications, you can pass BUILD_EXAMPLE
option to cmake

## Requirements
* C++11
* CMake >= 3.1
* Curl

## License
Metricspp is distributed under the MIT License. See [LICENSE](LICENSE) file for details.
