#ifndef HEADER_gubg_iterator_Transform_hpp_ALREADY_INCLUDED
#define HEADER_gubg_iterator_Transform_hpp_ALREADY_INCLUDED

#include "gubg/Range.hpp"
#include <iterator>

namespace gubg { namespace iterator { 
    
    template <typename Iterator, typename Functor, bool dereference = true> class Transform;
    
    namespace detail {

        template <typename Functor, bool dereference>
        struct Transformer
        {
            template <typename It>
            using result_type = std::invoke_result_t<Functor, typename std::iterator_traits<It>::reference>;

            Transformer(Functor f = Functor()) : f_(f) {}

            template <typename Iterator>
            result_type<Iterator> apply(Iterator it) const
            {
                return f_(*it);
            }
            operator const Functor &() const { return f_; }

            Functor f_;
        };
        
        template <typename Functor>
        struct Transformer<Functor, false>
        {
            template <typename It>
            using result_type = std::invoke_result_t<Functor, It>;

            Transformer(Functor f = Functor()) : f_(f) {}
            template <typename Iterator>
            result_type<Iterator> apply(Iterator it) const
            
            {
                return f_(it);
            }

            Functor f_;
        };

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

    template <typename Derived, typename Iterator, typename Transformer, typename Tag> class Transform;


    template <typename Derived, typename Iterator, typename Transformer> 
    class Transform<Derived, Iterator, Transformer, std::input_iterator_tag>
    {
        public:
            using result_type = typename Transformer::template result_type<Iterator>;
            using arrow_dispatch = detail::arrow_operator_dispatch<result_type, std::remove_reference_t<result_type> *>;

        public:
            using difference_type = typename std::iterator_traits<Iterator>::difference_type;
            using value_type = std::decay_t<result_type>;
            using reference = result_type;
            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            using pointer = typename arrow_dispatch::type;

        public:
            template <typename It>
            explicit Transform(It it, Transformer functor) 
            : base_(it),transform_(functor) 
            {
            }


            template <typename D, typename I>
            bool operator==(const Transform<D, I, Transformer, std::input_iterator_tag> & rhs) const 
            { 
                return base() == rhs.base(); 
            }

            template <typename D, typename I>
            bool operator!=(const Transform<D, I, Transformer, std::input_iterator_tag> & rhs) const 
            { 
                return base() != rhs.base(); 
            }

            reference operator*() const 
            { 
                return transform_.apply(base()); 
            }

            pointer operator->() const 
            { 
                return pointer(this->operator*()); 
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
            template <typename I, typename F, bool d> friend class iterator::Transform;

            Iterator base_;
            Transformer transform_;
    };

    template <typename Derived, typename Iterator, typename Transformer> 
    class Transform<Derived, Iterator, Transformer, std::forward_iterator_tag>
    : public Transform<Derived, Iterator, Transformer, std::input_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Transformer, std::input_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Transformer transform) 
            : Base(it, transform) 
            {

            }
    };

    template <typename Derived, typename Iterator, typename Transformer> 
    class Transform<Derived, Iterator, Transformer, std::bidirectional_iterator_tag>
    : public Transform<Derived, Iterator, Transformer, std::forward_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Transformer, std::forward_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Transformer transform) 
            : Base(it, transform) 
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

    template <typename Derived, typename Iterator, typename Transformer> 
    class Transform<Derived, Iterator, Transformer, std::random_access_iterator_tag>
    : public Transform<Derived, Iterator, Transformer, std::bidirectional_iterator_tag>
    {
        using Base = Transform<Derived, Iterator, Transformer, std::bidirectional_iterator_tag>;

        public:
            template <typename It>
            explicit Transform(It it, Transformer transform) 
            : Base(it, transform) 
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

    template <typename Derived, typename Iterator, typename Transformer> 
    Derived operator+(typename Derived::difference_type n, const Transform<Derived, Iterator, Transformer, std::random_access_iterator_tag> & it)
    {
        return it + n;
    }
} 

    template <typename Iterator, typename Functor, bool dereference>
    class Transform 
    : public detail::Transform<Transform<Iterator, Functor, dereference>, Iterator, detail::Transformer<Functor, dereference>, typename std::iterator_traits<Iterator>::iterator_category>
    {
        using Transformer = detail::Transformer<Functor, dereference>;
        using Base = detail::Transform<Transform<Iterator, Functor, dereference>, Iterator, Transformer, typename std::iterator_traits<Iterator>::iterator_category>;

    public:
        Transform()
        : Base(Iterator(), Transformer())
        {

        }
        
        template <typename It>
        explicit Transform(It it, Functor f = Functor())
        : Base(it, Transformer(f))
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

