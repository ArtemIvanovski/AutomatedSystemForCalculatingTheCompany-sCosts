#pragma once
#include "BaseWindow.h"

class TopUpBudgetWindow : public BaseWindow {
private:
    double value;
public:
    int show(bool isBudgetProject) {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "       Пополнение бюджета  " << endl;
        cout << "==============================" << endl;
        
        if (isBudgetProject) {
            cout << "Введите сумму для пополнения бюджета проекта: ";
        }
        else {
            cout << "Введите сумму для увеличения лимита бюджета: ";
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