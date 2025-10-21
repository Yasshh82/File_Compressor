#include "Huffman.hpp"
#include <fstream>
#include <iostream>
#include <bitset>
#include <chrono>
#include <filesystem>

void Huffman::writeBitstream(const std::string& bits, const std::string& outputFile, const std::unordered_map<char, int>& freqMap) {
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open output file: " + outputFile);
    }

    // --- HEADER ---
    // 1. Write number of unique symbols
    int uniqueCount = freqMap.size();
    out.write(reinterpret_cast<const char*>(&uniqueCount), sizeof(uniqueCount));

    // 2. Write (char, freq) pairs to reconstruct tree later
    for (auto& p : freqMap) {
        out.write(&p.first, sizeof(char));
        out.write(reinterpret_cast<const char*>(&p.second), sizeof(int));
    }

    // --- COMPRESSED DATA ---
    unsigned char buffer = 0;
    int bitCount = 0;
    for (char b : bits) {
        buffer <<= 1;
        if (b == '1') buffer |= 1;
        bitCount++;
        if (bitCount == 8) {
            out.write(reinterpret_cast<char*>(&buffer), 1);
            buffer = 0;
            bitCount = 0;
        }
    }

    // Write remaining bits (if not aligned to 8)
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.write(reinterpret_cast<char*>(&buffer), 1);
    }

    out.close();
}

std::unordered_map<char, int> Huffman::buildFrequencyTable(const std::string& inputFile) {
    std::unordered_map<char, int> freqMap;
    std::ifstream in(inputFile, std::ios::binary);
    if(!in.is_open()){
        throw std::runtime_error("Could not open input file: " + inputFile);
    }

    char c;
    while (in.get(c)) {
        freqMap[c]++;
    }
    return freqMap;
}

std::shared_ptr<Huffman::Node> Huffman::buildTree(const std::unordered_map<char, int>& freqMap) {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Compare> pq;

    for (auto& pair : freqMap) {
        pq.push(std::make_shared<Node>(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto parent = std::make_shared<Node>(left, right);
        pq.push(parent);
    }
    return pq.empty() ? nullptr : pq.top();
}
void Huffman::buildEncodingTable(std::shared_ptr<Node> root, const std::string& str) {
    if (!root) return;

    if (!root->left && !root->right) {
        encodingTable[root->ch] = str.empty() ? "0" : str; // Handle single character case
    }
    buildEncodingTable(root->left, str + "0");
    buildEncodingTable(root->right, str + "1");
}

void Huffman::compress(const std::string& inputFile, const std::string& outputFile) {
    auto start = std::chrono::high_resolution_clock::now();

    auto freqMap = buildFrequencyTable(inputFile);
    std::cout << "DEBUG: Frequency map size = " << freqMap.size() << std::endl;

    auto root = buildTree(freqMap);
    buildEncodingTable(root, "");
    
    std::ifstream in(inputFile, std::ios::binary);
    std::string bits;
    char c;
    while (in.get(c)) {
        bits += encodingTable[c];
    }
    in.close();

    std::cout << "DEBUG: Bits length = " << bits.size() << std::endl;
    std::cout << "DEBUG: Attempting to write " << outputFile << std::endl;

    writeBitstream(bits, outputFile, freqMap);

    auto end = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration<double>(end - start).count();
    auto inSize = std::filesystem::file_size(inputFile);
    auto outSize = std::filesystem::file_size(outputFile);
    double ratio = (1.0 - (double)outSize / inSize) * 100.0;
    std::cout << "✅ [Huffman] Compression complete.\n";
    std::cout << "Input: " << inSize << " bytes | Output: " << outSize << " bytes | ";
    std::cout << "Ratio: " << ratio << "% | Time: " << timeTaken << "s\n"; 
}

void Huffman::decompress(const std::string& inputFile, const std::string& outputFile) {
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream in(inputFile, std::ios::binary);
    if(!in.is_open()){
        throw std::runtime_error("Could not open input file: " + inputFile);
    }
    // --- READ HEADER ---
    int uniqueCount;
    in.read(reinterpret_cast<char*>(&uniqueCount), sizeof(uniqueCount));
    std::unordered_map<char, int> freqMap;
    for (int i = 0; i < uniqueCount; ++i) {
        char ch;
        int freq;
        in.read(&ch, sizeof(char));
        in.read(reinterpret_cast<char*>(&freq), sizeof(int));
        freqMap[ch] = freq;
    }

    // --- REBUILD TREE ---
    std::shared_ptr<Node> root = buildTree(freqMap);

    // --- READ BITSTREAM ---
    std::string bits;
    char byte;
    while (in.read(&byte, 1)) {
        for(int i=7; i>=0; i--){
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    in.close();

    // --- DECODE ---
    std::ofstream out(outputFile);
    if(!out.is_open()){
        throw std::runtime_error("Could not open output file: " + outputFile);
    }

    std::shared_ptr<Node> current = root;
    for (char bit : bits) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (current->left == nullptr && current->right == nullptr) {
            out.put(current->ch);
            current = root;
        }
    }
    out.close();

    auto end = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration<double>(end - start).count();

    auto inSize = std::filesystem::file_size(inputFile);
    auto outSize = std::filesystem::file_size(outputFile);
    std::cout << "✅ [Huffman] Decompression complete.\n";
    std::cout << "Input: " << inSize << " bytes | Output: " << outSize << " bytes | ";
    std::cout << "Time: " << timeTaken << "s\n";
}