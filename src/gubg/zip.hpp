#ifndef HEADER_gubg_zip_hpp_ALREADY_INCLUDED
#define HEADER_gubg_zip_hpp_ALREADY_INCLUDED

namespace gubg { 

    template <typename It0, typename It1, typename Ftor>
        bool zip(It0 it_0, It0 end_0, It1 it_1, Ftor ftor)
        {
            for (; it_0 != end_0; ++it_0, ++it_1)
                if (!ftor(*it_0, *it_1))
                    return false;
            return true;
        }

} 

#endif
