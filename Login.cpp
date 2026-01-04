#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "HotelSystem.hpp"
using namespace std;

void loginUser()
{
    string username, password, u, p;
    bool found = false;
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "Username: ";
        cin >> username;

        if (!isUserNameValid(username))
        {
            cout << "Invalid username format.\n";
            attempts++;
            continue;
        }

        cout << "Password: ";
        cin >> password;

        ifstream infile("users.txt");
        found = false;

        while (infile >> u >> p)
        {
            if (u == username)
            {
                found = true;

                if (p == password)
                {
                    cout << "Login successful!\n";
                    infile.close();
                    userMenu(username);
                    return;
                }
                else
                {
                    cout << "Incorrect password.\n";
                    infile.close();

                    char choice;
                    while (true)
                    {
                        cout << "Do you want to reset your password? (Y/N): ";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y')
                        {
                            forgotPassword();
                            return;
                        }
                        else if (choice == 'N' || choice == 'n')
                        {
                            return;
                        }
                        else
                        {
                            handleInputError(); 
                        }
                    }
                }
            }
        }
        infile.close();

        if (!found)
        {
            cout << "Account not found. Please register.\n";
            return;
        }

        attempts++;
    }

    cout << "Too many failed login attempts.\n";
}
