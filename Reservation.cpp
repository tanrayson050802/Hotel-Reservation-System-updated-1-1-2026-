#include <iostream>
#include <fstream>
#include <string>
#include "HotelSystem.hpp"

using namespace std;       
        
void makeReservation(string username)
{
    int roomType, roomNo;
    string date;
    int attempts = 0;
    bool dateValid = false;

    do
    {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;

        if (!isValidDateFormat(date))
        {
            cout << "Invalid date format! Please use YYYY-MM-DD.\n";
            attempts++;
        }
        else if (!isBookingDateLogical(date))
        {
            cout << "Invalid booking date.\nYou cannot book for past dates or dates exceeding 1 year.\n\n";
            attempts++;
        }
        else
        {
            dateValid = true;
            break; 
        }

    } while (attempts < 2);

    if (!dateValid)
    {
        cout << "Too many invalid attempts. Reservation cancelled.\n";
        return;
    }

    showRoomInfo();

    bool typeValid = false;
    do
    {
        cout << "Choose room type (1-Single, 2-Double, 3-Family): ";
        if (!(cin >> roomType) || (roomType < 1 || roomType > 3))
        {
            handleInputError();
        }
        else
        {
            typeValid = true;
        }
    } while (!typeValid);

    showRoomStatus(date);
    cout << "Choose room number: ";
    cin >> roomNo;

    if (!isRoomTypeValid(roomType, roomNo))
    {
        cout << "Invalid room number for selected room type!\n";
        return; 
    }

    if (isRoomOccupied(roomNo, date))
    {
        cout << "Room already booked on this date. Choose another room.\n";
        return;
    }

    ofstream out("reservations.txt", ios::app);
    if (out.is_open()) {
        out << username << " " << roomType << " " << roomNo << " " << date << endl;
        out.close();
        cout << "Reservation saved successfully!\n";
        generateBill(roomType);
    } else {
        cout << "Error opening database file.\n";
    }
}