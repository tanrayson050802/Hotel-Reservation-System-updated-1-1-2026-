#include <iostream>
#include <limits>
#include <cctype>
#include <ctime>
#include <chrono>
#include <string>
#include "HotelSystem.hpp"

using namespace std;

void handleInputError()
{
    cout << "Invalid input. Please enter correct command.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showAppreciation()
{
    cout << "\nThanks for visiting Velvet Vantage Hotel.\n";
    cout << "Wish you have a nice day!\n";
}

bool isValidDateFormat(const string& date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    int month = stoi(date.substr(5, 2));
    int day   = stoi(date.substr(8, 2));

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    return true;
}

bool isBookingDateLogical(const string& date)
{
    int year  = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day   = stoi(date.substr(8, 2));

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm today = *localtime(&now_time);

    today.tm_hour = 0;
    today.tm_min = 0;
    today.tm_sec = 0;
    time_t todayTime = mktime(&today);

    tm bookingDate = {};
    bookingDate.tm_year = year - 1900;
    bookingDate.tm_mon  = month - 1;
    bookingDate.tm_mday = day;
    time_t bookingTime = mktime(&bookingDate);

    if (difftime(bookingTime, todayTime) < 0)
        return false;

    tm maxDate = today;
    maxDate.tm_year += 1;
    time_t maxBookingTime = mktime(&maxDate);

    if (difftime(bookingTime, maxBookingTime) > 0)
        return false;

    return true;
}


bool isUserNameValid(const string& username)
{
    if (username.length() < 6)
        return false;

    bool hasAlpha = false;
    bool hasDigit = false;

    for (char c : username)
    {
        if (isalpha(c))
            hasAlpha = true;
        else if (isdigit(c))
            hasDigit = true;
    }

    return hasAlpha && hasDigit;
}

bool isPasswordValid(const string& password)
{
    if (password.length() < 8)
        return false;

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    for (char c : password)
    {
        if (isupper(c))
            hasUpper = true;
        else if (islower(c))
            hasLower = true;
        else if (isdigit(c))
            hasDigit = true;
        else
            hasSymbol = true;
    }

    return hasUpper && hasLower && hasDigit && hasSymbol;
}

bool isRoomOccupied(int roomNo, string date)
{
    ifstream in("reservations.txt");
    string user, d;
    int type, room;

    while (in >> user >> type >> room >> d)
    {
        if (room == roomNo && d == date)
        {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

bool isRoomTypeValid(int roomType, int roomNo)
{
    int positionOnFloor = (roomNo - 1) % 15;

    if (roomType == 3)
        return (positionOnFloor >= 0 && positionOnFloor < 5);
    
    if (roomType == 2)
        return (positionOnFloor >= 5 && positionOnFloor < 10);
    
    if (roomType == 1)
        return (positionOnFloor >= 10 && positionOnFloor < 15);

    return false;
}