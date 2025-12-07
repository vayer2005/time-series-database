#pragma once
#include <string>
#include <vector>
#include <cstdint>

// Block Metadata (meta.json structure)
// Contains high-level information about the block

struct BlockMetadata {
    uint16_t version;
    std::string block_id;
    uint64_t start_time;
    uint64_t end_time;
    uint64_t duration_seconds;
    uint32_t num_series;
    uint64_t num_samples;
    uint64_t compressed_size;
    std::vector<std::string> metrics;
    
    // TODO: Serialize to JSON
    std::string toJSON() const;
    
    // TODO: Deserialize from JSON
    static BlockMetadata fromJSON(const std::string& json);
    
    // TODO: Write to file
    void writeToFile(const std::string& filepath) const;
    
    // TODO: Read from file
    static BlockMetadata readFromFile(const std::string& filepath);
};

