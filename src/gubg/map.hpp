#ifndef HEADER_gubg_map_hpp_ALREADY_INCLUDED
#define HEADER_gubg_map_hpp_ALREADY_INCLUDED

#include <gubg/Convert.hpp>

#include <map>
#include <optional>

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

    template <typename Map, typename Key>
    const typename Map::mapped_type *get(const Map &map, const Key &key)
    {
        const auto it = map.find(key);
        if (it == map.end())
            return nullptr;
        return &it->second;
    }
    template <typename Map, typename Key>
    typename Map::mapped_type *get(Map &map, const Key &key)
    {
        const auto it = map.find(key);
        if (it == map.end())
            return nullptr;
        return &it->second;
    }

    template <typename Map, typename Key, typename Ftor>
    void with_value(const Map &map, const Key &key, Ftor &&ftor)
    {
        auto it = map.find(key);
        if (it != map.end())
            ftor(it->second);
    }
    template <typename Map, typename Key, typename Ftor>
    void with_value(Map &map, const Key &key, Ftor &&ftor)
    {
        auto it = map.find(key);
        if (it != map.end())
            ftor(it->second);
    }

} 

#endif
