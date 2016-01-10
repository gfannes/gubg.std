#ifndef HEADER_gubg_platform_compiler_info_h_ALREADY_INCLUDED
#define HEADER_gubg_platform_compiler_info_h_ALREADY_INCLUDED

//Compiler info
#ifdef __GNUC__
#define GUBG_CC_GCC
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif
#ifdef _MSC_VER
#define GUBG_CC_MSC
#endif

#endif
