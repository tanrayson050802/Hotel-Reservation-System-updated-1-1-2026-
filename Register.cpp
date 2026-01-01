#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "HotelSystem.hpp"
using namespace std;

void registerUser()
{
    string username, password;
    string u, p;

    const int MAX_ATTEMPTS = 3;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        cout << "Enter new username (Must contain at least 6 characters with at least 1 letter and 1 number): ";
        cin >> username;

        if (!isUserNameValid(username))
        {
            cout << "Invalid username format.\n";
            attempts++;
            continue;
        }

        ifstream infile("users.txt");
        bool exists = false;

        while (infile >> u >> p)
        {
            if (u == username)
            {
                exists = true;
                break;
            }
        }
        infile.close();

        if (exists)
        {
            cout << "Account already exists! Please login to your existing account.\n";
            return;
        }

        break;
    }

    if (attempts == MAX_ATTEMPTS)
    {
        cout << "Too many invalid attempts. Returning to main menu.\n";
        return;
    }

    attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        cout << "Enter password (Min 8 chars, uppercase, lowercase, number, symbol): ";
        cin >> password;

        if (!isPasswordValid(password))
        {
            cout << "Invalid password format.\n";
            attempts++;
            continue;
        }

        break;
    }

    if (attempts == MAX_ATTEMPTS)
    {
        cout << "Too many invalid attempts. Registration cancelled.\n";
        return;
    }

    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    cout << "Registration successful!\n";
}
