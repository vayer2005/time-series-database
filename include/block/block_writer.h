#pragma once
#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

// BlockWriter: Writes data to block files
// - Opens a new block file
// - Writes block header
// - Accumulates series data
// - Writes each series with its own header
// - Computes and writes checksums
// - Finalizes block with footer

class BlockWriter {
public:
    BlockWriter(const std::string& block_path);
    ~BlockWriter();
    
    // TODO: Open block for writing
    void open();
    
    // TODO: Write block header
    void writeHeader(uint64_t start_time, uint64_t end_time);
    
    // TODO: Write a series with header and compressed data
    void writeSeries(uint64_t series_id, const std::vector<uint8_t>& compressed_data);
    
    // TODO: Write block footer with checksums
    void writeFooter();
    
    // TODO: Close and finalize block
    void close();
    
private:
    std::string block_path_;
    std::ofstream file_;
    uint64_t current_offset_;
    uint32_t series_count_;
    
    // TODO: Calculate CRC32 checksum
    uint32_t calculateChecksum(const uint8_t* data, size_t length);
};

