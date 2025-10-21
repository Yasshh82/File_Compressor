#include <LZW.hpp>
#include <fstream>
#include <iostream>
#include <chrono>
#include <filesystem>

void LZW::compress(const std::string& inputFile, const std::string& outputFile){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if(!in.is_open() || !out.is_open()){
        std::cerr<<"Error opening files.\n";
        return;
    }

    // Initialize dictionary with all single character
    std::unordered_map<std::string, int> dict;
    for(int i = 0; i < 256; i++){
        dict[std::string(1, char(i))] = i;
    }

    std::string w;
    char c;
    int code = 256;
    while(in.get(c)){
        std::string wc = w + c;
        if(dict.find(wc) != dict.end()){
            w = wc;
        } else {
            out.write(reinterpret_cast<const char*>(&dict[w]), sizeof(int));
            dict[wc] = code++;
            w = std::string(1, c);
        }
    }

    if(!w.empty()){
        out.write(reinterpret_cast<const char*>(&dict[w]), sizeof(int));
    }

    in.close();
    out.close();

    auto end = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration<double>(end - start).count();

    auto inSize = std::filesystem::file_size(inputFile);
    auto outSize = std::filesystem::file_size(outputFile);
    double ratio = (1.0 - (double)outSize / inSize) * 100.0;

    std::cout << "✅ [LZW] Compression complete.\n";
    std::cout << "Input: " << inSize << " bytes | Output: " << outSize << " bytes | ";
    std::cout << "Ratio: " << ratio << "% | Time: " << timeTaken << "s\n";
}

void LZW::decompress(const std::string& inputFile, const std::string& outputFile){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if(!in.is_open() || !out.is_open()){
        std::cerr<<"Error opening files.\n";
        return;
    }

    //Initialize reverse dictionary
    std::vector<std::string> dict(4096);
    for(int i = 0; i<256; i++){
        dict[i] = std::string(1, char(i));
    }

    int prevCode, currCode;
    in.read(reinterpret_cast<char*>(&prevCode), sizeof(int));
    std::string s = dict[prevCode];
    out << s;

    int code = 256;
    while(in.read(reinterpret_cast<char*>(&currCode), sizeof(int))){
        std::string entry;
        if(currCode < code){
            entry = dict[currCode];
        } else if(currCode == code){
            entry = dict[prevCode] + s[0];
        } else {
            break;
        }
        out << entry;
        dict[code++] = dict[prevCode] + entry[0];
        prevCode = currCode;
        s = entry;
    }

    in.close();
    out.close();

    auto end = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration<double>(end - start).count();

    auto inSize = std::filesystem::file_size(inputFile);
    auto outSize = std::filesystem::file_size(outputFile);

    std::cout << "✅ [LZW] Decompression complete.\n";
    std::cout << "Input: " << inSize << " bytes | Output: " << outSize << " bytes | ";
    std::cout << "Time: " << timeTaken << "s\n";
}