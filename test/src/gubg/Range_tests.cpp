#include "catch.hpp"
#include "gubg/Range.hpp"
#include <iostream>
#include <memory>
using namespace gubg;
using namespace std;

TEST_CASE("gubg::Range tests with default context", "[ut][gubg][Range]")
{
    const size_t nr = 3;
    int ary[nr] = {1,2,3};

    auto r = make_range(ary, nr); 
    REQUIRE(r.front() == 1);
    REQUIRE(r.back() == 3);

    size_t i = 0;
    for (auto e: r)
    {
        REQUIRE(++i == e);
        cout << e << ' ';
    }
    cout << endl;
}

TEST_CASE("gubg::Range tests with non-default context", "[ut][gubg][Range]")
{
    auto ptr = make_shared<vector<int>>(3);
    *ptr = {1,2,3};
    auto r = make_range(ptr->begin(), ptr->end(), std::move(ptr));
    ptr.reset();
    auto rr = r;

    size_t i = 0;
    for (auto e: rr)
    {
        REQUIRE(++i == e);
        cout << e << ' ';
    }
    cout << endl;
}
