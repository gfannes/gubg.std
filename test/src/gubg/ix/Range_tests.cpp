#include <gubg/ix/Range.hpp>
#include <catch.hpp>
#include <vector>
using namespace gubg;

TEST_CASE("Basic functionality tests", "[ut][ix][Range]")
{
	ix::Range range;
	std::size_t size = 0u;

	SECTION("check defaults")
	{
		REQUIRE(range.begin() == 0u);
		REQUIRE(range.end() == 0u);
		REQUIRE(range.size() == 0u);
		REQUIRE(range.empty());
	}

	SECTION("consume()")
	{
		range.consume(1u, size);
		REQUIRE(size == 1u);
		REQUIRE(range.begin() == 0u);
		REQUIRE(range.size() == 1u);

		range.consume(2u, size);
		REQUIRE(size == 3u);
		REQUIRE(range.begin() == 1u);
		REQUIRE(range.size() == 2u);
	}

	SECTION("each*()")
	{
		range.consume(10u, size);

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
			REQUIRE(sum == 10*(0+1+2+3+4+5+6+7+8+9));
		}
		SECTION("each(vec0) from container")
		{
			unsigned int sum = 0u;
			range.each([&](auto v0){sum += v0;}, vec0);
			REQUIRE(sum == 10*(0+1+2+3+4+5+6+7+8+9));
		}
		SECTION("each(vec0, vec1) from container")
		{
			unsigned int sum = 0u;
			range.each([&](auto v0, auto v1){sum += v0+v1;}, vec0, vec1);
			REQUIRE(sum == (10+1)*(0+1+2+3+4+5+6+7+8+9));
		}
		SECTION("each_index(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each_index([&](auto ix){sum += 10u*ix;});
			REQUIRE(sum == 10*(0+1+2+3+4+5+6+7+8+9));
		}
		SECTION("each_with_index(vec0) from pointer")
		{
			unsigned int sum = 0u;
			range.each_with_index([&](auto v0, auto ix){REQUIRE(v0 == 10u*ix); sum += v0;}, vec0.data());
			REQUIRE(sum == 10*(0+1+2+3+4+5+6+7+8+9));
		}
	}
}