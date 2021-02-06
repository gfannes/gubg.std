#ifndef HEADER_gubg_time_Date_hpp_ALREADY_INCLUDED
#define HEADER_gubg_time_Date_hpp_ALREADY_INCLUDED

#include <ostream>
#include <string>
#include <string_view>
#include <charconv>
#include <tuple>

namespace gubg { namespace time { 
    class Date
    {
    public:
        unsigned int year = 0;
        unsigned int month = 0;
        unsigned int day = 0;

        Date(){}
        Date(unsigned int year, unsigned int month, unsigned int day): year(year), month(month), day(day){}
        Date(const std::string &str) { from(str); }

        static Date now()
        {
            Date d;
            return d;
        }

        bool operator==(const Date &rhs) const {return year==rhs.year && month==rhs.month && day==rhs.day;}
        bool operator!=(const Date &rhs) const {return !operator==(rhs);}
        bool operator<(const Date &rhs) const
        {
            using Tuple = std::tuple<unsigned int, unsigned int, unsigned int>;
            return Tuple{year, month, day} < Tuple{rhs.year, rhs.month, rhs.day};
        }

        void from(std::string_view sv)
        {
            auto pop = [&](auto &dst)
            {
                dst = 0;
                if (sv.empty())
                    return;
                if (auto ix = sv.find('-'); ix == sv.npos)
                {
                    std::from_chars(sv.data(), sv.data()+sv.size(), dst);
                    sv.remove_prefix(sv.size());
                }
                else
                {
                    std::from_chars(sv.data(), sv.data()+ix, dst);
                    sv.remove_prefix(ix+1);
                }
            };
            pop(year);
            pop(month);
            pop(day);
        }
        void from_chars(const char *b, const char *e) { from(std::string_view(b, e-b)); }

        void stream(std::ostream &os) const
        {
            os << year << '-' << month << '-' << day;
        }

    private:
    };

    inline std::ostream &operator<<(std::ostream &os, const Date &date)
    {
        date.stream(os);
        return os;
    }
} } 

#endif
