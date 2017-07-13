#ifndef HEADER_gubg_array_Pool_hpp_ALREADY_INCLUDED
#define HEADER_gubg_array_Pool_hpp_ALREADY_INCLUDED

#include "gubg/debug.hpp"
#include <memory>

namespace gubg { namespace array { 

    namespace list { 
        class Header
        {
        public:
            void remove()
            {
                if (prev_)
                    prev_->next_ = next_;
                if (next_)
                    next_->prev_ = prev_;
            }
        private:
            Header *prev_ = nullptr;
            Header *next_ = nullptr;
        };

        class Element
        {
        public:
            template <typename Data>
            static Element *create(size_t size)
            {
                S("");
                auto s = sizeof(Header) + Data::size_of(size);
                L(C(s));
                void *raw = std::malloc(s);
                L(C(raw));
                auto el = (Element*)raw;
                L(C(el));
                new (&el->header_) Header();
                Data &data = *(Data*)(&el->align_);
                Data::ctor(data, size);
                return el;
            }
            template <typename Data>
            static void destroy(Element &el)
            {
                S("");
                {
                el.header_.remove();
                Data &data = *(Data*)&el.align_;
                Data::dtor(data);
                auto hdr = (Header*)&data;
                --hdr;
                L(C(hdr));
                std::free(hdr);
                }
            }
        private:
            Header header_;
            void *align_;
        };
    }

    namespace array { 
        struct Header
        {
            size_t size = 0;
            size_t capacity = 0;
        };
    } 
    template <typename T>
    class Array
    {
    public:
        using Self = Array<T>;

        static size_t size_of(size_t size)
        {
            return sizeof(array::Header) + size*sizeof(T);
        }
        static void ctor(Self &self, size_t size)
        {
            S("");
            L(C(size));
            self.header_.size = size;
            self.header_.capacity = size;
            auto el = (T*)&self.align_;
            for (auto end = el+size; el != end; ++el)
            {
                L(C(el));
                new (el) T;
            }
        }
        static void dtor(Self &self)
        {
            S("");
            auto el = (T*)&self.align_;
            L(C(self.header_.size));
            for (auto end = el+self.header_.size; el != end; ++el)
            {
                L(C(el));
                el->~T();
            }
        }

    private:
        array::Header header_;
        void *align_;
    };

} } 

#endif
