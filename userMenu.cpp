#include <iostream>
#include <fstream>
#include <string>
#include "HotelSystem.hpp"

using namespace std;

void userMenu(string username)
{
    int choice;

    while (true)
    {
        cout << "\n===== User Menu =====\n";
        cout << "1. View Room Status\n";
        cout << "2. Make Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            handleInputError();
            continue;
        }

        switch (choice)
        {
        case 1:
            ViewRoomStatus();
            break;

        case 2:
            makeReservation(username);
            break;

        case 3:
            cancelBooking(username);
            break;

        case 4:
            showAppreciation();
            return;
        default:
            cout << "Invalid option.\n";
        }
    }
}