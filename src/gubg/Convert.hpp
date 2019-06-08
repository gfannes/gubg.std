#ifndef HEADER_gubg_Convert_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Convert_hpp_ALREADY_INCLUDED

#include <string>
#include <cstdlib>

namespace gubg { 

    template <typename Dst, typename Src>
    bool convert(Dst &dst, const Src &src)
    {
        dst = Dst{src};
        return true;
    }

    inline bool convert(double &dbl, const std::string &str)
    {
        const char *ptr = str.c_str();
        char *end = nullptr;
        dbl = std::strtod(ptr, &end);
        return end != ptr;
    }

} 

#endif
