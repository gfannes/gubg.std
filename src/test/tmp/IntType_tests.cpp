#include "catch.hpp"
#include "gubg/tmp/IntType.hpp"

TEST_CASE("IntType", "[ut][tmp]")
{
    typedef gubg::tmp::IntType<42> T;
    REQUIRE(T::value == 42);
}
