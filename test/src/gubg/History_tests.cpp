#include <gubg/History.hpp>
#include <catch.hpp>

TEST_CASE("History tests", "[ut][History]")
{
    gubg::History<int> h;
    REQUIRE(h.empty());
    REQUIRE(h.size() == 0);
    h.resize(3);
    REQUIRE(h[0] == 0);
    REQUIRE(h[1] == 0);
    REQUIRE(h[2] == 0);
    h.set(0, 10);
    h.set(1, 11);
    h.set(2, 12);
    REQUIRE(h[0] == 10);
    REQUIRE(h[1] == 11);
    REQUIRE(h[2] == 12);
    h.push(9);
    REQUIRE(h[0] == 9);
    REQUIRE(h[1] == 10);
    REQUIRE(h[2] == 11);
    h.push(8);
    REQUIRE(h[0] == 8);
    REQUIRE(h[1] == 9);
    REQUIRE(h[2] == 10);
    h.push(7);
    REQUIRE(h[0] == 7);
    REQUIRE(h[1] == 8);
    REQUIRE(h[2] == 9);
    h.push(6);
    REQUIRE(h[0] == 6);
    REQUIRE(h[1] == 7);
    REQUIRE(h[2] == 8);
    h.resize(4);
    REQUIRE(h[0] == 6);
    REQUIRE(h[1] == 7);
    REQUIRE(h[2] == 8);
    REQUIRE(h[3] == 0);
    h.push(5);
    REQUIRE(h[0] == 5);
    REQUIRE(h[1] == 6);
    REQUIRE(h[2] == 7);
    REQUIRE(h[3] == 8);
}
