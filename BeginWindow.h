#pragma once
#include "BaseWindow.h"

class BeginWindow : public BaseWindow {
public:
    int show() {
        string cases[3] = { "Авторизоваться", "Зарегистрироваться", "Выход" };
        while (true) {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "           МЕНЮ              " << endl;
            cout << "==============================" << endl;
            return system.getUserChoice(3, cases);
        }
    }

    void close() override {
        system.clearWindow();
    }
};