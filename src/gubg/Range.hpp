#ifndef HEADER_gubg_Range_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Range_hpp_ALREADY_INCLUDED


#ifdef RANGE
#error RANGE already defined
#endif
#define RANGE(ctr) (ctr).begin(), (ctr).end()

namespace gubg { 

    namespace details { 
        struct DoNothing { };
    } 

    template <typename It, typename Context = details::DoNothing>
    class Range
    {
    public:
        using reference = typename std::iterator_traits<It>::value_type;

        Range(It b, It e): begin_(b), end_(e) {}
        Range(It b, It e, Context &&context): context_(std::move(context)), begin_(b), end_(e) {}

        bool empty() const {return begin_ == end_;}
        size_t size() const {return end_ - begin_;}
        reference front() {return *begin_;}

        It begin() {return begin_;}
        It end() {return end_;}

        void pop_front() {++begin_;}

    private:
        Context context_;
        It begin_;
        It end_;
    };

    template <typename It>
    Range<It> make_range(It b, It e)
    {
        return Range<It>(b, e);
    }
    template <typename It, typename Context>
    Range<It, Context> make_range(It b, It e, Context &&context)
    {
        return Range<It, Context>(b, e, std::move(context));
    }
    template <typename It>
    Range<It> make_range(It b, size_t nr)
    {
        return Range<It>(b, b+nr);
    }
} 

#endif
