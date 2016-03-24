#include "catch.hpp"
#include "gubg/thread/Semaphore.hpp"
using namespace gubg::thread;

TEST_CASE("Semaphore tests", "[ut][semaphore]")
{
    Semaphore s(2);
    s.take();
    s.take();
    /* s.take(); */
}
