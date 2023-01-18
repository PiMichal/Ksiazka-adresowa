#include <iostream>
#include <windows.h>
#include <regex>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

fstream data, userFile;

struct User {
    int loginUserID;
    string login, password;
};

struct UserData {
    int id;
    string name, surname, phoneNumber, email, address;
};

string loadData() {
    string in = "";
    cin.sync();
    getline(cin, in);
    return in;
}

void saveChangesToTheFile(vector<UserData> &addressBookWithUsers, int loginUserID) {

    UserData user;

    data.open("Adresaci.txt", ios::in);
    ofstream newFile("Adresaci_temp.txt", ios::out);

    int loginID = 0, lineNumber = 1;
    string line;

    while (getline(data, line, '|')) {

        switch(lineNumber) {
        case 1:
            user.id = atoi(line.c_str());
            break;
        case 2:
            loginID = atoi(line.c_str());
            break;
        case 3:
            user.name = line;
            break;
        case 4:
            user.surname = line;
            break;
        case 5:
            user.phoneNumber = line;
            break;
        case 6:
            user.email = line;
            break;
        case 7:
            user.address = line;
            break;
        }

        if (lineNumber == 7) {
            if (addressBookWithUsers.size() == 0 && loginID != loginUserID)
                newFile << user.id << "|" << loginID << "|" << user.name << "|" << user.surname << "|" << user.phoneNumber << "|" << user.email << "|" << user.address << "|" << endl;
            else {
                for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
                    if (user.id == addressBookWithUsers.at(i).id && loginID == loginUserID) {
                        newFile << addressBookWithUsers.at(i).id << "|" << loginUserID << "|" << addressBookWithUsers.at(i).name << "|" << addressBookWithUsers.at(i).surname << "|" << addressBookWithUsers.at(i).phoneNumber << "|" << addressBookWithUsers.at(i).email << "|" << addressBookWithUsers.at(i).address << "|" << endl;
                        break;
                    } else if (loginID != loginUserID) {
                        newFile << user.id << "|" << loginID << "|" << user.name << "|" << user.surname << "|" << user.phoneNumber << "|" << user.email << "|" << user.address << "|" << endl;
                        break;
                    }
                }
            }

            lineNumber = 0;
        }

        lineNumber++;
    }
    newFile.close();
    data.close();
    remove("Adresaci.txt");
    rename("Adresaci_temp.txt", "Adresaci.txt");
}
void editingScreen(){
    system("cls");
    cout << ">>>>> Edycja adresata <<<<<" << endl;
    cout << "------------------------------" << endl;

}

void editHomeAddress(vector<UserData> &addressBookWithUsers, int ID) {
    editingScreen();

    cout << "Zmiana adresu " << addressBookWithUsers.at(ID).address << " na: ";
    addressBookWithUsers.at(ID).address = loadData();
}

bool emailAddressVerificationByRegex(string newEmail) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(newEmail,pattern);
}

string emailAddressVerification (vector<UserData> &addressBookWithUsers, string newEmail) {
    int i = 0;

    while (emailAddressVerificationByRegex(newEmail) == false && (int) addressBookWithUsers.size() == 0) {
        cout << "Niepoprawny adres e-mail.\nWpisz jeszcze raz: ";
        newEmail = loadData();
    }

    while (i < (int) addressBookWithUsers.size()) {

        if (emailAddressVerificationByRegex(newEmail) == false) {
            cout << "Niepoprawny adres e-mail.\nWpisz jeszcze raz: ";
            newEmail = loadData();
        } else if (addressBookWithUsers.at(i).email == newEmail) {
            cout << "Masz juz adresata z podanym e-mailem: " << newEmail << "\nWpisz pononwnie: ";
            newEmail = loadData();
            i = -1;
        }
        i++;
    }
    return newEmail;
}

void editAddresEmail(vector<UserData> &addressBookWithUsers, int ID) {
    editingScreen();

    string newEmail;
    cout << "Zmiana e-mail " << addressBookWithUsers.at(ID).email << " na: ";
    newEmail = loadData();

    newEmail = emailAddressVerification(addressBookWithUsers, newEmail);

    addressBookWithUsers.at(ID).email = newEmail;
}

bool checkIfThereAreOnlyDigits(string newNumber) {

    return all_of(newNumber.begin(), newNumber.end(), ::isdigit);
}

