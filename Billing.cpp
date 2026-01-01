#include <iostream>
#include "HotelSystem.hpp"

using namespace std;

void generateBill(int roomType)
{
    double price;

    if (roomType == 1) price = 100;
    else if (roomType == 2) price = 190;
    else price = 270;

    double sst = price * 0.06;
    double total = price + sst;

    cout << "\n------ BILL ------\n";
    cout << "Room Price: RM" << price << endl;
    cout << "SST (6%): RM" << sst << endl;
    cout << "Total: RM" << total << endl;
}
