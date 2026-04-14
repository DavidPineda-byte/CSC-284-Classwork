#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <algorithm>

void LogAnalyzer::analyzeFile(const std::string& filename, const std::vector<std::string>& keywords) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::cout << "Processing: " << filename << std::endl;

    std::string line;

    while (std::getline(file, line)) {
        for (const auto& keyword : keywords) {
            if (line.find(keyword) != std::string::npos) {
                std::lock_guard<std::mutex> lock(countMutex);
                ++keywordCounts[keyword];
            }
        }
    }
}

void LogAnalyzer::printSummary() const {
    std::cout << "\n--- Keyword Summary ---\n";

    // TODO: Use std::for_each and a lambda to print keyword counts.
    for_each(keywordCounts.begin(), keywordCounts.end(), [](const std::pair<std::string, int>& entry) {
        std::cout << entry.first << ": " << entry.second << "\n";
    });

    std::cout << "-----------------------\n";
}
