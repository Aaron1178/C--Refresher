/*
* The objective of this project is to create a Registration and login system 
* for the console. 
*/

/*
*   - Todo Add Change Username Option
*   - Todo Add Change Password Option
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const string loginDetailsFile = "loginDetailsRegistrar.txt";

[[deprecated]]
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

void WAIT()
{
#ifdef _WIN32
    system("pause");
#endif //Todo - Add different platform options for pausing console
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
    
    cout << "Login (1) or Register (2) or type Exit to end session! \n";

    string InputString = "";

    cin >> InputString;
     
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

    else if (InputString == "Exit")
        exit(0);

    else
        return; 
 
    return;
}


/*
*   - Search all usernames and match, then check password is correct. 
*   - No user found? Redirect to Registration
*
*/
void LoginScreen(LoginSystemScreens& inLSS)
{
    CLS();

    if (inLSS != LoginSystemScreens::_Login)
        return;

    cout << "Login using the correct username and password!\n";

    string fUsername = "";
    string fPassword = "";

    string Username = "";
    string Password = "";

    ifstream file(loginDetailsFile);

    if (file.is_open())
    {
        getline(file, fUsername);
        getline(file, fPassword);
    }

    file.close();

    cout << "Username: ";

    cin >> Username;

    cout << "\n" << "Password: ";

    cin >> Password;

    cout << "\n";

    if (Username != fUsername)
    {
        cout << "Username is Incorrect!" << "\n";
        
        inLSS = LoginSystemScreens::_Login;

        WAIT();

        return;
    }
    
    if (Password != fPassword)
    {
        cout << "Password is Incorrect!" << "\n";
        
        inLSS = LoginSystemScreens::_Login;
       
        WAIT();

        return;
    }

    cout << "Login Successful!" << "\n";

    inLSS = LoginSystemScreens::_MainScreen;

    WAIT();

    return;
}


// Todo - Add Multiple Registrations. Checks to see if valid password and username is available.
/*
*   - Encrypt passwords
*   - Confirm Password Option
*   - Password Strength (Maybe)
*/
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
    
    cout << "\n" << "Password: ";

    cin >> password;

    file << username << "\n" << password;

    file.close();

    cout << "Registration Successful! \n";

    inLSS = LoginSystemScreens::_MainScreen;

    WAIT();

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