#include "utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::pair<std::string, double>> parseMoviesCSV(const std::string& filename) {
    std::vector<std::pair<std::string, double>> result;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find_last_of(',');
        if (commaPos == std::string::npos) continue;
        
        std::string name = line.substr(0, commaPos);
        std::string ratingStr = line.substr(commaPos + 1);
        
        try {
            double rating = std::stod(ratingStr);
            result.push_back({name, rating});
        } catch (...) {
        }
    }
    return result;
}

std::vector<std::string> parsePrefixesTXT(const std::string& filename) {
    std::vector<std::string> prefixes;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return prefixes;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line == "\r") continue; 
        
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    return prefixes;
}
