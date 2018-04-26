#include "catch.hpp"
#include "gubg/tuple/TypeTransform.hpp"
#include <type_traits>
#include <vector>

namespace  { 
    template <typename T, size_t IX>
        struct Transform
        {
            typedef std::vector<T> Type;
        };
} 

TEST_CASE("TypeTransform", "[tuple]")
{
    SECTION("No parameters")
    {
        typedef std::tuple<> Tuple;
        typedef gubg::tuple::TypeTransform<Tuple, Transform>::Type TransTuple;
        REQUIRE((std::is_same<std::tuple<>, TransTuple>::value));
    }
    SECTION("One parameter")
    {
        typedef std::tuple<int> Tuple;
        typedef gubg::tuple::TypeTransform<Tuple, Transform>::Type TransTuple;
        REQUIRE((std::is_same<std::tuple<std::vector<int>>, TransTuple>::value));
    }
    SECTION("Two parameters")
    {
        typedef std::tuple<int, double> Tuple;
        typedef gubg::tuple::TypeTransform<Tuple, Transform>::Type TransTuple;
        REQUIRE((std::is_same<std::tuple<std::vector<int>, std::vector<double>>, TransTuple>::value));
    }
}
