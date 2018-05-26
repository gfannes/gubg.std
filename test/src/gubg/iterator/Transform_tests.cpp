#include "catch.hpp"
#include "gubg/iterator/Transform.hpp"
#include <iterator>
#include <sstream>
#include <forward_list>
#include <list>
#include <vector>
#include <map>

namespace {
    template <typename It, typename Tag> 
    bool check_category(It it = It(), Tag tag = Tag())
    {
        return std::is_same<typename std::iterator_traits<It>::iterator_category, Tag>::value;
    }

#define IS_CAT(IT, TAG) REQUIRE( (check_category<IT, TAG>()) )

    struct Transform
    {
        std::string operator()(char c) const
        {
            return std::string(1, c);
        }
    };

    template <typename It> void test(It first, It last, std::input_iterator_tag)
    {
        REQUIRE(first != last);
        REQUIRE(*first == "a");
        REQUIRE(first->size() == 1);
        REQUIRE(*first++ == "a");
        REQUIRE(*first == "b");
        ++first;
        first++;
        REQUIRE(first == last);
    }
    
    template <typename It> void test(It first, It last, std::forward_iterator_tag)
    {
        test(first, last, std::input_iterator_tag());
        test(first, last, std::input_iterator_tag());
    }
    
    template <typename It> void test(It first, It last, std::bidirectional_iterator_tag)
    {
        test(first, last, std::forward_iterator_tag());
        It it2 = first;
        it2++;

        REQUIRE(*it2-- == "b");
        REQUIRE(*it2 == "a");

        it2++;
        REQUIRE(--it2 == first);
    }
    
    template <typename It> void test(It first, It last, std::random_access_iterator_tag)
    {
        test(first, last, std::bidirectional_iterator_tag());

        {
            It it = first;
            it += 3;
            REQUIRE(it == last);
        }

        REQUIRE(first + 3 == last);
        REQUIRE(3 +first == last);

        {
            It it = last;
            it -= 3;
            REQUIRE(it == first);
        }

        REQUIRE(last - 3 == first);

        REQUIRE( (last - first)  == 3);
        REQUIRE(first[0] == "a");
        REQUIRE(first[1] == "b");
        REQUIRE(first[2] == "c");

        REQUIRE(first < last);
        REQUIRE(first <= last);
        REQUIRE(first+1 > first);
        REQUIRE(first+1 >= first);
        REQUIRE(first <= first);
        REQUIRE(first >= first);
    }
}

TEST_CASE("Input iterator test", "[ut][iterator]")
{
    typedef std::istream_iterator<char> Iterator;
    typedef gubg::iterator::Transform<Iterator, Transform> TransformIterator;

    IS_CAT(Iterator, std::input_iterator_tag);
    IS_CAT(TransformIterator, std::input_iterator_tag);


    std::stringstream ss("abc");
    TransformIterator it { Iterator(ss) };
    TransformIterator end;

    test(it, end, std::iterator_traits<TransformIterator>::iterator_category());
}

TEST_CASE("Forward iterator test", "[ut][iterator]")
{
    typedef std::forward_list<char> List;
    typedef List::iterator Iterator;
    typedef gubg::iterator::Transform<Iterator, Transform> TransformIterator;

    IS_CAT(Iterator, std::forward_iterator_tag);
    IS_CAT(TransformIterator, std::forward_iterator_tag);

    List lst = { 'a', 'b', 'c' };

    TransformIterator it { lst.begin() };
    TransformIterator end { lst.end() };
    
    test(it, end, std::iterator_traits<TransformIterator>::iterator_category());
}

TEST_CASE("Bidirectional iterator test", "[ut][iterator]")
{
    typedef std::list<char> List;
    typedef List::iterator Iterator;
    typedef gubg::iterator::Transform<Iterator, Transform> TransformIterator;

    IS_CAT(Iterator, std::bidirectional_iterator_tag);
    IS_CAT(TransformIterator, std::bidirectional_iterator_tag);

    List lst = { 'a', 'b', 'c' };

    TransformIterator it { lst.begin() };
    TransformIterator end { lst.end() };
    
    test(it, end, std::iterator_traits<TransformIterator>::iterator_category());
}

TEST_CASE("Random accesss iterator test", "[ut][iterator]")
{
    typedef std::vector<char> Vct;
    typedef Vct::iterator Iterator;
    typedef gubg::iterator::Transform<Iterator, Transform> TransformIterator;

    IS_CAT(Iterator, std::random_access_iterator_tag);
    IS_CAT(TransformIterator, std::random_access_iterator_tag);

    Vct vct = { 'a', 'b', 'c' };

    TransformIterator it { vct.begin() };
    TransformIterator end { vct.end() };
    
    test(it, end, std::iterator_traits<TransformIterator>::iterator_category());
}


TEST_CASE("gubg range test", "[ut][iterator]")
{
    typedef std::vector<char> Vct;
    typedef Vct::iterator Iterator;
    typedef gubg::iterator::Transform<Iterator, Transform> TransformIterator;

    Vct vct = { 'a', 'b', 'c' };
    
    
    TransformIterator it = gubg::iterator::transform<Transform>(vct.begin());
    {
        gubg::iterator::Transform<Vct::const_iterator, Transform> cit = it;
        cit = it;
        REQUIRE(cit == it);
    }
    auto range1 = gubg::iterator::transform<Transform>(gubg::make_range(vct));
    auto range2 = gubg::iterator::transform(gubg::make_range(vct), [](char c) { return std::string(1, c); });
    REQUIRE(it == range1.begin());

    bool eq = std::equal(RANGE(range1), RANGE(range2));
    REQUIRE(eq);

}

namespace {

    struct T
    {
        std::string & operator()(std::pair<const int, std::string> & p)
        {
            return p.second;
        }
    };
}

TEST_CASE("mutable test", "[ut][iterator]")
{
    std::map<int, std::string> v;
    v[0] = "abc";
    v[1] = "bcd";

    auto rng = gubg::iterator::transform(gubg::make_range(v), [](auto & p) -> std::string &  {return p.second; });
    while(!rng.empty())
    {
        rng.front() = "bbb";
        rng.pop_front();
    }

    REQUIRE(v[0] == "bbb");
    REQUIRE(v[1] == "bbb");
    REQUIRE(v.size() == 2);
}
