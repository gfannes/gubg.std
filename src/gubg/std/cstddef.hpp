#ifndef HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_COMPILER_GCC
#if GUBG_PLATFORM_OS_ARDUINO
namespace std { 
    enum class byte: unsigned char {};
} 
#else
#include <cstddef>
#endif
#endif

#if GUBG_PLATFORM_COMPILER_MSVC
#include <cstddef>
namespace std { 
    //Not sure if this check is strict enough, at least, on 14.14.26428, std::byte seems to be known
#if GUBG_PLATFORM_COMPILER_VERSION < 191426
    enum class byte: unsigned char {};
#endif
} 
#endif

#endif
