#include "catch.hpp"
#include "gubg/mss.hpp"
#include <string>
using namespace std;

namespace  { 
    enum class RC
    {
        OK, Error,
    };

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
    bool three(bool b, string &msg)
    {
        MSS_BEGIN(bool);
        //Custom aggregator inverses the meaning of b
        MSS(b, msg="fail", [](bool &rc, bool b){rc = !b;});
        msg="ok";
        MSS_END();
    }
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

    SECTION("three")
    {
        //Custom aggregator inverses the meaning of b
        string msg;
        REQUIRE(three(false,msg));
        REQUIRE(msg=="ok");
        REQUIRE(!three(true,msg));
        REQUIRE(msg=="fail");
    }

    SECTION("AGG")
    {
        bool action_executed = false;
        bool should_action_executed = false;
        auto action = [&](){action_executed = true;};

        SECTION("on bool")
        {
            bool ok = true;
            auto check = [&](){return ok;};

            AGG(ok, true);
            REQUIRE(check());
            AGG(ok, true);
            REQUIRE(check());
            AGG(ok, true, action());
            REQUIRE(check());
            AGG(ok, RC::OK);
            REQUIRE(check());
            SECTION("without expr should fail")
            {
                ok = false;
                /* AGG(ok); */
            }
            SECTION("fail on bool")
            {
                AGG(ok, false);
                REQUIRE(!check());
            }
            SECTION("fail on RC")
            {
                AGG(ok, RC::Error);
                REQUIRE(!check());
            }
            SECTION("fail with action")
            {
                AGG(ok, false, action());
                should_action_executed = true;
                REQUIRE(!check());
            }
            AGG(ok, true);
            REQUIRE(!check());
            AGG(ok, RC::OK);
            REQUIRE(!check());
        }
        SECTION("on RC")
        {
            RC rc = RC::OK;
            auto check = [&](){return rc == RC::OK;};

            AGG(rc, true);
            REQUIRE(check());
            AGG(rc, true);
            REQUIRE(check());
            AGG(rc, true, action());
            REQUIRE(check());
            AGG(rc, RC::OK);
            REQUIRE(check());
            SECTION("fail on bool")
            {
                AGG(rc, false);
                REQUIRE(!check());
            }
            SECTION("fail on RC")
            {
                AGG(rc, RC::Error);
                REQUIRE(!check());
            }
            SECTION("fail with action")
            {
                AGG(rc, false, action());
                should_action_executed = true;
                REQUIRE(!check());
            }
            AGG(rc, true);
            REQUIRE(!check());
            AGG(rc, RC::OK);
            REQUIRE(!check());
        }

        REQUIRE(should_action_executed == action_executed);
    }
}
