#include <gubg/Signaled.hpp>

#include <catch.hpp>

TEST_CASE("Signaled tests", "[ut][gubg][Signaled]")
{
    SECTION("bool flag")
    {
        SECTION("default")
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
        SECTION("true")
        {
            gubg::Signaled<int, bool, true> int_sig;
            REQUIRE(!!int_sig);
        }
    }
    SECTION("int flag")
    {
        SECTION("0")
        {
            gubg::Signaled<int, int, 0> int_sig;
            REQUIRE(int_sig.flag() == 0);
            REQUIRE(int_sig == 0);
        }

        SECTION("42")
        {
            gubg::Signaled<int, int, 42> int_sig;
            REQUIRE(int_sig.flag() == 42);
            REQUIRE(int_sig == 42);
        }
    }
}
