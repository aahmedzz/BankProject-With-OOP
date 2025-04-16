// BankProject_OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "clsLoginScreen.h"
using namespace std;

int main()
{
    //this will make the login screen displayed again after logout.
    while (true) {
        clsLoginScreen::ShowLoginScreen();
    }

    system("pause>0");
}

