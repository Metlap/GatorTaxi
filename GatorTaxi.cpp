// ADS-Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include "Taxi.h"

// Main function that creates an object of the Taxi class and reads from the input file
int main(int argc, char** argv)
{
    //Output file stream
    std::ofstream outputFile("output_file.txt");

    Taxi* taxi = new Taxi();

    if (argc == 1) {
        taxi->insertRide(25, 98, 46, outputFile);
        taxi->getNextRide(outputFile);
        taxi->getNextRide(outputFile);
        taxi->insertRide(42, 17, 89, outputFile);
        taxi->insertRide(9, 76, 31, outputFile);
        taxi->insertRide(53, 97, 22, outputFile);
        taxi->getNextRide(outputFile);
        taxi->insertRide(68, 40, 51, outputFile);
        taxi->getNextRide(outputFile);
        taxi->printRidesInRange(1, 100, outputFile);
        taxi->updateTrip(53, 15);
        taxi->insertRide(96, 28, 82, outputFile);
        taxi->insertRide(73, 28, 56, outputFile);
        taxi->updateTrip(9, 88);
        taxi->getNextRide(outputFile);
        taxi->printRide(9, outputFile);
        taxi->insertRide(20, 49, 59, outputFile);
        taxi->insertRide(62, 7, 10, outputFile);
        taxi->cancelRide(20);
        taxi->insertRide(25, 49, 46, outputFile);
        taxi->updateTrip(62, 15);
        taxi->getNextRide(outputFile);
        taxi->printRidesInRange(1, 100, outputFile);
        taxi->insertRide(53, 28, 19, outputFile);
        taxi->printRidesInRange(1, 100, outputFile);
    }
    // File passed as argument
    if (argc > 1) {
        // Read input from the input file passed as commandline arguments 
        taxi->readInputFromFile(argv[1], taxi->actionList);
        while (true) {
            if ((taxi->actionList).size() == 0) {
                return 0;
            }
            taxi->takeAction(outputFile);
        }

    }

    outputFile.close();
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
