#pragma once
#include "BaseWindow.h"

class BeginWindow : public BaseWindow {
public:
    int show() {
        string cases[3] = { "��������������", "������������������", "�����" };
        while (true) {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "           ����              " << endl;
            cout << "==============================" << endl;
            return system.getUserChoice(3, cases);
        }
    }

    void close() override {
        system.clearWindow();
    }
};