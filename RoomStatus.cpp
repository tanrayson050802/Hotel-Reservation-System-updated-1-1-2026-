#include <iostream>
#include <fstream>
#include <string>
#include "HotelSystem.hpp"

using namespace std;

void ViewRoomStatus()
{
    string date;
    int attempts = 0;
    bool isValid = false;

    do
    {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;

        if (!isValidDateFormat(date))
        {
            cout << "Invalid date format! Please use format YYYY-MM-DD.\n";
            attempts++;
        }
        else if (!isBookingDateLogical(date))
        {
            cout << "Invalid date to show room status.\nYou cannot view rooms for past date and date that exceeds a limit of 1 year. \n\n";
            attempts++;
        }
        else
        {
            isValid = true;
            break;
        }

    } while (attempts < 2);

    if (isValid)
    {
        showRoomStatus(date);
    }
    else
    {
        cout << "Too many invalid attempts. Returning to menu page. \n";
    }
}

void showRoomStatus(string date)
{
    cout << "\n===== ROOM STATUS FOR " << date << " =====" << endl;
    cout << "[ X ] = Booked | [ # ] = Available" << endl;

    for (int floor = 0; floor < 4; floor++)
    {
        int floorStart = (floor * 15) + 1;
        cout << "\n--- FLOOR " << floor + 1 << " ---" << endl;

        cout << "Family Rooms | ";
        for (int i = floorStart; i < floorStart + 5; i++)
        {
            if (isRoomOccupied(i, date)) cout << "[ X ]\t";
            else cout << "[ " << i << " ]\t";
        }
        cout << endl;

        cout << "Double Rooms | ";
        for (int i = floorStart + 5; i < floorStart + 10; i++)
        {
            if (isRoomOccupied(i, date)) cout << "[ X ]\t";
            else cout << "[ " << i << " ]\t";
        }
        cout << endl;

        cout << "Single Rooms | ";
        for (int i = floorStart + 10; i < floorStart + 15; i++)
        {
            if (isRoomOccupied(i, date)) cout << "[ X ]\t";
            else cout << "[ " << i << " ]\t";
        }
        cout << endl;
    }
}