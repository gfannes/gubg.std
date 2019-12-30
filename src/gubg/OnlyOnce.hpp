#ifndef HEADER_gubg_OnlyOnce_hpp_ALREADY_INCLUDED
#define HEADER_gubg_OnlyOnce_hpp_ALREADY_INCLUDED

namespace gubg
{
    class OnlyOnce
    {
    public:
        OnlyOnce() {}
        OnlyOnce(bool first_time): first_time_(first_time) {}

        bool operator()()
        {
            const bool res = first_time_;
            first_time_ = false;
            return res;
        }

        bool check() const {return first_time_;}

        void reset() {first_time_ = true;}

    private:
        bool first_time_ = true;
    };
}

#endif
