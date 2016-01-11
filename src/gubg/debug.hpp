#ifndef HEADER_gubg_debug_hpp_ALREADY_INCLUDED
#define HEADER_gubg_debug_hpp_ALREADY_INCLUDED

#include "gubg/macro/stream.hpp"
#include <iostream>

#define S(debug_ns) \
    const char * const l_debug_ns = debug_ns; \
    if (!!l_debug_ns) {std::cout << ">>" << l_debug_ns << std::endl;}

#define L(msg) do { \
    if (!!l_debug_ns) \
        std::cout << l_debug_ns << "::" << __func__ << ": " << msg << " (" << __FILE__ << ':' << __LINE__ << ")" << std::endl; \
    } while (false)

#endif
