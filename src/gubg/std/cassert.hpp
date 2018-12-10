#ifndef HEADER_gubg_std_cassert_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cassert_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO
#define assert(condition)
#define static_assert(condition, message)
#else
#include <cassert>
#endif

#endif