string phoneNumberVerification (vector<UserData> &addressBookWithUsers, string newNumber) {

    int i = 0;

    while (checkIfThereAreOnlyDigits(newNumber) == false && (int) addressBookWithUsers.size() == 0) {
        cout << "Niepoprawny numer telefonu.\nWpisz jeszcze raz: ";
        newNumber = loadData();
    }

    while (i < (int) addressBookWithUsers.size()) {
        if (checkIfThereAreOnlyDigits(newNumber) == false) {
            cout << "Niepoprawny numer telefonu.\nWpisz jeszcze raz: ";
            newNumber = loadData();
            i = -1;
        } else if (addressBookWithUsers.at(i).phoneNumber == newNumber && (int) addressBookWithUsers.size() != 0) {
            cout << "Masz juz adresata z podanym numerem: " << newNumber << "\nWpisz pononwnie: ";
            newNumber = loadData();
            i = -1;

        }
        i++;
    }

    return newNumber;
}

void editNumberPhone(vector<UserData> &addressBookWithUsers, int ID) {
    editingScreen();
    string newNumber;
    cout << "Zmiana numeru telefonu " << addressBookWithUsers.at(ID).phoneNumber << " na: ";
    newNumber = loadData();
    newNumber = phoneNumberVerification(addressBookWithUsers, newNumber);

    addressBookWithUsers.at(ID).phoneNumber = newNumber;
}

void editSurname(vector<UserData> &addressBookWithUsers, int ID) {
    editingScreen();

    cout << "Zmiana nazwiska " << addressBookWithUsers.at(ID).surname << " na: ";
    addressBookWithUsers.at(ID).surname = loadData();
}

void editName(vector<UserData> &addressBookWithUsers, int ID) {
    editingScreen();

    cout << "Zmiana imienia " << addressBookWithUsers.at(ID).name << " na: ";
    addressBookWithUsers.at(ID).name = loadData();
}

void displaysUsersByID(vector<UserData> &addressBookWithUsers, int ID) {
    cout << "Id:                " << addressBookWithUsers.at(ID).id << endl;
    cout << "Imie:              " << addressBookWithUsers.at(ID).name << endl;
    cout << "Nazwisko:          " << addressBookWithUsers.at(ID).surname << endl;
    cout << "Numer telefonu:    " << addressBookWithUsers.at(ID).phoneNumber << endl;
    cout << "E-mail:            " << addressBookWithUsers.at(ID).email << endl;
    cout << "Adres:             " << addressBookWithUsers.at(ID).address << endl;
    cout << endl;
}

void displaysEditMenu() {
    system ("cls");
    cout << ">>>>> Edycja adresata <<<<<" << endl;
    cout << endl;
    cout << "1. Zmien imie." << endl;
    cout << "2. Zmien nazwisko." << endl;
    cout << "3. Zmien numer telefonu." << endl;
    cout << "4. Zmien e-mail" << endl;
    cout << "5. Zmien adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cout << endl;
}


int searchForAUserByID(vector<UserData> &addressBookWithUsers) {

    int userID;
    string checkID;
    cout << "Wpisz ID: ";
    cout << endl;
    checkID = loadData();
    while (checkIfThereAreOnlyDigits(checkID) == false) {
        cout << "Wpisano: " << checkID << "\nNalezy wpisac ID skladajace sie z samych liczb: ";
        checkID = loadData();
    }
    userID = atoi(checkID.c_str());

    for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
        if (userID == addressBookWithUsers.at(i).id)
            return i;
    }
    return -1;
}

void editSelectedUserByID(vector<UserData> &addressBookWithUsers, int loginUserID) {

    int ID = searchForAUserByID(addressBookWithUsers);
    bool backToMenu = true;

    if (ID < 0 ) {
        cout << "Nie ma takiego adresata";
        Sleep(1500);
        backToMenu = false;
    }

    while (backToMenu && ID >= 0) {
        displaysEditMenu();
        displaysUsersByID(addressBookWithUsers, ID);
        switch (getch()) {
        case '1':
            editName(addressBookWithUsers, ID);
            break;
        case '2':
            editSurname(addressBookWithUsers, ID);
            break;
        case '3':
            editNumberPhone(addressBookWithUsers, ID);
            break;
        case '4':
            editAddresEmail(addressBookWithUsers, ID);
            break;
        case '5':
            editHomeAddress(addressBookWithUsers, ID);
            break;
        case '6':
            backToMenu = false;
            break;
        default:
            cout << "Niepoprawny wybor." << endl;
            Sleep(1000);
            break;
        }
        saveChangesToTheFile(addressBookWithUsers, loginUserID);
    }
}

