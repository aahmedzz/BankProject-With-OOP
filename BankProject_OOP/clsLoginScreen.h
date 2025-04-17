#include"clsScreen.h"
#include"clsUser.h"
#include"clsMainScreen.h"
#include"Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static bool _Login()
    {
        bool LoginFaild = false;
        short TrialsCount = 3;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";
                TrialsCount--;
                if (TrialsCount == 0) {
                    cout << "You are locked after 3 trials.\n\n";
                    return false;
                }
                else
                {
                    cout << "\nYou have "<< TrialsCount << " Trial(s) to login\n\n";
                }

            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }

};