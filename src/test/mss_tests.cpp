#include "catch.hpp"
#include "gubg/mss.hpp"
#include <string>
using namespace std;

bool one(bool b)
{
    MSS_BEGIN(bool);
    MSS(b);
    MSS_END();
}
bool two(bool b, string &msg)
{
    MSS_BEGIN(bool);
    MSS(b, msg="fail");
    msg="ok";
    MSS_END();
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
