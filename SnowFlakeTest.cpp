#include "SnowFlake.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <thread>
#include <unordered_set>
#include <vector>

using game_uuid_vetcor = std::vector<game::GameUuid>;
using game_uuid_set = std::unordered_set<game::GameUuid, game::uuid_hash, game::uuid_equal>;

game::SnowFlake t_sf;
game_uuid_vetcor first_v;
game_uuid_vetcor second_v;
game_uuid_vetcor third_v;
static const std::size_t kTestSize = 1000000;

void EmplaceToVector(game_uuid_vetcor& v)
{
    for (std::size_t i = 0; i < kTestSize; ++i)
    {
        v.emplace_back(t_sf.Generate());
    }
}

void GenerateThread1()
{
    EmplaceToVector(first_v); 
}

void GenerateThread2()
{
    EmplaceToVector(second_v);
}

void GenerateThread3()
{
    EmplaceToVector(third_v);
}

void TestNormal()
{
    game::SnowFlake sf;
    time_t t = sf.GetNow();
    std::cout << t << std::endl;
    game::GameUuid id = sf.Generate();
    std::cout << std::get<1>(id) << std::endl;
}

void PutVectorInToSet(game_uuid_set& s, game_uuid_vetcor& v)
{
    for (auto& it : v)
    {
        s.emplace(it);
    }
}

int32_t main()
{
    TestNormal();
    game_uuid_set guid_set;
    
    auto first_cb = std::bind(GenerateThread1);
    auto second_cb = std::bind(GenerateThread2);
    auto third_cb = std::bind(GenerateThread3);
    std::thread first_thread(first_cb);
    std::thread second_thread(second_cb);
    std::thread third_thread(third_cb);

    first_thread.join();                
    second_thread.join();   
    third_thread.join();

    PutVectorInToSet(guid_set, first_v);
    PutVectorInToSet(guid_set, second_v);
    PutVectorInToSet(guid_set, third_v);

    assert(guid_set.size() == (first_v.size() + second_v.size() + third_v.size()));

    return 0;
}