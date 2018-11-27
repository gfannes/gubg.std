#ifndef HEADER_gubg_platform_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_h_ALREADY_INCLUDED

#include "gubg/platform/compiler.h"
#if !defined(GUBG_PLATFORM_COMPILER)
#error GUBG_PLATFORM_COMPILER define not set
#endif
#if !(GUBG_PLATFORM_COMPILER_VERSION)
#error GUBG_PLATFORM_COMPILER_VERSION define not set
#endif
#if GUBG_PLATFORM_COMPILER_GCC
#elif GUBG_PLATFORM_COMPILER_MSVC
#else
#error Unknown compiler brand
#endif

#include "gubg/platform/os.h"
#if !defined(GUBG_PLATFORM_OS)
#error GUBG_PLATFORM_OS define not set
#endif

#include "gubg/platform/endian.h"
#if !defined(GUBG_PLATFORM_ENDIAN) || (!GUBG_PLATFORM_ENDIAN_LITTLE && !GUBG_PLATFORM_ENDIAN_BIG)
#error Not all endian defines are set
#endif

#if 0
#ifndef GUBG_PLATFORM_BITS
#error GUBG_PLATFORM_BITS is not available
#endif

#ifndef GUBG_PLATFORM_ARCH
#error GUBG_PLATFORM_ARCH is not available
#endif
#endif

#endif
