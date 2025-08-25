#pragma once
#include "BaseWindow.h"

class TopUpBudgetWindow : public BaseWindow {
private:
    double value;
public:
    int show(bool isBudgetProject) {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "       ���������� �������  " << endl;
        cout << "==============================" << endl;
        
        if (isBudgetProject) {
            cout << "������� ����� ��� ���������� ������� �������: ";
        }
        else {
            cout << "������� ����� ��� ���������� ������ �������: ";
        }
        
        value = system.inputDouble();
        if (value == -1.0)
            return 0;
        else
            return 1;
    }

    double getValue() { return value; }

    void close() override {
        system.clearWindow();
    }
};