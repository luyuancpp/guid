#ifndef GAME_GUID_H
#define GAME_GUID_H

#include <cstdint>
#include <tuple>

namespace game
{
using UiddHighType = uint64_t;
using UiddLowType = uint64_t; //
using GameGuid = std::tuple<UiddHighType, UiddLowType>;

struct guid_hash
{
    std::size_t operator() (const GameGuid& p) const {
        return std::hash<UiddHighType>{}(std::get<0>(p)) ^ std::hash<UiddLowType>{}(std::get<1>(p));
    }
};

struct guid_equal
{
    bool operator() (const GameGuid& first, const GameGuid& second) const {
        return std::get<0>(first) == std::get<0>(second) && 
               std::get<1>(first) == std::get<1>(second);
    }
};

}

#endif // !GAME_GUID_H
