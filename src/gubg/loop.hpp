#ifndef HEADER_gubg_loop_hpp_ALREADY_INCLUDED
#define HEADER_gubg_loop_hpp_ALREADY_INCLUDED

namespace gubg { 

    template <typename Nr, typename Ftor>
        void loop(Nr nr, Ftor ftor)
        {
            for (Nr i = 0; i < nr; ++i)
                ftor();
        }

} 

#endif
