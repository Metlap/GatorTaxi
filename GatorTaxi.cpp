// ADS-Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Taxi.h"

int main()
{
    std::cout << "Hello World!\n";
    Taxi* taxi = new Taxi();
    /*Ride ride(1, 2, 4);
    Ride r2(2, 10, 34);*/
    /*taxi->insertRide(2,2,4);
    taxi->insertRide(1, 10, 34);
    taxi->printRide(2);
    taxi->getNextRide();
    taxi->printRide(1);
    taxi->printRide(2); */    

    taxi->insertRide(25, 98, 46);
    taxi->getNextRide();
    taxi->getNextRide();
    taxi->insertRide(42, 17, 89);
    taxi->insertRide(9, 76, 31);
    taxi->insertRide(53, 97, 22);
    taxi->getNextRide();
    taxi->insertRide(68, 40, 51);
    taxi->getNextRide();
    taxi->printRidesInRange(1,100);
    taxi->updateTrip(53, 15);
    taxi->insertRide(96, 28, 82);
    taxi->insertRide(73, 28, 56);
    taxi->updateTrip(9, 88);
    taxi->getNextRide();
    taxi->printRide(9);
    taxi->insertRide(20, 49, 59);
    taxi->insertRide(62, 7, 10);
    taxi->cancelRide(20);
    taxi->insertRide(25, 49, 46);
    taxi->updateTrip(62, 15);
    taxi->getNextRide();
    taxi->printRidesInRange(1, 100);
    taxi->insertRide(53, 28, 19);
    taxi->printRidesInRange(1, 100);

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
