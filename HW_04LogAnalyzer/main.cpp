#include "LogAnalyzer.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <string> 

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <log_directory>\n";
        return 1;
    }

    std::string folderPath = argv[1];
    LogAnalyzer analyzer;
    std::vector<std::string> keywords = {"[ERROR]", "[WARNING]", "[INFO]", "[DEBUG]", "[TRACE]"};
    std::vector<std::thread> threads;

    std::cout << "Analyzing folder: " << folderPath << "\n\n";

    // TODO: Use std::filesystem to iterate through all files in the folder.
    for(const auto& file: fs::directory_iterator(folderPath)){

        threads.emplace_back([&analyzer, &keywords, file]() {
            if(file.path().extension() == ".log"){
                analyzer.analyzeFile(file.path().string(), keywords);
            }
        });
    }
    // TODO: Join all threads after launching.
    for (auto& t : threads) {
    t.join();
    }

    analyzer.printSummary();

    return 0;
}
