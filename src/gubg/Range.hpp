#ifndef HEADER_gubg_Range_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Range_hpp_ALREADY_INCLUDED


#ifdef RANGE
#error RANGE already defined
#endif
#define RANGE(ctr) (ctr).begin(), (ctr).end()

namespace gubg { 

    template <typename It>
        class Range
        {
            public:
                using reference = typename std::iterator_traits<It>::value_type;

                Range(It b, It e): begin_(b), end_(e) {}

                bool empty() const {return begin_ == end_;}
                reference front() {return *begin_;}

                It begin() {return begin_;}
                It end() {return end_;}

                void pop_front() {++begin_;}

            private:
                It begin_;
                It end_;
        };

    template <typename It>
        Range<It> make_range(It b, It e)
        {
            return Range<It>(b, e);
        }
} 

#endif
