#ifndef HEADER_gubg_platform_os_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_os_h_ALREADY_INCLUDED

#if defined(linux) || defined(__linux)
#define GUBG_PLATFORM_OS "linux"
#define GUBG_PLATFORM_OS_LINUX 1
#define GUBG_PLATFORM_API_POSIX 1
#endif

#if defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
#define GUBG_PLATFORM_OS "osx"
#define GUBG_PLATFORM_OS_OSX 1
#define GUBG_PLATFORM_API_POSIX 1
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#define GUBG_PLATFORM_OS "windows"
#define GUBG_PLATFORM_OS_WINDOWS 1
#ifdef __MINGW32__
#define GUBG_PLATFORM_API_MINGW 1
#define GUBG_PLATFORM_API_POSIX 1
#endif
#endif

#endif
