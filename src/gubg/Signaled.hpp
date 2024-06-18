#ifndef HEADER_gubg_Signaled_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Signaled_hpp_ALREADY_INCLUDED

namespace gubg {

    namespace signaled {
        // Can be extended by the user
        template<typename Flag>
        struct DefaultFlag
        {
            static constexpr Flag Value{};
        };
    } // namespace signaled

    // Represents an object of type T, together with a flag of type Flag (default zero-initialized).
    // The object is always present and valid, regardless of the value of the flag.
    template<typename T, typename Flag = bool, Flag DefaultFlag = signaled::DefaultFlag<Flag>::Value>
    class Signaled
    {
    public:
        using Self = Signaled<T, Flag, DefaultFlag>;

        const Flag &flag() const { return flag_; }
        operator Flag() const { return flag(); }

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
        Flag flag_ = DefaultFlag;
    };

} // namespace gubg

#endif
