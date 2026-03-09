#include "ResManager.h"
#include <iostream>
#include <cstring>

bool ResManager::Load(const std::string& filename)
{
    file.open(filename, std::ios::binary);

    if (!file)
    {
        std::cout << "Failed to open resource file\n";
        return false;
    }

    ResHeader header;

    file.read((char*)&header, sizeof(header));

    if (memcmp(header.magic, "PUZRES", 6) != 0)
    {
        std::cout << "Invalid resource file\n";
        return false;
    }

    for (uint32_t i = 0; i < header.fileCount; i++)
    {
        ResEntry e;
        file.read((char*)&e, sizeof(e));

        entries[e.name] = e;
    }

    std::cout << "Loaded resources: " << header.fileCount << "\n";

    return true;
}

std::vector<unsigned char> ResManager::Get(const std::string& name)
{
    if (entries.find(name) == entries.end())
    {
        std::cout << "Resource not found: " << name << "\n";
        return {};
    }

    ResEntry& e = entries[name];

    file.seekg(e.offset);

    std::vector<unsigned char> data(e.size);

    file.read((char*)data.data(), e.size);

    return data;
}
