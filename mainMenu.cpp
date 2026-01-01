#include <iostream>
#include "HotelSystem.hpp"

using namespace std;

void mainMenu()
{
    int choice;

    while (true)
    {
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            handleInputError();
            continue;
        }

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            showAppreciation();
            return;
        default:
            cout << "Invalid selection.\n";
        }
    }
}
