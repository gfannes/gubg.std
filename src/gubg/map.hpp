#ifndef HEADER_gubg_map_hpp_ALREADY_INCLUDED
#define HEADER_gubg_map_hpp_ALREADY_INCLUDED

#include <gubg/Convert.hpp>
#include <map>

namespace gubg { 

    template <typename T, typename Map, typename Key>
    T value_or(const T &default_value, const Map &map, const Key &key)
    {
        const auto it = map.find(key);
        if (it == map.end())
            return default_value;

        T res;
        if (!convert(res, it->second))
            return default_value;

        return res;
    }

} 

#endif