int loadTheDataFileIntoTheProgram(vector<UserData> &addressBookWithUsers, int loginUserID) {

    UserData user;
    addressBookWithUsers.clear();

    int lineNumber = 1, loginID = 0;
    string line;

    while (getline(data, line, '|')) {

        if (line == "\n")
            break;

        switch(lineNumber) {
        case 1:
            user.id = atoi(line.c_str());
            break;
        case 2:
            loginID = atoi(line.c_str());
            break;
        case 3:
            user.name = line;
            break;
        case 4:
            user.surname = line;
            break;
        case 5:
            user.phoneNumber = line;
            break;
        case 6:
            user.email = line;
            break;
        case 7:
            user.address = line;
            break;
        }
        if (lineNumber == 7) {
            lineNumber = 0;
            if (loginID == loginUserID)
                addressBookWithUsers.emplace_back(user);
        }
        lineNumber++;
    }

    return user.id;
}

void deleteScreen(){
    system("cls");
    cout << ">>>>> Usuwanie adresata <<<<<" << endl;
    cout << "------------------------------" << endl;
}

void deleteSelectedUser(vector<UserData> &addressBookWithUsers, int loginUserID) {

    deleteScreen();

    int ID = searchForAUserByID(addressBookWithUsers);
    if (ID < 0 ) {
        cout << "Nie ma takiego adresata";
        Sleep(1500);
    } else {
        displaysUsersByID(addressBookWithUsers, ID);
        cout << "Czy napewno chcesz usunac adresata ? " << endl;
        cout << "t/n: ";
    }

    if (ID >= 0 && getch() == 't') {

        if (addressBookWithUsers.size() == 1)
            addressBookWithUsers.clear();

        else if (addressBookWithUsers.size() > 1) {
            for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
                if (i == ID)
                    addressBookWithUsers.erase(addressBookWithUsers.begin() + ID);
            }
        }

        saveChangesToTheFile(addressBookWithUsers, loginUserID);
        system ("cls");
        cout << "\n>>>>> Adresat zostal usuniety. <<<<<";
        Sleep(1500);
    }
}

void displaysAllUsers(vector<UserData> &addressBookWithUsers) {

    system("cls");

    for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
        cout << addressBookWithUsers[i].id << endl;
        cout << addressBookWithUsers[i].name << endl;
        cout << addressBookWithUsers[i].surname << endl;
        cout << addressBookWithUsers[i].phoneNumber << endl;
        cout << addressBookWithUsers[i].email << endl;
        cout << addressBookWithUsers[i].address << endl << endl;
    }
    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . ." << endl;
    getch();
}

void searchBySurname(vector<UserData> &addressBookWithUsers) {
    bool check = true;
    string wantedSurname;
    system ("cls");
    cout << "Wpisz nazwisko: ";
    wantedSurname = loadData();
    cout << endl;
    for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
        if (wantedSurname == addressBookWithUsers.at(i).surname) {
            displaysUsersByID(addressBookWithUsers, i);
            check = false;
        }
    }
    if (check == true)
        cout << "Nie ma adresata o nazwisku: " << wantedSurname << endl;

    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . .";
    getch();
}

void searchByName(vector<UserData> &addressBookWithUsers) {
    bool check = true;
    string wantedName;
    system ("cls");
    cout << "Wpisz imie: ";
    wantedName = loadData();
    cout << endl;
    for (int i = 0; i < (int) addressBookWithUsers.size(); i++) {
        if (wantedName == addressBookWithUsers.at(i).name) {
            displaysUsersByID(addressBookWithUsers, i);
            check = false;
        }
    }
    if (check == true)
        cout << "Nie ma takiego adresata o imieniu: " << wantedName << endl;

    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . ." << endl;
    getch();
}

bool checkIfThereAreAnyUsers (vector<UserData> &addressBookWithUsers) {

    if ((int) addressBookWithUsers.size() == 0) {
        system ("cls");
        cout << "Ksiazka adresowa jest pusta !!!";
        Sleep(1500);;
        return false;
    }
    return true;
}

void dataLoggingScreen(){
    system("cls");
    cout << ">>>>> Dodawanie adresata <<<<<" << endl;
    cout << "------------------------------" << endl;
}

