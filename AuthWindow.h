#pragma once
#include "BaseWindow.h"

class AuthWindow : public BaseWindow {
private:
    string login;
    string password;
public:
    int show() {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "          ÂÕÎÄ              " << endl;
        cout << "==============================" << endl;

        do
        {
            system.clearArea(3, 2);
            login = system.getInputWithMask("Ëîãèí: ", 7, 3, false);
            if (login == "_") return 0;
            password = system.getInputWithMask("Ïàðîëü: ", 7, 4, true);
            if (password == "_") return 0;
        } while (login.empty() || password.empty());

        return 1;
    }

    void close() override {
        system.clearWindow();
    }

    string getPassword() {
        return this->password;
    }

    string getLogin() {
        return this->login;
    }
};