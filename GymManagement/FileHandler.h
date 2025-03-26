#pragma once

#include <vector>
#include <string>

class FileHandler {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    static void appendCSV(const std::string& filename, const std::vector<std::string>& row);
};