int dataLogging(vector<UserData> &addressBookWithUsers, int loginUserID) {

    dataLoggingScreen();

    int IDOfTheLastUser;

    data.open("Adresaci.txt", ios::in);

    if (data.good()){
        IDOfTheLastUser = loadTheDataFileIntoTheProgram(addressBookWithUsers, loginUserID);
        data.close();
    }

    ifstream in ("Adresaci.txt");
    bool fileIsEmpty = (in.get(), in.eof());

    if (fileIsEmpty){
        IDOfTheLastUser = 0;
        in.close();
    }

    string name, surname, phoneNumber, email, address;

    data.open("Adresaci.txt", ios::out | ios::app);

    if (IDOfTheLastUser == 0)
        IDOfTheLastUser = 1;
    else
        IDOfTheLastUser = IDOfTheLastUser + 1;


    cout << "Wpisz imie: ";
    name = loadData();

    cout << "Wpisz nazwisko: ";
    surname = loadData();

    cout << "Wpisz numer telefonu: ";
    phoneNumber = loadData();
    phoneNumber = phoneNumberVerification(addressBookWithUsers, phoneNumber);

    cout << "Wpisz adres e-mail: ";
    email = loadData();
    email = emailAddressVerification(addressBookWithUsers, email);

    cout << "Wpisz adres zamieszkania: ";
    address = loadData();

    addressBookWithUsers.push_back({IDOfTheLastUser, name, surname, phoneNumber, email, address});

    cout << "Adresat zostal dodany do ksiazki adresowej." << endl;
    Sleep(1000);

    data << IDOfTheLastUser << "|" << loginUserID << "|" << name << "|" << surname << "|" << phoneNumber << "|" << email << "|" << address << "|" << endl;

    data.close();

    return IDOfTheLastUser;
}

void editUserPassword(vector<User> &userRegistry, int loginUserID) {

    system("cls");
    data.open("Uzytkownicy.txt", ios::out);
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;

    for (int i = 0; i < (int) userRegistry.size(); i++) {
        if (userRegistry.at(i).loginUserID == loginUserID) {
            userRegistry.at(i).password = password;
            data <<  userRegistry.at(i).loginUserID << "|" << userRegistry.at(i).login << "|" << userRegistry.at(i).password << "|" << endl;
        }

        else
            data <<  userRegistry.at(i).loginUserID << "|" << userRegistry.at(i).login << "|" << userRegistry.at(i).password << "|" << endl;
    }

    data.close();
    system ("cls");
    cout << "Haslo zmienione";
    Sleep(1500);
}

void displaysTheMainMenu() {
    system ("cls");
    cout << ">>>>> MENU UZYTKOWNIKA <<<<<" << endl;
    cout << endl;
    cout << "1. Dodaj adresata." << endl;
    cout << "2. Wyszukaj po imieniu." << endl;
    cout << "3. Wyszukaj po nazwisku." << endl;
    cout << "4. Wyswietl wszystkich adresatow." << endl;
    cout << "5. Usun adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "-----------------------" << endl;
    cout << "7. Zmien haslo." << endl;
    cout << "8. Wyloguj sie." << endl;
}


void selectAnOptionInTheMainMenu(vector<User> &userRegistry, int loginUserID) {

    vector<UserData> addressBookWithUsers;
    bool logout = true;

    data.open("Adresaci.txt", ios::in);
    if (data.good()) {
        loadTheDataFileIntoTheProgram(addressBookWithUsers, loginUserID);
        data.close();
    }

    while (logout) {

        displaysTheMainMenu();

        switch (getch()) {
        case '1':
            dataLogging(addressBookWithUsers, loginUserID);
            break;
        case '2':
            if (checkIfThereAreAnyUsers(addressBookWithUsers))
                searchByName(addressBookWithUsers);
            break;
        case '3':
            if (checkIfThereAreAnyUsers(addressBookWithUsers))
                searchBySurname(addressBookWithUsers);
            break;
        case '4':
            if (checkIfThereAreAnyUsers(addressBookWithUsers))
                displaysAllUsers(addressBookWithUsers);
            break;
        case '5':
            deleteSelectedUser(addressBookWithUsers, loginUserID);

            break;
        case '6':
            editSelectedUserByID(addressBookWithUsers, loginUserID);
            break;
        case '7':
            editUserPassword(userRegistry, loginUserID);
            break;
        case '8':
            system ("cls");
            logout = false;
            cout << "Wylogowales sie";
            Sleep(1500);
            break;
        default:
            cout << "Niepoprawny wybor. Sprobuj jeszcze raz:" << endl;
            Sleep(1500);
            break;
        }
    }
}

