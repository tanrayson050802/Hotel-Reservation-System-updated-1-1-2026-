#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include "HotelSystem.hpp"
using namespace std;

void forgotPassword()
{
    string username, newpass;
    vector<pair<string, string>> users;
    string u, p;
    bool found = false;

    cout << "Enter username to reset password: ";
    cin >> username;

    ifstream infile("users.txt");

    while (infile >> u >> p)
    {
        if (u == username)
        {

            while (true)
            {
                cout << "Enter new password (Must have at least 1 Uppercase, 1 Lowercase, 1 Number and 1 Symbol): ";
                cin >> newpass;

                if (!isPasswordValid(newpass))
                {
                    cout << "Invalid password format!\n";
                    cout << "Password must be at least 8 characters and include:\n";
                    cout << "- At least 1 Uppercase letter\n";
                    cout << "- At least 1 Lowercase letter\n";
                    cout << "- At least 1 Number\n";
                    cout << "- At least 1 Symbol\n";
                    continue;
                }
                break;
            }

            users.push_back({u, newpass});
            found = true;
        }
        else
        {
            users.push_back({u, p});
        }
    }
    infile.close();

    if (!found)
    {
        cout << "Username not found. You can create a new account with a valid username on \"Register\" page. Thank you.\n";
        return;
    }

    ofstream outfile("users.txt");
    for (auto &user : users)
        outfile << user.first << " " << user.second << endl;
    outfile.close();

    cout << "Password reset successful.\n";
}