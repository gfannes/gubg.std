#include "catch.hpp"
#include "gubg/mss.hpp"
#include <string>
using namespace std;

bool one(bool b)
{
    MSS(b);
    return true;
}
bool two(bool b, string &msg)
{
    MSS(b, msg="fail");
    msg="ok";
    return true;
}

TEST_CASE("MSS tests", "[ut][mss]")
{
    SECTION("one")
    {
        REQUIRE(one(true));
        REQUIRE(!one(false));
    }

    SECTION("two")
    {
        string msg;
        REQUIRE(two(true,msg));
        REQUIRE(msg=="ok");
        REQUIRE(!two(false,msg));
        REQUIRE(msg=="fail");
    }
}
