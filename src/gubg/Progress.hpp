#ifndef HEADER_gubg_Progress_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Progress_hpp_ALREADY_INCLUDED

namespace gubg { 

    struct Progresss
    {
            size_t ix = 0;
            size_t nr = 0;

            Progresss(){}
            Progresss(size_t nr): nr(nr) {}

            operator bool() const {return ix < nr;}

            Progresss &operator++()
            {
                ++ix;
                return *this;
            }
            Progresss operator++(int)
            {
                Progresss ret = *this;
                operator++();
                return ret;
            }

            template <typename T>
                T operator()(T v) const { return v*ix/nr; }

        private:
    };

} 

#endif
