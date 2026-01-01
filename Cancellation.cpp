#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "HotelSystem.hpp"

using namespace std;

void cancelBooking(string username)
{
    vector<string> records;
    vector<int> userRooms;
    vector<int> userTypes;

    ifstream in("reservations.txt");
    string user, fileDate, inputDate;
    int type, room;
    int attempts = 0;
    bool dateValid = false;

    do
    {
        cout << "Enter date to cancel (YYYY-MM-DD): ";
        cin >> inputDate;

        if (!isValidDateFormat(inputDate))
        {
            cout << "Invalid date format! Please use format YYYY-MM-DD.\n";
            attempts++;
        }
        else if (!isBookingDateLogical(inputDate))
        {
            cout << "Invalid date. You cannot cancel bookings for past dates or dates exceeding 1 year.\n";
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
        cout << "Too many invalid attempts. Returning to menu.\n";
        in.close();
        return;
    }

    while (in >> user >> type >> room >> fileDate)
    {
        if (user == username && fileDate == inputDate)
        {
            userRooms.push_back(room);
            userTypes.push_back(type);
        }
        
        records.push_back(user + " " + to_string(type) + " " + to_string(room) + " " + fileDate);
    }
    in.close();

    if (userRooms.empty())
    {
        cout << "No bookings found for " << username << " on " << inputDate << ".\n";
        return;
    }

    if (userRooms.size() == 1)
    {
        char confirm;
        cout << "\nOnly one booking found:\n";
        cout << "Room " << userRooms[0] << " | ";

        if (userTypes[0] == 1) cout << "Single Room";
        else if (userTypes[0] == 2) cout << "Double Room";
        else if (userTypes[0] == 3) cout << "Family Room";

    while (true)
    {
        cout << "\nConfirm cancellation? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y')
        {
            break;
        }
        else if (confirm == 'N' || confirm == 'n')
        {
            cout << "Cancellation aborted.\n";
            return;
        }
        else
        {
            handleInputError();
        }
    }

    ofstream out("reservations.txt");
    for (auto &r : records)
    {
        if (!(r.find(username + " ") == 0 &&
              r.find(" " + to_string(userRooms[0]) + " ") != string::npos &&
              r.find(inputDate) != string::npos))
        {
            out << r << endl;
        }
    }
    out.close();

    cout << "Booking cancelled successfully.\n";
    return;
}

    cout << "\nRooms booked on " << inputDate << ":\n";
    for (size_t i = 0; i < userRooms.size(); i++)
    {
        cout << i + 1 << ". Room " << userRooms[i] << " | ";

        if (userTypes[i] == 1)
            cout << "Single Room";
        else if (userTypes[i] == 2)
            cout << "Double Room";
        else if (userTypes[i] == 3)
            cout << "Family Room";

        cout << endl;
    }

    cout << "\nChoose cancellation option:\n";
    cout << "1. Cancel ONE room\n";
    cout << "2. Cancel MULTIPLE rooms\n";
    cout << "3. Cancel ALL rooms\n";
    cout << "Selection: ";

    int choice;
    cin >> choice;

    vector<int> roomsToCancel;

    if (choice == 1)
    {
        int idx;
        cout << "Enter room index to cancel: ";
        cin >> idx;
        roomsToCancel.push_back(userRooms[idx - 1]);
    }
    else if (choice == 2)
    {
        int count;
        cout << "How many rooms to cancel? ";
        cin >> count;

        cout << "Enter room indexes (spacing between indexes): ";
        for (int i = 0; i < count; i++)
        {
            int idx;
            cin >> idx;
            roomsToCancel.push_back(userRooms[idx - 1]);
        }
    }
    else if (choice == 3)
    {
        roomsToCancel = userRooms;
    }
    else
    {
        cout << "Invalid selection.\n";
        return;
    }

    ofstream out("reservations.txt");
    for (auto &r : records)
    {
        bool cancel = false;

        for (int roomNo : roomsToCancel)
        {
            if (r.find(username + " ") == 0 &&
                r.find(" " + to_string(roomNo) + " ") != string::npos &&
                r.find(inputDate) != string::npos)
            {
                cancel = true;
            }
        }

        if (!cancel)
            out << r << endl;
    }
    out.close();

    cout << "Selected room(s) cancelled successfully.\n";
}

