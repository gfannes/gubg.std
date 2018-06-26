#ifndef HEADER_gubg_platform_os_api_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_os_api_h_ALREADY_INCLUDED

//OS API info
#ifdef __linux
#define GUBG_API_LINUX 1
#define GUBG_API_POSIX 1
#endif//__linux

#ifdef __APPLE__
#define GUBG_API_APPLE 1
#define GUBG_API_POSIX 1
#endif//__APPLE__

#ifdef _WIN32
#define GUBG_API_WIN32 1
#ifdef __MINGW32__
#define GUBG_API_MINGW 1
#define GUBG_API_POSIX 1
#endif//__MINGW32__
#endif//_WIN32

#endif
