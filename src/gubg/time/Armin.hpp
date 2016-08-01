#ifndef HEADER_gubg_time_Armin_hpp_ALREADY_INCLUDED
#define HEADER_gubg_time_Armin_hpp_ALREADY_INCLUDED

#include "gubg/mss.hpp"

namespace gubg { namespace time { 

    template <typename Dst>
        bool from_armin(Dst &dst_sec, const unsigned int src_sec)
        {
            MSS_BEGIN(bool);
            dst_sec = (src_sec/100)*60;
            dst_sec += (src_sec%100);
            MSS_END();
        }

} } 

#endif
