# 🗜️ File Compressor — Huffman & LZW Based Compression Suite

### 🚀 A C++ Project for Efficient File Compression and Decompression

---

## 📖 Introduction

**File Compressor** is a modular C++ project designed to compress and decompress files using **Huffman Encoding** and **LZW (Lempel–Ziv–Welch)** algorithms.
The project emphasizes performance, scalability, and extensibility — developed in **VS Code** with CMake integration and soon to include a modern **Qt GUI interface** for desktop users.

The core architecture separates:

* **Backend Logic** (compression algorithms)
* **Frontend Layer** (CLI now, GUI later)
* **Build Management** (via CMake)

This ensures that the backend can be reused across multiple frontends — terminal, GUI, or even web-based clients.

---

## 📂 Contents

```
FILE_COMPRESSOR/
│
├── include/          # Header files
│   ├── Huffman.hpp
│   ├── LZW.hpp
│   ├── Utils.hpp
│
├── src/              # Source implementation
│   ├── Huffman.cpp
│   ├── LZW.cpp
│   ├── main.cpp
│
├── tests/            # (Optional) Test inputs and results
│
├── build/            # Build artifacts (ignored by Git)
│
├── .gitignore
├── CMakeLists.txt
└── README.md
```

---

## ⚙️ Build Instructions

### 🧩 Prerequisites

* **C++17 or later**
* **CMake 3.16+**
* **MinGW / MSVC / LLVM toolchain**
* Optional: **Qt 6.7.3+** (for GUI build — future phase)

### 🧱 Build (CLI Mode)

Open a terminal inside the project root and run:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

This will generate:

```
compress.exe   → command-line compressor executable
```

💻 **Usage**
The CLI supports both Huffman and LZW algorithms for compression and decompression.

▶️ **Example Commands**

**Huffman Compression**

```bash
./compress -algo huffman -mode compress input.txt output.huff
```

**Huffman Decompression**

```bash
./compress -algo huffman -mode decompress output.huff restored.txt
```

**LZW Compression**

```bash
./compress -algo lzw -mode compress input.txt output.lzw
```

**LZW Decompression**

```bash
./compress -algo lzw -mode decompress output.lzw restored.txt
```

---

## 🧠 Architecture Overview

### 🧩 Core Components

| Module           | Purpose                                                                   |
| ---------------- | ------------------------------------------------------------------------- |
| Huffman.cpp/.hpp | Implements Huffman Tree, frequency mapping, bitstream encoding/decoding.  |
| LZW.cpp/.hpp     | Implements dictionary-based compression using LZW algorithm.              |
| Utils.hpp        | Handles byte/bit I/O utilities for compact storage.                       |
| main.cpp         | CLI driver — parses arguments, triggers chosen algorithm, manages output. |

### 🧵 Multithreading Extension (Prototype Ready)

The backend design already supports future integration of multi-threaded compression for large files.
A planned module **CompressionWorker** (using `std::thread` / `QThread`) will parallelize data chunking, allowing faster compression on multi-core CPUs.

---

## 🎨 Future Roadmap

| Feature                        | Description                                                                                     | Status                 |
| ------------------------------ | ----------------------------------------------------------------------------------------------- | ---------------------- |
| 🖥️ Qt GUI Interface           | A full-fledged desktop UI using Qt 6, with file browser, progress bar, and threaded operations. | ⏳ Planned              |
| ⚡ Multi-threaded Backend       | Concurrent chunk-level compression for large datasets.                                          | 🧩 Under design        |
| 🔒 File Integrity Verification | Optional hash verification post decompression.                                                  | 🔜 Next iteration      |
| 🧰 Custom File Extensions      | Introduce `.fcomp` unified extension for all compressed outputs.                                | 🚧 Proposed            |
| 📈 Compression Stats           | Display compression ratio, size difference, and time taken.                                     | ✅ CLI-ready, GUI later |

### 🧭 Future GUI Hypothesis

The upcoming Qt interface will introduce:

* Drag-and-drop compression
* Real-time progress bars
* Multi-threaded worker threads (`CompressionWorker`)
* Status logging and error handling in UI
* Dual mode: Compress / Decompress

**Preview Layout (planned)**

```
+----------------------------------------+
| File Path: [Browse...]                 |
|----------------------------------------|
| [ Compress ]   [ Decompress ]          |
|----------------------------------------|
| Progress: [██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒] 75% |
|----------------------------------------|
| Log Output:                            |
| > Compression started...               |
| > File saved as example.huff           |
+----------------------------------------+
```

---

## 🧑‍💻 Author

**Yash**
Programmer | Systems Developer | Passionate about clean architecture and performance-driven design.

---

## 🌐 License

**MIT License** — Open for personal and academic use.
Feel free to fork, modify, and extend the project.

---

## 🤝 Getting Started for Contributors

If you’d like to contribute:

```bash
# Clone repository
git clone https://github.com/<your-username>/File_Compressor.git

# Navigate to project
cd File_Compressor

# Create build directory
mkdir build && cd build

# Build
cmake ..
cmake --build .

# Run
./compress -algo huffman -mode compress input.txt output.huff
```

Pull requests and feature discussions are always welcome 🚀
