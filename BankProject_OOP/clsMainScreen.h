#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientScreens.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen:protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7,eShowLoginRegister = 8, eShowCurrencyScreen = 9 , eLogout = 10 ,eExit = 11
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 11]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 11, "Enter Number between 1 to 11? ");
        return Choice;
    }

    static void _ShowAllClientsScreen()
    {
        clsClientScreens::ShowClientsListScreen();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsClientScreens::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsClientScreens::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsClientScreens::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsClientScreens::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUserScreen::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsUserScreens::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
        // then it will return to main function...
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static  void _DeniedAccess()
    {
        _DrawScreenHeader("Access Denied! Contact your Admin.");
    }

    static bool _CheckAccessPermission(clsUser::enPermissions permission)
    {
        if (!CurrentUser.CheckUserPermissions(permission)) {
            _DeniedAccess();
            _GoBackToMainMenue();
            return false;
        }
        return true;
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        system("cls");
        switch (MainMenueOption)
        {
            case enMainMenueOptions::eListClients:
                if (_CheckAccessPermission(clsUser::enPermissions::pListClients)) {
                    _ShowAllClientsScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eAddNewClient:
                if (_CheckAccessPermission(clsUser::enPermissions::pAddNewClient)) {
                    _ShowAddNewClientsScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eDeleteClient:
                if (_CheckAccessPermission(clsUser::enPermissions::pDeleteClient)) {
                    _ShowDeleteClientScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eUpdateClient:
                if (_CheckAccessPermission(clsUser::enPermissions::pUpdateClients)) {
                    _ShowUpdateClientScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eFindClient:
                if (_CheckAccessPermission(clsUser::enPermissions::pFindClient)) {
                    _ShowFindClientScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eShowTransactionsMenue:
                if (_CheckAccessPermission(clsUser::enPermissions::pTranactions)) {
                    _ShowTransactionsMenue();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eManageUsers:
                if (_CheckAccessPermission(clsUser::enPermissions::pManageUsers)) {
                    _ShowManageUsersMenue();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eShowLoginRegister:
                if (_CheckAccessPermission(clsUser::enPermissions::pShowLogInRegister)) {
                    clsUserScreens::ShowLoginRegisterScreen();
                    _GoBackToMainMenue();
                }
                break;

            case enMainMenueOptions::eShowCurrencyScreen:
                system("cls");
                _ShowCurrencyExchangeMainScreen();
                _GoBackToMainMenue();
                break;

            case enMainMenueOptions::eLogout:
                _Logout();
                break;
            case enMainMenueOptions::eExit:
                exit(0);
                break;
        }
    }

public:
    static void ShowMainMenue()
    {
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "\t[11] Exit.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }
};

