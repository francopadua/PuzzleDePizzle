#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

struct ResEntry
{
    char name[64];
    uint32_t offset;
    uint32_t size;
};

struct ResHeader
{
    char magic[6];
    uint32_t version;
    uint32_t fileCount;
};

class ResManager
{
public:

    bool Load(const std::string& filename);

    std::vector<unsigned char> Get(const std::string& name);

private:

    std::ifstream file;
    std::unordered_map<std::string, ResEntry> entries;
};
