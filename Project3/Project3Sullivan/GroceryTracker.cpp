#include "GroceryTracker.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

// Constructor: Initializes the tracker with the given input file name,
// loads item data into memory, and saves a frequency backup file.
GroceryTracker::GroceryTracker(string fileName) {
    // Store the provided file name for use in LoadData()
    inputFileName = fileName;
    // Parse the input file and populate the itemFrequency map
    LoadData();
    // Write the frequency data to frequency.dat as a backup record
    SaveToFile();
}

// LoadData: Opens the input file and reads each item line by line.
// Each item is used as a map key; its value is incremented on each occurrence.
// Throws runtime_error if the file cannot be opened.
void GroceryTracker::LoadData() {
    ifstream inputFile(inputFileName);

    // Verify the file opened successfully before attempting to read
    if (!inputFile.is_open()) {
        throw runtime_error("Error: Could not open file " + inputFileName);
    }

    string item;
    // Read one word (item name) at a time until end of file
    while (inputFile >> item) {
        // If item doesn't exist in map, it's created at 0 then incremented
        itemFrequency[item]++;
    }

    inputFile.close();
}

// SaveToFile: Writes all item-frequency pairs to "frequency.dat".
// Each line contains an item name followed by its purchase count.
// Throws runtime_error if the output file cannot be created.
void GroceryTracker::SaveToFile() {
    ofstream outputFile("frequency.dat");

    // Verify the output file was created successfully
    if (!outputFile.is_open()) {
        throw runtime_error("Error: Could not create frequency.dat");
    }

    // Iterate through the map and write each key-value pair to the file
    for (auto& pair : itemFrequency) {
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close();
}

// GetItemFrequency: Returns the number of times the given item appears
// in the purchase records. Returns 0 if the item is not found.
int GroceryTracker::GetItemFrequency(string item) {
    // Check if item exists before accessing to avoid inserting a default value
    if (itemFrequency.count(item) > 0) {
        return itemFrequency[item];
    }
    return 0;
}

// PrintAllFrequencies: Prints every item and its purchase count
// to the console, one item per line.
void GroceryTracker::PrintAllFrequencies() {
    for (auto& pair : itemFrequency) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// PrintHistogram: Prints a visual histogram to the console.
// Each item is followed by a row of asterisks equal to its purchase count.
void GroceryTracker::PrintHistogram() {
    for (auto& pair : itemFrequency) {
        cout << pair.first << " ";
        // Print one '*' per purchase occurrence
        for (int i = 0; i < pair.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}
