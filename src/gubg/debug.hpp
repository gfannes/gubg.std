#ifndef HEADER_gubg_debug_hpp_ALREADY_INCLUDED
#define HEADER_gubg_debug_hpp_ALREADY_INCLUDED

#include "gubg/platform.h"

#if GUBG_PLATFORM_OS_ARDUINO
#include "gubg/debug_noop.hxx"
#else
#include "gubg/debug_cout.hxx"
#endif

#endif
