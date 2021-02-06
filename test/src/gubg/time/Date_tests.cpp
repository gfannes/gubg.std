#include <gubg/time/Date.hpp>
#include <catch.hpp>
using namespace gubg;

TEST_CASE("gubg::time::Date API tests", "[ut][time][Date][API]")
{
    SECTION("default ctor")
    {
        time::Date date;
        REQUIRE(date.year == 0);
        REQUIRE(date.month == 0);
        REQUIRE(date.day == 0);
    }
    SECTION("from string")
    {
        time::Date date{"1-2-3"};
        REQUIRE(date.year == 1);
        REQUIRE(date.month == 2);
        REQUIRE(date.day == 3);
    }
}
TEST_CASE("gubg::time::Date parse tests", "[ut][time][Date][parse]")
{
    struct Scn
    {
        std::string str;
    };
    struct Exp
    {
        time::Date date;
    };

    Scn scn;
    Exp exp;

    SECTION("")
    {
        scn.str = "";
        exp.date.year = 0; exp.date.month = 0; exp.date.day = 0;
    }
    SECTION("1")
    {
        scn.str = "1";
        exp.date.year = 1; exp.date.month = 0; exp.date.day = 0;
    }

    time::Date date{scn.str};
    REQUIRE(date.year == exp.date.year);
    REQUIRE(date.month == exp.date.month);
    REQUIRE(date.day == exp.date.day);
}
