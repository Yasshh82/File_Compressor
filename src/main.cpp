#include <iostream>
#include <string>
#include "Huffman.hpp"
#include "LZW.hpp"

int main(int argc, char** argv){
    if(argc < 7){
        std::cout<< "Usage: ./compress -algo [huffman|lzw] -mode [compress|decompress] <input> <output>\n";
        return 0;
    }

    std::string algo = argv[2];
    std::string mode = argv[4];
    std::string inputFile = argv[5];
    std::string outputFile = argv[6];

    if(algo == "huffman"){
        Huffman h;
        if(mode == "compress"){
            h.compress(inputFile, outputFile);
        } 
        else if(mode == "decompress"){
            h.decompress(inputFile, outputFile);
        } 
        else {
            std::cerr<<"Invalid mode.\n";
        }
    }
    else if(algo == "lzw"){
        LZW l;
        if(mode == "compress"){
            l.compress(inputFile, outputFile);
        } 
        else if(mode == "decompress"){
            l.decompress(inputFile, outputFile);
        } 
        else {
            std::cerr<<"Invalid mode.\n";
        }
    } 
    return 0;
}