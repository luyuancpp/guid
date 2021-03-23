#ifndef GAME_UUID_H
#define GAME_UUID_H

#include <cstdint>
#include <tuple>

namespace game
{
using UiddHighType = uint64_t;
using UiddLowType = uint64_t; //
using GameUuid = std::tuple<UiddHighType, UiddLowType>;

struct uuid_hash
{
    std::size_t operator() (const GameUuid& p) const {
        return std::hash<UiddHighType>{}(std::get<0>(p)) ^ std::hash<UiddLowType>{}(std::get<1>(p));
    }
};

struct uuid_equal
{
    bool operator() (const GameUuid& first, const GameUuid& second) const {
        return std::get<0>(first) == std::get<0>(second) && 
               std::get<1>(first) == std::get<1>(second);
    }
};

}

#endif // !GAME_UUID_H
