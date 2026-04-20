// Daniel Sullivan  
// Project 3 - Grocery Frequency
// 04/03/26

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "GroceryTracker.h"
using namespace std;

void UserMenu() {   //Initial User Menu option. Prints everytime a selection is made either correctly or incorrectly.
    cout << setfill('*') << setw(40) << " " << endl;
    cout << "* Corner Grocer Inventory Application *" << endl;
    cout << setfill('*') << setw(40) << " " << endl;
    cout << "*        1) Item Search               *" << endl;
    cout << "*        2) Print List                *" << endl;
    cout << "*        3) Frequency Check           *" << endl;
    cout << "*        4) Exit Program              *" << endl;
    cout << setfill('*') << setw(40) << " " << endl;
    cout << "Select an option (1-4): ";


}

int MenuOption(GroceryTracker& tracker) {
    //Initial Variables
    int choice = 0;
    string item;
    int count = 0;
    //First try method. Will catch anything that is not 1-4
    try {
        //Check for must be a number
        if (!(cin >> choice)) {
            throw invalid_argument("Input must be a number");
        }
        //Check for Choices of 1-4
        if (choice < 1 || choice > 4) {
            throw out_of_range("Number must be between 1 and 4");
        }
        //Switch to check after valid option has been selected.
        switch (choice) {
        //First case is for Item Frequency
        case 1:
            cout << "Enter item to search: ";
            cin >> item;
            count = tracker.GetItemFrequency(item);
            //Basic if/else statement for proper grammer
            if (count == 0) {
                cout << item << " was not found in the records." << endl;
            }
            else if (count == 1) {
                cout << item << " was purchased 1 time." << endl;
            }
            else {
                cout << item << " was purchased " << count << " times." << endl;
            }
            break;
            //Prints all frequencies
        case 2:
            tracker.PrintAllFrequencies();
            break;
        case 3:
            //Prints Histogram
            tracker.PrintHistogram();
            break;
        case 4:
            //Exits program
            cout << "Exiting program." << endl;
            break;
        }
    }
    //Both of these are the catch statemnts. Clears out input so it does not create an infinite loop.
    catch (const invalid_argument& e) {
        cout << endl << e.what() << endl << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }
    catch (const out_of_range& e) {
        cout << endl << e.what() << endl << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }

    return choice;
}
//Main Program
int main() {
    //Has a try/catch to ensure that proper file is being uploaded. 
    try {
        //Creates the Grocery Tracker class with the input file. 
        //Possible addition could be to get the input file in through cin and then create it. But since only one file this is all that is needed. 
        GroceryTracker tracker("InputFile.txt");
        //Sets the userChoice to 0 so loop will start. 
        int userChoice = 0;
        //Main loop of program. Once option is 4 will exit program.
        while (userChoice != 4) {
            //Displays menu options
            UserMenu();
            //Sets userChoice based on the menu option. This will run the program
            //and catch any errors for the user putting in the wrong input.
            userChoice = MenuOption(tracker);
        }
    }
    //Catch statement to display error. I had a runtime error for a while because I ahd the wrong InputFile put in. 
    catch (const runtime_error& e) {
        cout << e.what() << endl; 
    }
    return 0;
}