#include "catch.hpp"
#include "gubg/Transition.hpp"
using namespace gubg;

TEST_CASE("Transition tests", "[ut]")
{
    Transition<int> trans;

    SECTION("fresh should be initialized")
    {
        REQUIRE(0 == trans.previous());
        REQUIRE(0 == trans.current());
        REQUIRE(!trans.changed());
    }

    SECTION("push with default argument")
    {
        trans.push();
        REQUIRE(0 == trans.current());
    }

    SECTION("push with nondefault argument")
    {
        trans.push(42);
        REQUIRE(42 == trans.current());
        trans.push();
        REQUIRE(42 == trans.previous());
        REQUIRE(0 == trans.current());
    }
}
