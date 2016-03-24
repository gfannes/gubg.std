#include "catch.hpp"
#include "gubg/tmp/TypeList.hpp"
#include <string>

TEST_CASE("Typelist tests", "[ut][tmp]")
{
    REQUIRE(0 == gubg::tmp::TypeListSize<gubg::tmp::Null>::Value);
    typedef GUBG_TYPE_LIST(int, std::string) TL;
    REQUIRE(2 == gubg::tmp::TypeListSize<TL>::Value);
}
