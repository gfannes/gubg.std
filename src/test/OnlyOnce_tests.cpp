#include "catch.hpp"
#include "gubg/OnlyOnce.hpp"

TEST_CASE("OnlyOnce tests", "[ut]")
{
    gubg::OnlyOnce oo;

    REQUIRE(oo.check());
    REQUIRE(oo.check());
    REQUIRE(oo());
    REQUIRE(!oo());
    REQUIRE(!oo());
    REQUIRE(!oo.check());
    REQUIRE(!oo.check());

    oo.reset();

    REQUIRE(oo.check());
    REQUIRE(oo.check());
    REQUIRE(oo());
    REQUIRE(!oo());
    REQUIRE(!oo());
    REQUIRE(!oo.check());
    REQUIRE(!oo.check());
}
