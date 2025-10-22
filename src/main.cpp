#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Huffman.hpp"
#include "LZW.hpp"

bool VERBOSE = false;

void printHelp()
{
    std::cout << "\n📘 FileCompressor CLI — Usage Guide\n";
    std::cout << "----------------------------------\n";
    std::cout << "Usage:\n";
    std::cout << "  ./compress -algo [huffman|lzw] -mode [compress|decompress] [options] <input> <output>\n\n";
    std::cout << "Options:\n";
    std::cout << "  --help            Show this help message and exit\n";
    std::cout << "  --verbose         Enable detailed logs\n";
    std::cout << "  --threads N       Number of threads (only for Huffman compression)\n\n";
    std::cout << "Examples:\n";
    std::cout << "  ./compress -algo huffman -mode compress input.txt output.bin\n";
    std::cout << "  ./compress -algo huffman -mode compress --threads 4 input.txt output.bin\n";
    std::cout << "  ./compress -algo lzw -mode decompress input.lzw output.txt\n";
    std::cout << "----------------------------------\n";
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printHelp();
        return 0;
    }

    std::vector<std::string> args(argv + 1, argv + argc);

    // handle --help
    if (std::find(args.begin(), args.end(), "--help") != args.end())
    {
        printHelp();
        return 0;
    }

    // handle --verbose
    if (std::find(args.begin(), args.end(), "--verbose") != args.end())
    {
        VERBOSE = true;
        std::cout << "🔍 Verbose mode enabled.\n";
    }

    // validate required args
    if (argc < 7)
    {
        std::cout << "Usage: ./compress -algo [huffman|lzw] -mode [compress|decompress] <input> <output>\n";
        return 0;
    }

    std::string algo = argv[2];
    std::string mode = argv[4];
    std::string inputFile = argv[5];
    std::string outputFile = argv[6];

    // Default thread count
    int threadCount = 1;

    // Find --threads flag
    for (int i = 1; i < argc - 1; ++i)
    {
        if (std::string(argv[i]) == "--threads")
        {
            try
            {
                threadCount = std::stoi(argv[i + 1]);
            }
            catch (...)
            {
                std::cerr << "Invalid thread count specified.\n";
                return 1;
            }
        }
    }

    if (algo == "huffman")
    {
        Huffman h;
        if (mode == "compress")
        {
            if (threadCount > 1)
            {
                std::cout << "🚀 Using " << threadCount << " threads for Huffman compression.\n";
                h.compressMultiThreaded(inputFile, outputFile, threadCount);
            }
            else
            {
                h.compress(inputFile, outputFile);
            }
        }
        else if (mode == "decompress")
        {
            h.decompress(inputFile, outputFile);
        }
        else
        {
            std::cerr << "Invalid mode.\n";
        }
    }
    else if (algo == "lzw")
    {
        LZW l;
        if (mode == "compress")
        {
            l.compress(inputFile, outputFile);
        }
        else if (mode == "decompress")
        {
            l.decompress(inputFile, outputFile);
        }
        else
        {
            std::cerr << "Invalid mode.\n";
        }
    }
    else
    {
        std::cerr << "Unsupported algorithm.\n";
    }
    return 0;
}