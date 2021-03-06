#ifndef HEADER_gubg_time_DayTime_hpp_ALREADY_INCLUDED
#define HEADER_gubg_time_DayTime_hpp_ALREADY_INCLUDED

#include "gubg/Strange.hpp"
#include "gubg/mss.hpp"
#include <string>
#include <ostream>
#include <chrono>

namespace gubg { namespace time { 
    class DayTime
    {
        private:
            constexpr static const char *logns = nullptr;//"DayTime";
            static const unsigned int sec_per_day = 86400;
            static const unsigned int sec_per_hour = 3600;
            static const unsigned int sec_per_minute = 60;

        public:
            using Seconds = std::chrono::seconds;

            DayTime(){}
            DayTime(unsigned int hour, unsigned int min = 0, unsigned int sec = 0): seconds_(hour*sec_per_hour + min*sec_per_minute + sec){}
            static bool from_armin(DayTime &dt, unsigned int armin)
            {
                MSS_BEGIN(bool);
                MSS(armin < sec_per_day);
                const unsigned int hours = armin/100;
                const unsigned int minutes = armin%100;
                dt.seconds_ = Seconds(hours*sec_per_hour + minutes*sec_per_minute);
                MSS_END();
            }
            static bool from_armin(DayTime &dt, const std::string &str)
            {
                MSS_BEGIN(bool, logns);
                L(str);
                gubg::Strange strange(str);
                unsigned int armin;
                MSS(strange.pop_decimal(armin));
                MSS(from_armin(dt, armin));
                MSS_END();
            }
            bool from_armin(unsigned int armin)
            {
                return DayTime::from_armin(*this, armin);
            }
            bool from_armin(const std::string &str)
            {
                return DayTime::from_armin(*this, str);
            }

            bool operator==(const DayTime &rhs) const {return seconds_ == rhs.seconds_;}
            bool operator!=(const DayTime &rhs) const {return seconds_ != rhs.seconds_;}

            bool operator<(const DayTime &rhs)  const {return seconds_ <  rhs.seconds_;}
            bool operator<=(const DayTime &rhs) const {return seconds_ <= rhs.seconds_;}
            bool operator>(const DayTime &rhs)  const {return seconds_ >  rhs.seconds_;}
            bool operator>=(const DayTime &rhs) const {return seconds_ >= rhs.seconds_;}

            Seconds operator-(const DayTime &rhs) const {return seconds_ - rhs.seconds_;}

            DayTime &operator+=(const Seconds &duration)
            {
                seconds_ += duration;
                return *this;
            }

            Seconds duration() const {return seconds_;}

            unsigned int hours() const {return seconds_.count()/sec_per_hour;}
            unsigned int minutes() const {return (seconds_.count()%sec_per_hour)/sec_per_minute;}
            unsigned int seconds() const {return seconds_.count()%sec_per_minute;}

            void stream(std::ostream &os) const
            {
                const auto flags = os.flags();
                os << hours() << ':' << std::setfill('0') << std::setw(2) << minutes() << ':' << std::setw(2) << seconds();
                os.flags(flags);
            }
        private:
            Seconds seconds_{0};
    };
    inline std::ostream &operator<<(std::ostream &os, const DayTime &dt)
    {
        dt.stream(os);
        return os;
    }
} } 

#endif
