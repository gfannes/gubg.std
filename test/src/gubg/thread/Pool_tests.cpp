#include <gubg/thread/Pool.hpp>
#include <catch.hpp>
#include <iostream>
using namespace gubg;

TEST_CASE("thread::Pool tests", "[ut][thread][Pool]")
{
    using Argument = std::string;
    auto lambda = [](const std::string &str)
    {
        std::cout << str << std::endl;
    };
    thread::Pool<Argument> tp{10, lambda};
}
