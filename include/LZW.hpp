#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class LZW{
public:
    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);
};