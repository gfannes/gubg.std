#include <gubg/ix/Range.hpp>
#include <catch.hpp>
#include <vector>
using namespace gubg;

TEST_CASE("Basic functionality tests", "[ut][ix][Range]")
{
	ix::Range range;

	SECTION("check defaults")
	{
		REQUIRE(range.begin() == 0u);
		REQUIRE(range.end() == 0u);
		REQUIRE(range.size() == 0u);
		REQUIRE(range.empty());
	}

	SECTION("ctor and ==")
	{
		ix::Range range1{1, 2};
		REQUIRE(range1.begin() == 1);
		REQUIRE(range1.end() == 1+2);

		REQUIRE(!(range == range1));
		REQUIRE(range != range1);

		range.setup(1, 2);
		REQUIRE(range == range1);
		REQUIRE(!(range != range1));
		range.clear();
		range1.clear();
		REQUIRE(range == range1);
		REQUIRE(!(range != range1));
	}

	SECTION("setup() and clear()")
	{
		range.setup(1,2);
		REQUIRE(range.begin() == 1);
		REQUIRE(range.end() == 1+2);
		range.clear();
		REQUIRE(range.begin() == 0);
		REQUIRE(range.end() == 0);
	}

	SECTION("ix()")
	{
		range.setup(1,2);
		REQUIRE(range.ix(0) == 1);
		REQUIRE(range[0] == 1);
		REQUIRE(range.ix(1) == 2);
		REQUIRE(range[1] == 2);
	}

	SECTION("each*()")
	{
		const auto size = 10u;
		range.setup(1u, size-2);

		std::vector<unsigned int> vec0(size, 0u);
		for (auto ix = 0u; ix < size; ++ix)
			vec0[ix] = 10u*ix;

		std::vector<unsigned int> vec1(size, 0u);
		for (auto ix = 0u; ix < size; ++ix)
			vec1[ix] = ix;

		SECTION("each(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each([&](auto v0){sum += v0;}, vec0.data());
			REQUIRE(sum == 10*(1+2+3+4+5+6+7+8));
		}
		SECTION("each(vec0) from container")
		{
			unsigned int sum = 0u;
			range.each([&](auto v0){sum += v0;}, vec0);
			REQUIRE(sum == 10*(1+2+3+4+5+6+7+8));
		}
		SECTION("each(vec0, vec1) from container")
		{
			unsigned int sum = 0u;
			range.each([&](auto v0, auto v1){sum += v0+v1;}, vec0, vec1);
			REQUIRE(sum == (10+1)*(1+2+3+4+5+6+7+8));
		}
		SECTION("each_index(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each_index([&](auto ix){sum += 10u*ix;});
			REQUIRE(sum == 10*(1+2+3+4+5+6+7+8));
		}
		SECTION("each_offset(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each_offset([&](auto ix0){sum += 10u*ix0;});
			REQUIRE(sum == 10*(0+1+2+3+4+5+6+7));
		}
		SECTION("each_with_offset(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each_with_offset([&](auto v0, auto ix0){REQUIRE(v0 == 10u*(ix0+range.begin())); sum += v0;}, vec0.data());
			REQUIRE(sum == 10*(1+2+3+4+5+6+7+8));
		}
	}
}