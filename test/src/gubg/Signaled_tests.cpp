#include <gubg/Signaled.hpp>

#include <catch.hpp>

TEST_CASE("Signaled tests", "[ut][gubg][Signaled]")
{
    gubg::Signaled<int> int_sig;
    REQUIRE(!int_sig);
    REQUIRE(int_sig.cref() == 0);

    int_sig.set(true);
    REQUIRE(!!int_sig);
    REQUIRE(int_sig.cref() == 0);

    int_sig.ref() = 42;
    REQUIRE(!!int_sig);
    REQUIRE(int_sig.cref() == 42);
}
