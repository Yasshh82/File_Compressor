#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // Min-heap based on frequency
    }
};

class Huffman {
public:
    Huffman() = default;
    ~Huffman();

    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    HuffmanNode* root = nullptr;

    void buildTree(const std::unordered_map<char, int>& freq);
    void freeTree(HuffmanNode* node);

    void generateCodes(HuffmanNode* node, const std::string& prefix, 
                       std::unordered_map<char, std::string>& codeTable);

    std::string readFile(const std::string& filename);
    void writeFile(const std::string& filename, const std::string& data);
};