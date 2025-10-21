#pragma once
#include <string>
#include <filesystem>
#include <chrono>

namespace Utils {
    inline long long getFileSize(const std::string& path) {
        try {
            return std::filesystem::file_size(path);
        } catch (...) {
            return -1;
        }
    }

    class Timer {
    public:
        Timer() { start = std::chrono::high_resolution_clock::now(); }
        double stop() {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            return elapsed.count();
        }
    private:
        std::chrono::high_resolution_clock::time_point start;
    };
}