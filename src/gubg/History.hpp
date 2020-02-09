#ifndef HEADER_gubg_History_hpp_ALREADY_INCLUDED
#define HEADER_gubg_History_hpp_ALREADY_INCLUDED

#include <vector>
#include <cassert>

namespace gubg { 

    //A contiguous-memory delayline with runtime size
    //T should be easy to copy, there will always be 2 copies in existance for a given index
    template <typename T>
    class History
    {
    public:
        using Self = History<T>;

        History() {}
        History(const Self &rhs)
        {
            data_ = rhs.data_;
            size_ = rhs.size_;
            if (size_ == 0)
                begin_ = nullptr;
            else
                //We cannot simply copy begin_, it is relative wrt data_
                begin_ = data_.data()+(rhs.begin_-rhs.data_.data());
        }
        History(std::size_t size)
        {
            resize(size);
        }
        Self &operator=(const Self &rhs)
        {
            if (&rhs != this)
            {
                data_ = rhs.data_;
                size_ = rhs.size_;
                if (size_ == 0)
                    begin_ = nullptr;
                else
                    //We cannot simply copy begin_, it is relative wrt data_
                    begin_ = data_.data()+(rhs.begin_-rhs.data_.data());
            }
            return *this;
        }

        bool empty() const {return size_ == 0;}
        std::size_t size() const {return size_;}

        void resize(std::size_t size)
        {
            //Copy all data to the front of data_
            for (auto ix = 0u; ix < size_; ++ix)
                data_[ix] = begin_[ix];
            //Clear all the rest from data_
            data_.resize(size_);
            data_.resize(size);
            //Resize data_ to the proper size
            data_.resize(2*size);
            size_ = size;
            //Make sure the duplicated elements are present
            for (auto ix = 0u; ix < size_; ++ix)
                data_[ix+size_] = data_[ix];
            //Set begin_ to the start of data_
            begin_ = data_.data();
        }

        //Writing via operator[]() is not allowed as this need to write in 2 locations to keep the data_ consistent.
        //All the size() elements are placed in contiguous memory.
        const T &operator[](std::size_t ix) const
        {
            assert(ix < size_);
            return begin_[ix];
        }

        const T &front() const
        {
            assert(size_ > 0);
            return begin_[0];
        }
        const T &back() const
        {
            assert(size_ > 0);
            return begin_[size_-1];
        }

        void set(std::size_t ix, const T &v)
        {
            assert(ix < size_);
            begin_[ix] = v;
            begin_[ix+size_] = v;
        }

        void push_pop(const T &v)
        {
            if (empty())
                return;
            if (begin_ == data_.data())
                begin_ += size_-1;
            else
                --begin_;
            set(0, v);
        }

    private:
        std::vector<T> data_;
        std::size_t size_ = 0;
        T *begin_ = nullptr;
    };

} 

#endif
