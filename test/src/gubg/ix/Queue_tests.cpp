#include <catch.hpp>
#include <gubg/ix/Queue.hpp>

using namespace gubg;

TEST_CASE("", "[ut][ix][Queue]")
{
    ix::Queue queue;
    REQUIRE(queue.capacity() == 0);
    REQUIRE(queue.size() == 0);
    REQUIRE(queue.full());
    REQUIRE(queue.empty());

    REQUIRE(queue.pop() == std::nullopt);

    REQUIRE(queue.push() == std::nullopt);

    queue.init(3);
    REQUIRE(queue.capacity() == 3);
    REQUIRE(queue.size() == 0);
    REQUIRE(!queue.full());
    REQUIRE(queue.empty());

    REQUIRE(queue.pop() == std::nullopt);

    REQUIRE(queue.push() == std::make_optional(0u));
    REQUIRE(queue.push() == std::make_optional(1u));
    REQUIRE(queue.push() == std::make_optional(2u));
    REQUIRE(queue.push() == std::nullopt);

    REQUIRE(queue.pop() == std::make_optional(0u));
    REQUIRE(queue.pop() == std::make_optional(1u));
    REQUIRE(queue.pop() == std::make_optional(2u));
    REQUIRE(queue.pop() == std::nullopt);

    REQUIRE(queue.push() == std::make_optional(0u));
    REQUIRE(queue.push() == std::make_optional(1u));
    REQUIRE(queue.push() == std::make_optional(2u));
    REQUIRE(queue.push() == std::nullopt);

    REQUIRE(queue.pop() == std::make_optional(0u));
    REQUIRE(queue.pop() == std::make_optional(1u));
    REQUIRE(queue.pop() == std::make_optional(2u));
    REQUIRE(queue.pop() == std::nullopt);
}
