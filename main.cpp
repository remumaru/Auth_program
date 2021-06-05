#include <iostream>
#include <unistd.h>
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
    auto* usernames = new string[500];
    auto* passwords = new string[500];
    ofstream writefile("userdata.txt", ios_base::app | ios_base::ate);
    ifstream readfile("userdata.txt");
    string login;
    string passwd;
    int choice;
    cout << "0: Register" << endl << "1: Login" << endl << "Your choice: ";
    cin >> choice;
    system("clear");
    cout << "  Login  : ";
    cin >> login;
    cout << "Password : ";
    cin >> passwd;
    system("clear");
    if (!choice) {

    }
    else if (choice) {
        string str((istreambuf_iterator<char>(readfile)), istreambuf_iterator<char>());
        get_data(str, usernames, passwords);
        for (int x = 0, y = x; x < 500; x++, y++) {
            if (usernames[x].empty())
                continue;
            cout << usernames[x] << " * " << passwords[y] << endl;
        }
    }
    writefile.close();
    return 0;
}