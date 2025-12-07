#pragma once
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include "block_header.h"
#include "block_footer.h"
#include "series_header.h"

// BlockReader: Reads data from block files
// - Verifies magic numbers
// - Validates checksums
// - Can seek to specific series using offsets
// - Decompresses series data on demand
// - Handles corrupted blocks gracefully

class BlockReader {
public:
    BlockReader(const std::string& block_path);
    ~BlockReader();
    
    // TODO: Open block for reading
    void open();
    
    // TODO: Read and verify block header
    BlockHeader readHeader();
    
    // TODO: Read block footer
    BlockFooter readFooter();
    
    // TODO: Read a specific series by ID
    std::vector<uint8_t> readSeries(uint64_t series_id);
    
    // TODO: Read series at a specific offset
    std::vector<uint8_t> readSeriesAt(uint64_t offset);
    
    // TODO: Verify block integrity
    bool verifyIntegrity();
    
    // TODO: Close block
    void close();
    
private:
    std::string block_path_;
    std::ifstream file_;
    BlockHeader header_;
    BlockFooter footer_;
    
    // TODO: Verify checksum
    bool verifyChecksum(const uint8_t* data, size_t length, uint32_t expected_crc);
};

