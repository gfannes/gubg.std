#ifndef HEADER_gubg_block_each_hpp_ALREADY_INCLUDED
#define HEADER_gubg_block_each_hpp_ALREADY_INCLUDED

#include <gubg/mss.hpp>

namespace gubg { namespace block { 

    template <typename T, typename Ftor>
    bool each(std::size_t blocksize, T *b, T *e, Ftor &&ftor)
    {
        MSS_BEGIN(bool);
        const auto size = e-b;
        const auto nrblocks = size/blocksize;
        MSS(nrblocks*blocksize == size);
        for (auto bix = 0u; bix < nrblocks; ++bix)
        {
            e = b+blocksize;
            MSS(ftor(b, e));
            b = e;
        }
        MSS_END();
    }

    template <typename T, typename Ftor>
    bool each(std::size_t blocksize, std::vector<T> &vec, Ftor &&ftor)
    {
        T *ptr = vec.data();
        return each(blocksize, ptr, ptr+vec.size(), ftor);
    }

} } 

#endif
