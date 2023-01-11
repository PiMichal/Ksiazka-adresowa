#include <iostream>
#include <windows.h>
#include <regex>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

fstream addressBook;

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

void saveChangesToTheFile(vector<UserData> &usersDatabase) {

    addressBook.open("Adresaci.txt", ios::out);

    for (int i = 0; i < (int) usersDatabase.size(); i++)
        addressBook << usersDatabase.at(i).id << "|" << usersDatabase.at(i).name << "|" << usersDatabase.at(i).surname << "|" << usersDatabase.at(i).phoneNumber << "|" << usersDatabase.at(i).email << "|" << usersDatabase.at(i).address << "|" << endl;

    addressBook.close();
}

void editHomeAddress(vector<UserData> &usersDatabase, int ID) {
    system ("cls");

    cout << "Zmiana adresu " << usersDatabase.at(ID).address << " na: ";
    usersDatabase.at(ID).address = loadData();
}

bool emailAddressVerificationByRegex(string newEmail) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(newEmail,pattern);
}

string emailAddressVerification (vector<UserData> &usersDatabase, string newEmail) {
    int i = 0;

    while (emailAddressVerificationByRegex(newEmail) == false && (int) usersDatabase.size() == 0) {
        cout << "Niepoprawny adres e-mail.\nWpisz jeszcze raz: ";
        newEmail = loadData();
    }

    while (i < (int) usersDatabase.size()) {

        if (emailAddressVerificationByRegex(newEmail) == false) {
            cout << "Niepoprawny adres e-mail.\nWpisz jeszcze raz: ";
            newEmail = loadData();
        } else if (usersDatabase.at(i).email == newEmail) {
            cout << "Masz juz adresata z podanym e-mailem: " << newEmail << "\nWpisz pononwnie: ";
            newEmail = loadData();
            i = -1;
        }
        i++;
    }
    return newEmail;
}

void editAddresEmail(vector<UserData> &usersDatabase, int ID) {
    system ("cls");

    string newEmail;
    cout << "Zmiana e-mail " << usersDatabase.at(ID).email << " na: ";
    newEmail = loadData();

    newEmail = emailAddressVerification(usersDatabase, newEmail);

    usersDatabase.at(ID).email = newEmail;
}

bool checkIfThereAreOnlyDigits(string newNumber) {

    return all_of(newNumber.begin(), newNumber.end(), ::isdigit);
}

string phoneNumberVerification (vector<UserData> &usersDatabase, string newNumber) {

    int i = 0;

    while (checkIfThereAreOnlyDigits(newNumber) == false && (int) usersDatabase.size() == 0) {
        cout << "Niepoprawny numer telefonu.\nWpisz jeszcze raz: ";
        newNumber = loadData();
    }

    while (i < (int) usersDatabase.size()) {
        if (checkIfThereAreOnlyDigits(newNumber) == false) {
            cout << "Niepoprawny numer telefonu.\nWpisz jeszcze raz: ";
            newNumber = loadData();
            i = -1;
        } else if (usersDatabase.at(i).phoneNumber == newNumber && (int) usersDatabase.size() != 0) {
            cout << "Masz juz adresata z podanym numerem: " << newNumber << "\nWpisz pononwnie: ";
            newNumber = loadData();
            i = -1;

        }
        i++;
    }

    return newNumber;
}

void editNumberPhone(vector<UserData> &usersDatabase, int ID) {
    system ("cls");
    string newNumber;
    cout << "Zmiana numeru telefonu " << usersDatabase.at(ID).phoneNumber << " na: ";
    newNumber = loadData();
    newNumber = phoneNumberVerification(usersDatabase, newNumber);

    usersDatabase.at(ID).phoneNumber = newNumber;
}

void editSurname(vector<UserData> &usersDatabase, int ID) {
    system ("cls");

    cout << "Zmiana nazwiska " << usersDatabase.at(ID).surname << " na: ";
    usersDatabase.at(ID).surname = loadData();
}

void editName(vector<UserData> &usersDatabase, int ID) {
    system ("cls");

    cout << "Zmiana imienia " << usersDatabase.at(ID).name << " na: ";
    usersDatabase.at(ID).name = loadData();
}

