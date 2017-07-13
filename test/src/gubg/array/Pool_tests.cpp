#include "catch.hpp"
#include "gubg/array/Pool.hpp"
using namespace gubg::array;

namespace  { 
    struct A
    {
        A(): id(next_id__++) {}
        ~A() {--next_id__;}
        int id;
        static int next_id__;
    };
    int A::next_id__ = 0;
} 

TEST_CASE("gubg::array::list::Element tests", "[ut][gubg][array]")
{
    S("");
    size_t nr = 3;
    auto el = list::Element::create<Array<A>>(nr);
    REQUIRE(A::next_id__ == nr);
    list::Element::destroy<Array<A>>(*el);
    REQUIRE(A::next_id__ == 0);
}
