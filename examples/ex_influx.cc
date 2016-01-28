#include <chrono>
#include <thread>
#include <memory>

#include <counter.hpp>
#include <timestamp-c++.hpp>


using namespace timestamp;


int main (int argc, char** argv)
{
    auto factory = CFactory::create();

    factory->setupConnection("127.0.0.1", 4444, "influx.udp");
    auto counter = factory->counter<int>("counter1",
                                {
                                    {"host", "localhost"},
                                    {"region", "Imaginaryland"},
                                    {"cpu", "test-cpu"}
                                },
                                "test");


    for(int i = 0; i < 10000L; i++)
    {
        // time operation whatever
        std::this_thread::sleep_for(std::chrono::milliseconds(i % 4));
        counter->value(i);
    }

    return 0;
}
