#include <gubg/ix/Range.hpp>

#include <catch.hpp>

#include <vector>
using namespace gubg;

TEST_CASE("Basic functionality tests", "[ut][ix][Range]")
{
    ix::Range range;

    SECTION("check defaults")
    {
        REQUIRE(range.start() == 0u);
        REQUIRE(range.stop() == 0u);
        REQUIRE(range.size() == 0u);
        REQUIRE(range.empty());
    }

    SECTION("ctor and ==")
    {
        ix::Range range1{1, 2};
        REQUIRE(range1.start() == 1);
        REQUIRE(range1.stop() == 1 + 2);

        REQUIRE(!(range == range1));
        REQUIRE(range != range1);

        range.init(1, 2);
        REQUIRE(range == range1);
        REQUIRE(!(range != range1));
        range.clear();
        range1.clear();
        REQUIRE(range == range1);
        REQUIRE(!(range != range1));
    }

    SECTION("setup() and clear()")
    {
        range.init(1, 2);
        REQUIRE(range.start() == 1);
        REQUIRE(range.stop() == 1 + 2);
        range.clear();
        REQUIRE(range.start() == 0);
        REQUIRE(range.stop() == 0);
    }

    SECTION("ix()")
    {
        range.init(1, 2);
        REQUIRE(range.ix(0) == 1);
        REQUIRE(range[0] == 1);
        REQUIRE(range.ix(1) == 2);
        REQUIRE(range[1] == 2);
    }

    SECTION("each*()")
    {
        const auto size = 10u;
        range.init(1u, size - 2);

        std::vector<unsigned int> vec0(size, 0u);
        for (auto ix = 0u; ix < size; ++ix)
            vec0[ix] = 10u * ix;

        std::vector<unsigned int> vec1(size, 0u);
        for (auto ix = 0u; ix < size; ++ix)
            vec1[ix] = ix;

        SECTION("each(vec0) from pointer")
        {
            unsigned int sum = 0u;
            range.each([&](auto v0) { sum += v0; }, vec0.data());
            REQUIRE(sum == 10 * (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8));
        }
        SECTION("each(vec0) from container")
        {
            unsigned int sum = 0u;
            range.each([&](auto v0) { sum += v0; }, vec0);
            REQUIRE(sum == 10 * (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8));
        }
        SECTION("each(vec0, vec1) from container")
        {
            unsigned int sum = 0u;
            range.each([&](auto v0, auto v1) { sum += v0 + v1; }, vec0, vec1);
            REQUIRE(sum == (10 + 1) * (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8));
        }
        SECTION("each_index(vec0) from pointer")
        {
            unsigned int sum = 0u;
            range.each_index([&](auto ix) { sum += 10u * ix; });
            REQUIRE(sum == 10 * (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8));
        }
        SECTION("each_offset(vec0) from pointer")
        {
            unsigned int sum = 0u;
            range.each_offset([&](auto ix0) { sum += 10u * ix0; });
            REQUIRE(sum == 10 * (0 + 1 + 2 + 3 + 4 + 5 + 6 + 7));
        }
        SECTION("each_with_offset(vec0) from pointer")
        {
            unsigned int sum = 0u;
            range.each_with_offset([&](auto v0, auto ix0) {REQUIRE(v0 == 10u*(ix0+range.start())); sum += v0; }, vec0.data());
            REQUIRE(sum == 10 * (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8));
        }
    }

    SECTION("for()")
    {
        range = ix::make_range(3);
        using Vec = std::vector<std::size_t>;
        Vec vec;
        SECTION("normal")
        {
            for (auto ix : range)
                vec.push_back(ix);
            REQUIRE(vec == Vec({0, 1, 2}));
        }

        SECTION("reverse()")
        {
            for (auto ix : range.reverse())
                vec.push_back(ix);
            REQUIRE(vec == Vec({2, 1, 0}));
        }
    }

    SECTION("contains()")
    {
        range = ix::Range(2, 3);
        REQUIRE(!range.contains(0));
        REQUIRE(!range.contains(1));
        REQUIRE(range.contains(2));
        REQUIRE(range.contains(3));
        REQUIRE(range.contains(4));
        REQUIRE(!range.contains(5));
    }
}
