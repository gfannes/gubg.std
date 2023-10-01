#ifndef HEADER_gubg_Signaled_hpp_ALREAD_INCLUDED
#define HEADER_gubg_Signaled_hpp_ALREAD_INCLUDED

namespace gubg {

    template<typename T, typename Flag = bool>
    class Signaled
    {
    public:
        using Self = Signaled<T, Flag>;

        const Flag &flag() const { return flag_; }
        operator bool() const { return flag(); }

        Self &set(Flag flag)
        {
            flag_ = flag;
            return *this;
        }

        const T &cref() const { return v_; }
        T &ref() { return v_; }

        const T *operator->() const { return &v_; }
        T *operator->() { return &v_; }

        const T &operator*() const { return v_; }
        T &operator*() { return v_; }

    private:
        T v_{};
        Flag flag_{};
    };

} // namespace gubg

#endif
