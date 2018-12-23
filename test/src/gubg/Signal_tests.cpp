#include "catch.hpp"
#include "gubg/Signal.hpp"

namespace  { 
    struct A
    {
        std::optional<int> data;
        void process(int v) {data = v;}
    };
} 

TEST_CASE("Signal tests", "[ut][Signal]")
{
    gubg::Signal<int> signal;

    std::optional<int> data;
    A a;

    signal.connect([&](int v){data = v;});
    signal.connect(a, &A::process);

    signal.emit(42);
    REQUIRE(!!data);
    REQUIRE(*data == 42);
    REQUIRE(!!a.data);
    REQUIRE(*a.data == 42);
}
