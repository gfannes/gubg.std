#ifndef HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED
#define HEADER_gubg_std_cstddef_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_COMPILER_GCC
#include <cstddef>
#endif

#if GUBG_PLATFORM_COMPILER_MSVC
#include <cstddef>
namespace std { 
    enum class byte: unsigned char {};
} 
#endif

#endif
