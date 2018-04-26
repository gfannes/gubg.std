#ifndef HEADER_gubg_platform_os_api_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_os_api_h_ALREADY_INCLUDED

//OS API info
#ifdef __linux
#define GUBG_API_LINUX
#define GUBG_API_POSIX
#endif//__linux

#ifdef __APPLE__
#define GUBG_API_APPLE
#define GUBG_API_POSIX
#endif//__APPLE__

#ifdef _WIN32
#define GUBG_API_WIN32
#ifdef __MINGW32__
#define GUBG_API_MINGW
#define GUBG_API_POSIX
#endif//__MINGW32__
#endif//_WIN32

#endif
