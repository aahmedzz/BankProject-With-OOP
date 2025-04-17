#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "D://AHMED/Abu hahoud/My Liberaries/clsDate.h"
using namespace std;

class clsScreen
{
public:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t     ___________________________________________";
        cout << "\n\n\t\t\t\t\t" << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t" << SubTitle;
        }
        cout << "\n\t\t\t\t     ___________________________________________\n\n";

        cout << "\t\t\t\t     User: " << CurrentUser.UserName;
        clsDate currentDate;
        cout << "\n\t\t\t\t     Date: " << clsDate::DateToString(clsDate()) <<"\n\n";
    }
};

