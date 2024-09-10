#include <gubg/thread/Pool2.hpp>

#include <catch.hpp>

#include <cstdint>

using namespace gubg;

namespace {
    struct Fibo
    {
        std::uint64_t n;
        std::uint64_t res;

        Fibo(std::uint64_t n): n(n) {}

        bool operator()()
        {
            res = fibo_(n);
            return true;
        }

    private:
        static std::uint64_t fibo_(std::uint64_t n)
        {
            if (n < 2)
                return n;
            return fibo_(n - 1) + fibo_(n - 2);
        }
    };
} // namespace

TEST_CASE("", "[ut][thread][Pool2]")
{
    S("");

    thread::Pool2<Fibo> pool;

    REQUIRE(pool.init(3, 2, 10));
    REQUIRE(pool.start());
    REQUIRE(pool.push(Fibo(45)));
    REQUIRE(pool.pop(false, [&](const auto &input, const auto &output) { L(C(input) C(output)); }));
}
