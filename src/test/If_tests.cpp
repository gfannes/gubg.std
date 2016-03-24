#include "catch.hpp"
#include "gubg/tmp/If.hpp"
#include <string>
using namespace gubg::tmp;

struct One {enum: int {Value = 1};};
struct Two {enum: int {Value = 2};};

TEST_CASE("If tests", "[ut][tmp]")
{
    REQUIRE(1 == (If<true, One, Two>::Type::Value));
    REQUIRE(2 == (If<false, One, Two>::Type::Value));
}
