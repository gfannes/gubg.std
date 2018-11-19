#ifndef HEADER_gubg_platform_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_h_ALREADY_INCLUDED

#include "gubg/platform/compiler.h"
#if !defined(GUBG_PLATFORM_COMPILER) || !defined(GUBG_PLATFORM_COMPILER_GCC) || !defined(GUBG_PLATFORM_COMPILER_VERSION)
#error Not all compiler defines are set
#endif

#include "gubg/platform/os.h"
#if !defined(GUBG_PLATFORM_OS) || (!defined(GUBG_PLATFORM_API_POSIX) && !defined(GUBG_PLATFORM_API_WIN32) && !defined(GUBG_PLATFORM_API_ARDUINO))
#error Not all os defines are set
#endif

#include "gubg/platform/endian.h"
#if !defined(GUBG_PLATFORM_ENDIAN) || (!defined(GUBG_PLATFORM_ENDIAN_LITTLE) && !defined(GUBG_PLATFORM_ENDIAN_BIG))
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
