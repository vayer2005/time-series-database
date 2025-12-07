#pragma once
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

// Per-Block Index Structure (index.bin)
// Purpose: Fast lookup of series within a block
// 
// Structure:
// - Index Header (Magic: "INDX", Num entries)
// - Index Entry 1 (Series ID, Metric hash, File offset, Num samples)
// - Index Entry 2
// - ...
// Sorted by series ID for binary search!

struct IndexHeader {
    char magic[4];          // "INDX"
    uint32_t num_entries;   // Number of index entries
    uint32_t reserved[2];   // Reserved for future use
} __attribute__((packed));

struct IndexEntry {
    uint64_t series_id;         // Series identifier
    uint64_t metric_hash;       // Hash of metric name for fast lookup
    uint64_t file_offset;       // Offset in samples.bin
    uint32_t num_samples;       // Number of samples in this series
    uint32_t reserved;          // Reserved for future use
} __attribute__((packed));

class BlockIndex {
public:
    BlockIndex(const std::string& index_path);
    ~BlockIndex();
    
    // TODO: Add an entry to the index
    void addEntry(uint64_t series_id, uint64_t metric_hash, 
                  uint64_t file_offset, uint32_t num_samples);
    
    // TODO: Find series by ID (binary search)
    IndexEntry findSeries(uint64_t series_id);
    
    // TODO: Get all series IDs
    std::vector<uint64_t> getAllSeriesIDs();
    
    // TODO: Write index to file
    void writeToFile();
    
    // TODO: Load index from file
    void loadFromFile();
    
private:
    std::string index_path_;
    std::vector<IndexEntry> entries_;
    
    // TODO: Sort entries by series_id
    void sortEntries();
};

