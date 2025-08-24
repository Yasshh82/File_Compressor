#include <iostream>
#include <string>

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Compression Tool (bootstrap)\n"
                  << "Usage (coming next): ./compress -algo [huffman|lzw] -mode [compress|decompress] <input> <output>\n";
        return 0;
    }

    std::cout << "Args received. Full functionality lands in step 2.\n";
    return 0;
}