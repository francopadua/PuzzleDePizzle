#pragma once

#include <cstdint>
#include <vector>

struct LevelResultData
{
    int slice{};
    float starOpacity{};
    float percent{};
    std::uint32_t salt{};
};

class SaveSystem
{
public:
    static bool Save(const char* filename, const std::vector<LevelResultData>& data);
    static bool Load(const char* filename, std::vector<LevelResultData>& data);
};
