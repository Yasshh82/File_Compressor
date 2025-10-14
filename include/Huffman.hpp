#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <memory>

class Huffman {
public:
    void compress(const std::string& inputFile, const std::string& outputFile);
    void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    struct Node {
        char ch;
        int freq;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
        Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
    };
    struct Compare {
        bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
            return a->freq > b->freq;
        }
    };

    std::unordered_map<char, int> buildFrequencyTable(const std::string& inputFile);
    std::shared_ptr<Node> buildTree(const std::unordered_map<char, int>& freqMap);
    void buildEncodingTable(std::shared_ptr<Node> root, const std::string& str);

    std::unordered_map<char, std::string> encodingTable;

    void writeBitstream(const std::string& bits, const std::string& outputFile, const std::unordered_map<char, int>& freqMap);
};