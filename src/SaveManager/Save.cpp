#include "Save.h"

#include <fstream>
#include <cstring>
#include <cstdio>
#include <raylib.h>

// ============================================================
// Internal constants (not visible outside this file)
// ============================================================

constexpr int SAVE_VERSION = 1;

constexpr uint32_t HASH_SEED = 0x030301;

constexpr uint32_t HASH_MUL1 = 31;
constexpr uint32_t HASH_MUL2 = 17;
constexpr uint32_t HASH_MUL3 = 13;

constexpr int HASH_SHIFT_L = 5;
constexpr int HASH_SHIFT_R = 27;

constexpr int KEY_SHIFT_L = 7;
constexpr int KEY_SHIFT_R = 9;

constexpr char SAVE_MAGIC[4] = { 'V','F','V','P' };

constexpr uint32_t XOR_FACTOR1 = 0xB0B0B0B0;
constexpr uint32_t XOR_FACTOR2 = 0x0B0B0B0B;

constexpr uint32_t GOLDEN_RATIO_HASH = 0x9E3779B9;
constexpr uint32_t MAX_RANGE = 0x7FFFFFFF;


// ============================================================
// Internal helper functions
// ============================================================

static uint32_t GenerateKey(uint32_t checksum)
{
    uint32_t key = checksum ^ XOR_FACTOR1;

    key ^= (key << KEY_SHIFT_L);
    key ^= (key >> KEY_SHIFT_R);
    key ^= XOR_FACTOR2;

    return key;
}

static void ObfuscateRecord(LevelResultData& d, uint32_t baseKey, int index)
{
    uint32_t recordKey = baseKey ^ d.salt ^ (index * GOLDEN_RATIO_HASH);

    auto* bytes = reinterpret_cast<unsigned char*>(&d);

    constexpr size_t DATA_SIZE = sizeof(LevelResultData) - sizeof(uint32_t);

    for (size_t i = 0; i < DATA_SIZE; ++i)
        bytes[i] ^= reinterpret_cast<unsigned char*>(&recordKey)[i % 4];
}

static uint32_t CalculateChecksum(const std::vector<LevelResultData>& data)
{
    uint32_t hash = HASH_SEED;

    for (const auto& d : data)
    {
        hash ^= d.slice * HASH_MUL1;
        hash ^= static_cast<int>(d.starOpacity * 1000) * HASH_MUL2;
        hash ^= static_cast<int>(d.percent * 1000) * HASH_MUL3;

        hash = (hash << HASH_SHIFT_L) | (hash >> HASH_SHIFT_R);
    }

    return hash;
}

const char* SaveSystem::GetSaveFile()
{
#if defined(_WIN32)
    return m_fileName;
#elif defined(PLATFORM_ANDROID)
    return GetAndroidWritablePath() + m_fileName;
#else
    return m_fileName;
#endif
}

// ============================================================
// Save
// ============================================================

bool SaveSystem::Save(const char* filename, const std::vector<LevelResultData>& data)
{
    std::string tempFile = std::string(filename) + ".tmp";

    std::ofstream file(tempFile, std::ios::binary);
    if (!file)
        return false;

    auto count = static_cast<int>(data.size());

    uint32_t checksum = CalculateChecksum(data);
    uint32_t key = GenerateKey(checksum);

    file.write(SAVE_MAGIC, sizeof(SAVE_MAGIC));
    file.write(reinterpret_cast<const char*>(&SAVE_VERSION), sizeof(SAVE_VERSION));
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (int i = 0; i < count; ++i)
    {
        LevelResultData d = data[i];

        d.salt = GetRandomValue(1, MAX_RANGE);

        ObfuscateRecord(d, key, i);

        file.write(reinterpret_cast<char*>(&d), sizeof(LevelResultData));
    }

    file.write(reinterpret_cast<char*>(&checksum), sizeof(checksum));

    file.close();

    if (!file.good())
        return false;

    std::remove(filename);

    if (std::rename(tempFile.c_str(), filename) != 0) {
        std::remove(tempFile.c_str());
        return false;
    }

    return true;
}


// ============================================================
// Load
// ============================================================

bool SaveSystem::Load(const char* filename, std::vector<LevelResultData>& data)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        return false;

    char magic[4];
    int version{};
    int count{};

    file.read(magic, sizeof(magic));

    if (std::memcmp(magic, SAVE_MAGIC, sizeof(SAVE_MAGIC)) != 0)
        return false;

    file.read(reinterpret_cast<char*>(&version), sizeof(version));

    if (version != SAVE_VERSION)
        return false;

    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    if (count <= 0 || count > 1000)
        return false;

    data.resize(count);

    for (int i = 0; i < count; ++i)
    {
        if (!file.read(reinterpret_cast<char*>(&data[i]), sizeof(LevelResultData)))
            return false;
    }

    uint32_t storedChecksum{}; 
    file.read(reinterpret_cast<char*>(&storedChecksum), sizeof(storedChecksum));

    uint32_t key = GenerateKey(storedChecksum);

    for (int i = 0; i < count; ++i)
        ObfuscateRecord(data[i], key, i);

    uint32_t actualChecksum = CalculateChecksum(data);

    if (actualChecksum != storedChecksum)
    {
        data.clear();
        return false;
    }

    return true;
}
