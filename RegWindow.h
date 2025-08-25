#pragma once
#include "BaseWindow.h"

class RegWindow : public BaseWindow {
private:
    string login;
    string password;
    string name;
    string email;
    string role;
public:
    int show() {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "          РЕГИСТРАЦИЯ         " << endl;
        cout << "==============================" << endl;

        do
        {
            system.clearArea(3, 7);
            name = system.getInputWithMask("Введите имя: ", 7, 3, false);
            if (name == "_") return 0;
            do
            {
                system.clearArea(4, 1);
                email = system.getInputWithMask("Введите почту: ", 7, 4, false);
                if (email == "_") return 0;
            } while (!system.isValidEmail(email));
            
            //TODO: add checker for login
            login = system.getInputWithMask("Придумайте логин: ", 7, 5, false);
            if (login == "_") return 0;

            password = system.getInputWithMask("Придумайте пароль: ", 7, 6, true);
            if (password == "_") return 0;

            system.printWithColor("Выберете роль пользователя : \n", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 7, 8, true);

            string cases[2] = { "Администратор", "Пользователь" };
            switch (system.getUserChoice(2, cases, 10, 9, true)) {
            case -1:
                return 0;
            case 1:
                role = "manager";
                break;
            case 2:
                role = "analyst";
                break;
            }
        } while (name.empty() || password.empty() || login.empty() || role.empty());

        return 1;
    }

    void close() override {
        system.clearWindow();
    }

    string getEmail() {
        return this->email;
    }

    string getName() {
        return this->name;
    }

    string getPassword() {
        return this->password;
    }

    string getLogin() {
        return this->login;
    }

    string getRole() {
        return this->role;
    }
};