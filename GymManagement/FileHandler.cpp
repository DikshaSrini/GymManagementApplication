#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Function to read data from a CSV file and return it as a vector of vector of strings
std::vector<std::vector<std::string>> FileHandler::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data; // Vector to store the CSV data
    std::ifstream file(filename); // Open the file for reading
    if (!file.is_open()) { // Check if the file was successfully opened
        std::cerr << "Error: Could not open file " << filename << "\n"; // Print error message if file cannot be opened
        return data; // Return empty data vector
    }

    std::string line;
    while (std::getline(file, line)) { // Read the file line by line
        std::vector<std::string> row; // Vector to store the values of the current row
        std::stringstream ss(line); // Create a stringstream from the line
        std::string value;
        while (std::getline(ss, value, ',')) { // Split the line by commas
            row.push_back(value); // Add each value to the row vector
        }
        data.push_back(row); // Add the row vector to the data vector
    }
    file.close(); // Close the file
    return data; // Return the data vector
}

// Function to append a row of data to a CSV file
void FileHandler::appendCSV(const std::string& filename, const std::vector<std::string>& row) {
    std::ofstream file(filename, std::ios::app); // Open the file for appending
    if (!file.is_open()) { // Check if the file was successfully opened
        std::cerr << "Error: Could not open file " << filename << "\n"; // Print error message if file cannot be opened
        return; // Exit the function
    }

    for (size_t i = 0; i < row.size(); ++i) { // Iterate over the values in the row
        file << row[i]; // Write each value to the file
        if (i < row.size() - 1) file << ","; // Add a comma after each value except the last one
    }
    file << "\n"; // Add a newline at the end of the row
    file.close(); // Close the file
}