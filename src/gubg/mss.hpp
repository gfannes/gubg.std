#ifndef HEADER_gubg_mss_hpp_ALREADY_INCLUDED
#define HEADER_gubg_mss_hpp_ALREADY_INCLUDED

#include <type_traits>

namespace gubg { namespace mss { 

    namespace detail { 
        template <typename RC> struct Traits
            {
                static const RC Ok() { return RC::OK;  }
                static const RC Error() { return RC::Error; }
            };
        template <>
            struct Traits<bool>
            {
                static const bool Ok() { return true; }
                static const bool Error() { return false; }
            };
        template <>
            struct Traits<int>
            {
                static const int Ok() { return 0; }
                static const int Error() { return -1; }
            };
    } 
    template <typename RC>
        RC ok_value(){return detail::Traits<RC>::Ok();}

    namespace detail { 
        template <typename RC, typename Src>
            struct ErrorValue
            {
                static RC error_value(Src src){return Traits<RC>::Error();}
            };
        template <typename RC>
            struct ErrorValue<RC, RC>
            {
                static RC error_value(RC src){return src;}
            };
    } 
    template <typename RC, typename Src>
        RC error_value(Src src){return detail::ErrorValue<RC, Src>::error_value(src);}

    template <typename RC>
        bool is_ok(RC rc) {return rc == ok_value<RC>();}

    template <typename T, typename RC>
        RC on_fail(T v, RC e)
        {
            if (is_ok(v))
                return ok_value<RC>();
            return e;
        }

} } 

#include "gubg/macro/variadic.h"
#include "gubg/debug.hpp"

//MSS_BEGIN
#if defined(MSS_BEGIN) || defined(MSS_BEGIN_1) || defined(MSS_BEGIN_2)
#error MSS_BEGIN macros already defined
#endif
#define MSS_BEGIN_1(rc_type) \
    S(nullptr); \
    using l_rc_type = rc_type
#define MSS_BEGIN_2(rc_type,logns) \
    S(logns); \
    using l_rc_type = rc_type
#define MSS_BEGIN(...) GUBG_GET_ARG_3((__VA_ARGS__, MSS_BEGIN_2,MSS_BEGIN_1))(__VA_ARGS__)

//MSS
#if defined(MSS) || defined(MSS_1) || defined(MSS_2)
#error MSS macros already defined
#endif
#define MSS_1(expr) do { \
    const auto l_rc = (expr); \
    if (!gubg::mss::is_ok(l_rc)) \
    { \
        S("MSS"); L("Error: " #expr << " failed in \"" << __FILE__ << ":" << __LINE__ << "\""); \
        return gubg::mss::error_value<l_rc_type>(l_rc); \
    } \
} while (false)
#define MSS_2(expr,action) do { \
    const auto l_rc = (expr); \
    if (!gubg::mss::is_ok(l_rc)) \
    { \
        S("MSS"); L("Error: " #expr << " failed in \"" << __FILE__ << ":" << __LINE__ << "\""); \
        action; \
        return gubg::mss::error_value<l_rc_type>(l_rc); \
    } \
} while (false)
#define MSS(...) GUBG_GET_ARG_3((__VA_ARGS__, MSS_2,MSS_1))(__VA_ARGS__)

//MSS_Q
#if defined(MSS_Q) || defined(MSS_Q_1) || defined(MSS_Q_2)
#error MSS_Q macros already defined
#endif
#define MSS_Q_1(expr) do { \
    const auto l_rc = (expr); \
    if (!gubg::mss::is_ok(l_rc)) \
    { \
        return gubg::mss::error_value<l_rc_type>(l_rc); \
    } \
} while (false)
#define MSS_Q_2(expr,action) do { \
    const auto l_rc = (expr); \
    if (!gubg::mss::is_ok(l_rc)) \
    { \
        action; \
        return gubg::mss::error_value<l_rc_type>(l_rc); \
    } \
} while (false)
#define MSS_Q(...) GUBG_GET_ARG_3((__VA_ARGS__, MSS_Q_2,MSS_Q_1))(__VA_ARGS__)

//MSS_END
#if defined(MSS_END)
#error MSS_END macros already defined
#endif
#define MSS_END() return gubg::mss::ok_value<l_rc_type>()

//MSS_RETURN_OK
#if defined(MSS_RETURN_OK)
#error MSS_RETURN_OK macros already defined
#endif
#define MSS_RETURN_OK() return gubg::mss::ok_value<l_rc_type>()

#endif
