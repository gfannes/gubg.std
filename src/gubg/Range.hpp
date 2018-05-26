#ifndef HEADER_gubg_Range_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Range_hpp_ALREADY_INCLUDED

#include <utility>
#include <iterator>

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
        using reference = typename std::iterator_traits<It>::reference;

        Range() {}
        Range(It b, It e): begin_(b), end_(e) {}
        Range(It b, It e, Context &&context): context_(std::move(context)), begin_(b), end_(e) {}

        bool empty() const {return begin_ == end_;}
        size_t size() const {return end_ - begin_;}
        reference front() const {return *begin_;}
        reference back() const {return *std::prev(end_);}

        It begin() const {return begin_;}
        It end() const { return end_;}

        void pop_front() {++begin_;}

        template <typename It2>
        bool operator==(const Range<It2> & rhs) const
        {
            return begin_ == rhs.begin_ && end_ == rhs.end_;
        }

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

    template <typename It>
    Range<It> make_range(const std::pair<It, It> & p)
    {
        return Range<It>(p.first, p.second);
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

    template <typename Container>
    Range<typename Container::iterator> make_range(Container & container)
    {
        return Range<typename Container::iterator>(RANGE(container));
    }

    template <typename Container>
    Range<typename Container::const_iterator> make_range(const Container & container)
    {
        return Range<typename Container::const_iterator>(RANGE(container));
    }
} 

#endif
