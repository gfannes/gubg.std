#ifndef HEADER_gubg_mss_hpp_ALREADY_INCLUDED
#define HEADER_gubg_mss_hpp_ALREADY_INCLUDED

namespace gubg { namespace mss { 
    template <typename T>
        bool ok(T v) {return v;}
} } 

#include "gubg/macro/variadic.h"

#if defined(MSS) || defined(MSS_1) || defined(MSS_2)
#error MSS macros already defined
#endif
#define MSS_1(expr) do { \
    const auto rc = (expr); \
    if (!gubg::mss::ok(rc)) \
    { \
        return rc; \
    } \
} while (false)
#define MSS_2(expr,action) do { \
    const auto rc = (expr); \
    if (!gubg::mss::ok(rc)) \
    { \
        action; \
        return rc; \
    } \
} while (false)
#define MSS(...) GUBG_GET_ARG_3((__VA_ARGS__, MSS_2,MSS_1))(__VA_ARGS__)

#endif
