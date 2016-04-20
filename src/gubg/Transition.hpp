#ifndef HEADER_gubg_Transition_hpp_ALREADY_INCLUDED
#define HEADER_gubg_Transition_hpp_ALREADY_INCLUDED

#include <array>

namespace gubg { 

    template <typename T>
        class Transition
        {
            private:
                using Self = Transition<T>;

            public:
                bool same() const {return data_[0] == data_[1];}
                bool changed() const {return !same();}

                const T &previous() const {return data_[1-cur_];}
                T &current() {return data_[cur_];}

                Self &push()
                {
                    cur_ = 1-cur_;
                    current() = T{};
                    return *this;
                }
                Self &push(const T &v)
                {
                    cur_ = 1-cur_;
                    current() = v;
                    return *this;
                }

            private:
                using Data = std::array<T, 2>;
                Data data_{};
                size_t cur_ = 0;
        };

} 

#endif
