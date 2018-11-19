#ifndef HEADER_gubg_platform_endian_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_endian_h_ALREADY_INCLUDED

#include "gubg/platform/os.h"

#ifdef __GNUC__

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GUBG_PLATFORM_ENDIAN "little"
#define GUBG_PLATFORM_ENDIAN_LITTLE 1
#endif
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define GUBG_PLATFORM_ENDIAN "big"
#define GUBG_PLATFORM_ENDIAN_BIG 1
#endif

#else

#if GUBG_PLATFORM_OS_WINDOWS
#define GUBG_PLATFORM_ENDIAN "little"
#define GUBG_PLATFORM_ENDIAN_LITTLE 1
#endif

#endif

#endif
