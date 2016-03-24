#include "catch.hpp"
#include "gubg/tmp/Inheritance.hpp"
#include <string>
using namespace gubg::tmp;

struct Base1 {};
struct Base2 {};
struct Derived1: Base1 {};
struct Derived2: Base2 {};
struct Derived12: Base1, Base2 {};
struct Derived_1: Derived1 {};
struct Unrelated {};

TEST_CASE("Inheritance tests", "[ut][tmp]")
{
    REQUIRE((Inheritance<Derived1, Base1>::Value));
    REQUIRE(!(Inheritance<Base1, Derived1>::Value));
    REQUIRE((Inheritance<Derived12, Base1>::Value));
    REQUIRE(!(Inheritance<Base1, Derived12>::Value));
    REQUIRE((Inheritance<Derived12, Base2>::Value));
    REQUIRE(!(Inheritance<Base2, Derived12>::Value));
    REQUIRE((Inheritance<Derived_1, Base1>::Value));
    REQUIRE(!(Inheritance<Base1, Derived_1>::Value));
    REQUIRE(!(Inheritance<Unrelated, Base1>::Value));
    REQUIRE((Inheritance<Base1, Base1>::Value));
    REQUIRE((Inheritance<Derived_1, Derived_1>::Value));
}
