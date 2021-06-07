#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
using namespace std;

void get_data(string data, string u[], string p[]) {
    int u_pos = 1, p_pos = 1;
    bool usr_name_selected = true;
    string usr_name_temp, passwd_temp;
    for (int x = 0; x < data.length(); x++) {
        if (data.at(x) == '\n')
            continue;
        if (data.at(x) == ':') {
            x++;
            usr_name_selected = true;
            p[p_pos - 1] = passwd_temp;
            passwd_temp = "";
            if (x != 1)
                p_pos++;

        } else if (data.at(x) == '*') {
            x++;
            usr_name_selected = false;
            u[u_pos - 1] = usr_name_temp;
            usr_name_temp = "";
            u_pos++;
        } else if (data.at(x) == ';') {
            p[p_pos - 1] = passwd_temp;
            return;
        }
        if (usr_name_selected) {
            usr_name_temp += data.at(x);

        } else {
            passwd_temp += data.at(x);
        }
    }
}
//0x178aeb8
int main() {
    bool log_success = false;
    auto* usernames = new string[500];
    auto* passwords = new string[500];
    ifstream readfile("userdata.txt");
    if (!readfile.is_open()) {
        ofstream writefile("userdata.txt");
        writefile.close();
    }
    string str((istreambuf_iterator<char>(readfile)), istreambuf_iterator<char>());
    get_data(str, usernames, passwords);
    string login;
    string passwd;
    int choice;
    cout << "0: Register" << endl << "1: Login" << endl << "Your choice: ";
    cin >> choice;
    if (choice)
        if (str.empty()) {
            cout << "No users is on the list. First create a user" << endl;
            return 0;
        }
    system("cls");
    cout << "   Login   : ";
    cin >> login;
    cout << "  Password : ";
    cin >> passwd;
    cout << endl;
    //Registration
    if (!choice) {
        ofstream writefile("userdata.txt", ios_base::trunc);
        if (!str.empty()) {
            for (int x = 0; x < 500; x++) {
                if (usernames[x].empty()) {
                    continue;
                } else {
                    for (int i = 0; i < 500; i++) {
                        if (usernames[i].empty())
                            continue;
                        else if (usernames[i] == login) {
                            cout << "Username is already exist!!";
                            return 0;
                        }
                    }
                    str.erase(prev(str.end()));
                    writefile << str << endl << ":" << login << "*" << passwd << ";";
                    writefile.close();
                    cout << "Registration Successful!!" << endl;
                    return 0;
                }
            }
        }
        else {
            writefile << ":" << login << "*" << passwd << ";";
            cout << "Registration Successful!!" << endl;
        }
    }
    //Authorization
    else if (choice) {
        for (int x = 0; x < 500; x++) {
            if (usernames[x].empty())
                continue;
            else if (usernames[x] == login) {
                if (passwords[x] == passwd)
                    log_success = true;
                else {
                    cout << "Wrong password!!" << endl;
                    return 0;
                }
            }
        }
        if (log_success) {
            cout << "Authorization Successful!!" << endl;
        }
        else {
            cout << "Wrong login or password!!" << endl;
        }
    }

    return 0;
}