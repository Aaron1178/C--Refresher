/*
* The objective of this project is to create a Registration and login system 
* for the console. 
*/

#include <iostream>
#include <fstream>

using namespace std;

const string loginDetailsFile = "loginDetailsRegistrar.txt";

bool isDigitFromString(string& stringToCheck)
{
    return stringToCheck.find_first_not_of("0123456789") == string::npos;
}

void CLS()
{
#ifdef _WIN32
    system("cls");
#endif //Todo - Add different platform options for clearing console screens
}


enum class LoginSystemScreens {
    _MainScreen,
    _Login,
    _Registration
};


void MainScreen(LoginSystemScreens& inLSS)
{
    CLS();

    if (inLSS != LoginSystemScreens::_MainScreen)
        return;

    cout << "Login and Registration system by Aaron Thompson\n\n";
    
    cout << "Login (1) or Register (2)\n";

    string InputString = "";

    cin >> InputString;

    if (!isDigitFromString(InputString))
        return;

     
    if (InputString == "1")
    {
        inLSS = LoginSystemScreens::_Login;

        return;
    }
    else if (InputString == "2")
    {
        inLSS = LoginSystemScreens::_Registration;
            
        return;
    }
    else
        return;

    return;
}

void LoginScreen(LoginSystemScreens& inLSS)
{
    CLS();

    if (inLSS != LoginSystemScreens::_Login)
        return;

    cout << "Login using the correct username and password!\n";

    cout << "Username: ";

    string InputString = "";

    cin >> InputString;

    return;
}

void RegisterScreen(LoginSystemScreens& inLSS)
{
    CLS();

    if (inLSS != LoginSystemScreens::_Registration)
        return;

    ofstream file(loginDetailsFile);

    cout << "Register with a username and password!\n";

    cout << "Username: ";

    string username = "";
    string password = "";

    cin >> username;
    
    cout << "\nPassword: ";

    cin >> password;

    file << username << "\n" << password;

    file.close();

    cout << "Registration Successful! \n";

    inLSS = LoginSystemScreens::_MainScreen;

    return;
}

int main()
{
    string ConsoleInput = "";

    cout << "Login (1) or Register! (2)\n\n";

    LoginSystemScreens Screens = LoginSystemScreens::_MainScreen;

    while (true)
    {
        switch (Screens)
        {
            case LoginSystemScreens::_MainScreen: MainScreen(Screens);

            case LoginSystemScreens::_Login: LoginScreen(Screens);

            case LoginSystemScreens::_Registration: RegisterScreen(Screens);
        }
    }

    return 0;
}