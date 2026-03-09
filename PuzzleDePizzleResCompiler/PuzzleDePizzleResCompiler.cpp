#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>

struct Header
{
    char magic[6];
    uint32_t version;
    uint32_t fileCount;
};

struct Entry
{
    char name[64];
    uint32_t offset;
    uint32_t size;
};

int main()
{
    std::vector<Entry> table;
    std::vector<std::vector<char>> files;

    std::string baseFolder = "ProtectedRes";

    for (auto& p : std::filesystem::recursive_directory_iterator(baseFolder))
    {
        if (!p.is_regular_file())
            continue;

        std::ifstream f(p.path(), std::ios::binary);

        if (!f)
        {
            std::cout << "Failed to open: " << p.path() << "\n";
            continue;
        }

        std::vector<char> data(
            (std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());

        Entry e{};
        std::string name = std::filesystem::relative(p.path(), baseFolder).string();

        std::replace(name.begin(), name.end(), '\\', '/');

        memset(e.name, 0, sizeof(e.name));
        memcpy(e.name, name.c_str(), std::min(name.size(), sizeof(e.name) - 1));

        e.size = (uint32_t)data.size();

        table.push_back(e);
        files.push_back(data);

        std::cout << "Packing: " << name << "\n";
    }

    if (table.empty())
    {
        std::cout << "No files found.\n";
        return 0;
    }

    uint32_t offset = sizeof(Header) + table.size() * sizeof(Entry);

    for (auto& e : table)
    {
        e.offset = offset;
        offset += e.size;
    }

    std::ofstream out("game.puzres", std::ios::binary);

    Header header{};
    memcpy(header.magic, "PUZRES", 6);
    header.version = 1;
    header.fileCount = (uint32_t)table.size();

    out.write((char*)&header, sizeof(header));

    for (auto& e : table)
        out.write((char*)&e, sizeof(e));

    for (auto& f : files)
        out.write(f.data(), f.size());

    std::cout << "\nResource file created: game.puzres\n";
    std::cout << "Total files: " << table.size() << "\n";

    return 0;
}
