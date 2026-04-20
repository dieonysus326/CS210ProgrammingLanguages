#pragma once
#include <string>
#include <map>


class GroceryTracker {
private:
    std::map<std::string, int> itemFrequency;  // Stores items and counts pairs
    std::string inputFileName;                 // File Name Creation
    void LoadData();                           // reads input file, populates map

public:
    GroceryTracker(std::string fileName);       // Constructor Method
    int GetItemFrequency(std::string item);     // Gets Frequency of item
    void PrintAllFrequencies();                 // Prints all Frequency's
    void PrintHistogram();                      // Prints Histograph for items (using * as count)              
    void SaveToFile();                          // writes frequency.dat
};

