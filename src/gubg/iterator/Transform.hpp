#ifndef HEADER_gubg_iterator_Transform_hpp_ALREADY_INCLUDED
#define HEADER_gubg_iterator_Transform_hpp_ALREADY_INCLUDED

#include "gubg/Range.hpp"
#include <iterator>

namespace gubg { namespace iterator { 
    
    template <typename Iterator, typename Functor> class Transform;
    
    namespace detail {

    template <typename Reference, typename Pointer> struct arrow_operator_dispatch
    {
        struct proxy
        {
            explicit proxy(const Reference & ref) : ref_(ref) {}

            Reference * operator->() { return std::addressof(ref_); }
            operator Reference *() { return std::addressof(ref_); }

            private:
            Reference ref_;
        };

        using type = proxy;
        static type apply(const Reference & ref) { return type(ref); }
    };

    template <typename ValueType, typename Pointer> struct arrow_operator_dispatch<ValueType &, Pointer>
    {
        using type = Pointer;
        static type apply(ValueType & value) { return std::addressof(value); }
    };

    template <typename Derived, typename Iterator, typename Functor, typename Tag> class Transform;


    template <typename Derived, typename Iterator, typename Functor> class Transform<Derived, Iterator, Functor, std::input_iterator_tag>
    {
        public:
            using result_type = std::result_of_t<Functor(typename std::iterator_traits<Iterator>::reference)>;
            using arrow_dispatch = detail::arrow_operator_dispatch<result_type, std::remove_reference_t<result_type> *>;

        public:
            using difference_type = typename std::iterator_traits<Iterator>::difference_type;
            using value_type = std::decay_t<result_type>;
            using reference = result_type;
            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using pointer = typename arrow_dispatch::type;

        public:
            template <typename It>
            explicit Transform(It it, Functor functor) 
            : base_(it),transform_(functor) 
            {
            }


            template <typename D, typename I>
            bool operator==(const Transform<D, I, Functor, std::input_iterator_tag> & rhs) const 
            { 
                return base() == rhs.base(); 
            }

            template <typename D, typename I>
            bool operator!=(const Transform<D, I, Functor, std::input_iterator_tag> & rhs) const 
            { 
                return base() != rhs.base(); 
            }

            reference operator*() const 
            { 
                return transform_(*base()); 
            }

            pointer operator->() const 
            { 
                return pointer(transform_(*base())); 
            }

            Derived & operator++() 
            {
                ++base_; 
                return static_cast<Derived&>(*this); 
            }

            Derived operator++(int) 
            {
                return Derived(base_++, transform_);
            }

            Iterator base() const 
            { 
                return base_; 
            }

        private:
            template <typename D, typename I, typename F, typename T> friend class Transform;
            template <typename I, typename F> friend class iterator::Transform;

            Iterator base_;
            Functor transform_;
    };

    template <typename Derived, typename Iterator, typename Functor> class Transform<Derived, Iterator, Functor, std::forward_iterator_tag>
    : public Transform<Derived, Iterator, Functor, std::input_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Functor, std::input_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Functor functor) 
            : Transform<Derived, Iterator, Functor, std::input_iterator_tag>(it, functor) 
            {

            }
    };

    template <typename Derived, typename Iterator, typename Functor> class Transform<Derived, Iterator, Functor, std::bidirectional_iterator_tag>
    : public Transform<Derived, Iterator, Functor, std::forward_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Functor, std::forward_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Functor functor) 
            : Transform<Derived, Iterator, Functor, std::forward_iterator_tag>(it, functor) 
            {

            }

            Derived & operator--()
            {
                --this->base_;
                return static_cast<Derived&>(*this); 
            }

            Derived operator--(int)
            {
                return Derived(this->base_--, this->transform_);
            }
    };

    template <typename Derived, typename Iterator, typename Functor> class Transform<Derived, Iterator, Functor, std::random_access_iterator_tag>
    : public Transform<Derived, Iterator, Functor, std::bidirectional_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Functor, std::bidirectional_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Functor functor) 
            : Transform<Derived, Iterator, Functor, std::bidirectional_iterator_tag>(it, functor) 
            {
            }

            Derived & operator+=(typename Transform::difference_type n)
            {
                this->base_ += n;
                return static_cast<Derived &>(*this);
            }

            Derived & operator-=(typename Transform::difference_type n)
            {
                this->base_ -= n;
                return static_cast<Derived &>(*this);
            }

            Derived operator+(typename Transform::difference_type n) const
            {
                return Derived(this->base_ + n, this->transform_);
            }

            Derived operator-(typename Transform::difference_type n) const
            {
                return Derived(this->base_ - n, this->transform_);
            }

            typename Transform::difference_type operator-(const Derived & rhs) const
            {
                return this->base_ - rhs.base_;
            }

            typename Transform::reference operator[](typename Transform::difference_type n) const
            {
                return *(this->operator+(n));
            }

            bool operator<(const Derived & rhs) const
            {
                return this->base_ < rhs.base_;
            }
            bool operator>(const Derived & rhs) const
            {
                return this->base_ > rhs.base_;
            }
            bool operator<=(const Derived & rhs) const
            {
                return this->base_ <= rhs.base_;
            }
            bool operator>=(const Derived & rhs) const
            {
                return this->base_ >= rhs.base_;
            }
    };

    template <typename Derived, typename Iterator, typename Functor> 
    Derived operator+(typename Derived::difference_type n, const Transform<Derived, Iterator, Functor, std::random_access_iterator_tag> & it)
    {
        return it + n;
    }
} 

    template <typename Iterator, typename Functor>
    class Transform 
    : public detail::Transform<Transform<Iterator, Functor>, Iterator, Functor, typename std::iterator_traits<Iterator>::iterator_category>
    {
        using Base = detail::Transform<Transform<Iterator, Functor>, Iterator, Functor, typename std::iterator_traits<Iterator>::iterator_category>;

    public:
        Transform()
        : Base(Iterator(), Functor())
        {

        }
        
        template <typename It>
        explicit Transform(It it, Functor f = Functor())
        : Base(it, f)
        {
        }

        template <typename It>
        Transform(const Transform<It, Functor> & rhs)
        : Base(rhs.base(), rhs.transform_)
        {
        }

        template <typename It>
        Transform(Transform<It, Functor> && rhs)
        {
            Base(std::move(rhs.base_), std::move(rhs.transform_));
        }

        template <typename It>
        Transform & operator=(const Transform<It, Functor> & rhs)
        {
            this->base_ = rhs.base_;
            this->transform_ = rhs.transform_;
            return *this;
        }
        
        template <typename It>
        Transform & operator=(Transform<It, Functor> && rhs)
        {
            this->base_ = std::move(rhs.base_);
            this->transform_ = std::move(rhs.transform_);
            return *this;
        }
    };
    
    template <typename Functor, typename It>
    Transform<It, Functor> transform(It it, Functor f = Functor())
    {
        return Transform<It, Functor>(it, f);
    }

    template <typename Functor, typename It>
    Range<Transform<It, Functor>> transform(const Range<It> & range, Functor f = Functor())
    {
        return make_range(transform(range.begin(),f), transform(range.end(), f));
    }

} }

#endif

