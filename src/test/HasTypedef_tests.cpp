#include "catch.hpp"
#include "gubg/tmp/HasTypedef.hpp"
#include <string>
using namespace gubg::tmp;

struct S1 { typedef int Name; };
struct S2 { };

TEST_CASE("HasTypedef tests", "[ut][tmp]")
{
    REQUIRE((HasTypedef<S1>::Value));
    REQUIRE(!(HasTypedef<S2>::Value));
}
