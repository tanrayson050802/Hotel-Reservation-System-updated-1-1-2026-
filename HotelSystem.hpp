#ifndef HOTEL_SYSTEM_HPP
#define HOTEL_SYSTEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <fstream>
#include <chrono>
#include <ctime>
#include <limits>

using namespace std;

void showWelcome();
void generateBill(int roomType);
void cancelBooking(string username);
void ViewRoomStatus();
void makeReservation(string username);
void forgotPassword();
void loginUser();
void mainMenu();
void registerUser();
void userMenu(string username);
bool isRoomOccupied (int roomNo, string date);
bool isRoomTypeValid(int roomType, int roomNo);
void showRoomInfo();
void showRoomStatus(string date);
void handleInputError();
void showAppreciation();
bool isValidDateFormat(const string& date);
bool isBookingDateLogical(const string& date);
bool isUserNameValid(const string& username);
bool isPasswordValid(const string& password);

#endif