void displaysUsersByID(vector<UserData> &usersDatabase, int ID) {
    cout << "Id:                " << usersDatabase.at(ID).id << endl;
    cout << "Imie:              " << usersDatabase.at(ID).name << endl;
    cout << "Nazwisko:          " << usersDatabase.at(ID).surname << endl;
    cout << "Numer telefonu:    " << usersDatabase.at(ID).phoneNumber << endl;
    cout << "E-mail:            " << usersDatabase.at(ID).email << endl;
    cout << "Adres:             " << usersDatabase.at(ID).address << endl;
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

int searchForAUserByID(vector<UserData> &usersDatabase) {

    int userID;
    string checkID;
    system ("cls");
    cout << "Wpisz ID: ";
    cout << endl;
    checkID = loadData();
    while (checkIfThereAreOnlyDigits(checkID) == false) {
        cout << "Wpisano: " << checkID << "\nNalezy wpisac ID skladajace sie z samych liczb: ";
        checkID = loadData();
    }
    userID = atoi(checkID.c_str());

    for (int i = 0; i < (int) usersDatabase.size(); i++) {
        if (userID == usersDatabase.at(i).id)
            return i;
    }
    return -1;
}

void editSelectedUserByID(vector<UserData> &usersDatabase) {

    int ID = searchForAUserByID(usersDatabase);
    bool backToMenu = true;

    if (ID < 0 ) {
        cout << "Nie ma takiego adresata";
        Sleep(1500);
        backToMenu = false;
    }

    while (backToMenu && ID >= 0) {
        displaysEditMenu();
        displaysUsersByID(usersDatabase, ID);
        switch (getch()) {
        case '1':
            editName(usersDatabase, ID);
            break;
        case '2':
            editSurname(usersDatabase, ID);
            break;
        case '3':
            editNumberPhone(usersDatabase, ID);
            break;
        case '4':
            editAddresEmail(usersDatabase, ID);
            break;
        case '5':
            editHomeAddress(usersDatabase, ID);
            break;
        case '6':
            backToMenu = false;
            break;
        default:
            cout << "Niepoprawny wybor." << endl;
            Sleep(1000);
            break;
        }
        saveChangesToTheFile(usersDatabase);
    }
}

void loadTheDataFileIntoTheProgram(vector<UserData> &usersDatabase, UserData &user) {

    addressBook.open("Adresaci.txt", ios::in);

    int lineNumber = 1;
    string line;

    while (getline(addressBook, line, '|')) {

        if (line == "\n")
            break;

        switch(lineNumber) {
        case 1: {
            user.id = atoi(line.c_str());
            break;
        }
        case 2: {
            user.name = line;
            break;
        }
        case 3: {
            user.surname = line;
            break;
        }
        case 4: {
            user.phoneNumber = line;
            break;
        }
        case 5: {
            user.email = line;
            break;
        }
        case 6: {
            user.address = line;
            break;
        }
        }
        if (lineNumber == 6) {
            lineNumber = 0;
            usersDatabase.emplace_back(user);
        }
        lineNumber++;
    }
    addressBook.close();
}

void deleteSelectedUser(vector<UserData> &usersDatabase) {
    system ("cls");

    int ID = searchForAUserByID(usersDatabase);
    if (ID < 0 ) {
        cout << "Nie ma takiego adresata";
        Sleep(1500);
    }
    else{
        displaysUsersByID(usersDatabase, ID);
        cout << "Czy napewno chcesz usunac adresata ? " << endl;
        cout << "t/n: ";
    }

    if (ID >= 0 && getch() == 't') {

        addressBook.open("Adresaci.txt", ios::out);

        if (usersDatabase.size() == 1) {
            remove("Adresaci.txt");
            addressBook.close();
            usersDatabase.clear();
            system ("cls");
            cout << "\n>>>>> Adresat zostal usuniety. <<<<<";
            Sleep(1500);

        } else {

            for (int i = 0; i < (int) usersDatabase.size(); i++) {
                if (i != ID)
                    addressBook << usersDatabase.at(i).id << "|" << usersDatabase.at(i).name << "|" << usersDatabase.at(i).surname << "|" << usersDatabase.at(i).phoneNumber << "|" << usersDatabase.at(i).email << "|" << usersDatabase.at(i).address << "|" << endl;
            }
            addressBook.close();
            usersDatabase.clear();

            system ("cls");
            cout << "\n>>>>> Adresat zostal usuniety. <<<<<";
            Sleep(1500);
        }
    }

}

void displaysAllUsers(vector<UserData> &usersDatabase) {

    system("cls");

    for (int i = 0; i < (int) usersDatabase.size(); i++) {
        cout << usersDatabase[i].id << endl;
        cout << usersDatabase[i].name << endl;
        cout << usersDatabase[i].surname << endl;
        cout << usersDatabase[i].phoneNumber << endl;
        cout << usersDatabase[i].email << endl;
        cout << usersDatabase[i].address << endl << endl;
    }
    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . ." << endl;
    getch();
}

void searchBySurname(vector<UserData> &usersDatabase) {
    bool check = true;
    string wantedSurname;
    system ("cls");
    cout << "Wpisz nazwisko: ";
    wantedSurname = loadData();
    cout << endl;
    for (int i = 0; i < (int) usersDatabase.size(); i++) {
        if (wantedSurname == usersDatabase.at(i).surname) {
            displaysUsersByID(usersDatabase, i);
            check = false;
        }
    }
    if (check == true)
        cout << "Nie ma adresata o nazwisku: " << wantedSurname << endl;

    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . .";
    getch();
}

void searchByName(vector<UserData> &usersDatabase) {
    bool check = true;
    string wantedName;
    system ("cls");
    cout << "Wpisz imie: ";
    wantedName = loadData();
    cout << endl;
    for (int i = 0; i < (int) usersDatabase.size(); i++) {
        if (wantedName == usersDatabase.at(i).name) {
            displaysUsersByID(usersDatabase, i);
            check = false;
        }
    }
    if (check == true)
        cout << "Nie ma takiego adresata o imieniu: " << wantedName << endl;

    cout << "\nNacisnij dowolny klawisz, aby kontynuowac . . ." << endl;
    getch();
}

bool checkIfThereAreAnyUsers (vector<UserData> &usersDatabase) {

    if ((int) usersDatabase.size() == 0) {
        system ("cls");
        cout << "Ksiazka adresowa jest pusta !!!";
        Sleep(1500);;
        return false;
    }
    return true;
}

void dataLogging(vector<UserData> &usersDatabase) {

    system("cls");

    int ID = usersDatabase.size();
    string name, surname, phoneNumber, email, address;

    addressBook.open("Adresaci.txt", ios::out | ios::app);

    if (ID == 0)
        ID = 1;
    else
        ID = usersDatabase.at(ID - 1).id + 1;

    cout << "Wpisz imie: ";
    name = loadData();

    cout << "Wpisz nazwisko: ";
    surname = loadData();

    cout << "Wpisz numer telefonu: ";
    phoneNumber = loadData();
    phoneNumber = phoneNumberVerification(usersDatabase, phoneNumber);

    cout << "Wpisz adres e-mail: ";
    email = loadData();
    email = emailAddressVerification(usersDatabase, email);

    cout << "Wpisz adres zamieszkania: ";
    address = loadData();

    usersDatabase.push_back({ID, name, surname, phoneNumber, email, address});

    cout << "Adresat zostal dodany do ksiazki adresowej." << endl;
    Sleep(1000);

    addressBook << ID << "|" << name << "|" << surname << "|" << phoneNumber << "|" << email << "|" << address << "|" << endl;

    addressBook.close();

}

void displaysTheMainMenu() {
    system ("cls");
    cout << ">>>>> KSIAZKA ADRESOWA <<<<<" << endl;
    cout << endl;
    cout << "1. Dodaj adresata." << endl;
    cout << "2. Wyszukaj po imieniu." << endl;
    cout << "3. Wyszukaj po nazwisku." << endl;
    cout << "4. Wyswietl wszystkich adresatow." << endl;
    cout << "5. Usun adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "9. Zakoncz program." << endl;
}

void selectAnOptionInTheMainMenu(vector<UserData> &usersDatabase, UserData &user) {

    while (1) {

        displaysTheMainMenu();

        switch (getch()) {
        case '1':
            dataLogging(usersDatabase);
            break;
        case '2':
            if (checkIfThereAreAnyUsers(usersDatabase))
                searchByName(usersDatabase);
            break;
        case '3':
            if (checkIfThereAreAnyUsers(usersDatabase))
                searchBySurname(usersDatabase);
            break;
        case '4':
            if (checkIfThereAreAnyUsers(usersDatabase))
                displaysAllUsers(usersDatabase);
            break;
        case '5':
            deleteSelectedUser(usersDatabase);
            loadTheDataFileIntoTheProgram(usersDatabase, user);
            break;
        case '6':
            editSelectedUserByID(usersDatabase);
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

    UserData user;
    vector<UserData> usersDatabase;

    if (addressBook.good()) {
        loadTheDataFileIntoTheProgram(usersDatabase, user);
    }

    selectAnOptionInTheMainMenu(usersDatabase, user);
}