void welcomeDisplay(vector<User> &userRegistry, int loginUserID) {
    system ("cls");
    cout << ">>>>> Witaj ! <<<<<" << endl;
    cout << "-----------------------" << endl;
    cout << "----> " << userRegistry.at(loginUserID - 1).login << " <----" << endl;
    cout << "-----------------------" << endl;
    cout << "Jestes zalogowany";
    Sleep(1500);
}

int logging(vector<User> &userRegistry) {

    system("cls");
    int loginUserID = 0;
    string login, password;

    cout << "Login: ";
    cin >> login;
    cout << "Haslo: ";
    cin >> password;

    for (int i = 0; i < (int) userRegistry.size(); i++) {
        if (userRegistry.at(i).login == login && userRegistry.at(i).password == password)
            loginUserID = userRegistry.at(i).loginUserID;
    }

    return loginUserID;
}

bool makeSureTheUserIsNotTaken(vector<User> &userRegistry, string username) {

    for (int i = 0; i < (int) userRegistry.size(); i++) {
        if (userRegistry.at(i).login == username)
            return true;
    }

    return false;
}

void endOfUserRegistrationScreen(){

    system("cls");
    cout << "-----------------------------" << endl;
    cout << "****** Konto utworzone ******" << endl;
    cout << "-----------------------------" << endl;
    Sleep(1500);

}

void userRegistrationScreen(){
    system("cls");
    cout << ">>>>> Rejestracja <<<<<" << endl;
    cout << "-----------------------" << endl;
}

void userRegistration(vector<User> &userRegistry) {

    userRegistrationScreen();
    User loginDatabase;

    int loginUserID = userRegistry.size();
    string username, password;

    if (loginUserID == 0)
        loginUserID = 1;
    else
        loginUserID = userRegistry.size() + 1;

    userFile.open("Uzytkownicy.txt", ios::out | ios::app);

    loginDatabase.loginUserID = loginUserID;

    cout << "Podaj login: ";
    cin >> username;

    while (makeSureTheUserIsNotTaken(userRegistry, username)) {
        cout << "Login jest zajety. Wpisz inny: ";
        cin >> username;
    }

    loginDatabase.login = username;

    cout << "Podaj haslo: ";
    cin >> password;
    loginDatabase.password = password;

    userRegistry.emplace_back(loginDatabase);

    userFile << loginUserID << "|" << loginDatabase.login << "|" << loginDatabase.password << "|" << endl;
    userFile.close();

    endOfUserRegistrationScreen();
}

void loadUserRegistry (vector<User> &userRegistry) {

    User loginDatabase;

    int lineNumber = 1;
    string line;

    while (getline(userFile, line, '|')) {

        if (line == "\n")
            break;

        switch(lineNumber) {
        case 1:
            loginDatabase.loginUserID = atoi(line.c_str());
            break;
        case 2:
            loginDatabase.login = line;
            break;
        case 3:
            loginDatabase.password = line;
            break;
        }
        if (lineNumber == 3) {
            lineNumber = 0;
            userRegistry.emplace_back(loginDatabase);
        }
        lineNumber++;
    }
}

void loginAndRegistrationScreen() {
    system ("cls");
    cout << ">>>>> MENU GLOWNE <<<<<" << endl;
    cout << "-----------------------" << endl;
    cout << "1. Rejestracja." << endl;
    cout << "2. Logowanie." << endl;
    cout << "9. Koniec programu." << endl;
    cout << "-----------------------" << endl;
    cout << "Twoj wybor: ";

}

void loginMenu (vector<User> &userRegistry) {

    int loginUserID = 0;

    userFile.open("Uzytkownicy.txt", ios::in);
    if (userFile.good()) {
        loadUserRegistry(userRegistry);
        userFile.close();
    }

    while (1) {

        loginAndRegistrationScreen();

        switch (getch()) {
        case '1':
            userRegistration(userRegistry);
            break;
        case '2':
            loginUserID = logging(userRegistry);
            if (loginUserID > 0) {
                welcomeDisplay(userRegistry, loginUserID);
                selectAnOptionInTheMainMenu(userRegistry, loginUserID);
            }

            else {
                cout << "Nie poprawny Login lub haslo.";
                Sleep(1500);
            }
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << "Niepoprawny wybor. Sprobuj jeszcze raz:" << endl;
            Sleep(1500);
            break;
        }
    }
}

int main() {

    vector<User> userRegistry;

    loginMenu(userRegistry);
}
