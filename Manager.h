#pragma once
#include "User.h"
#include "CustomException.h"

class Manager : public User {
private:
    double budgetLimit;

public:
    Manager() : User(), budgetLimit(0) {}

    Manager(int managerId, const string& managerName, const string& managerEmail, double initialBudget)
        : User(managerId, managerName, managerEmail), budgetLimit(initialBudget) {}

    double getBudgetLimit() const { return budgetLimit; }

    friend void increaseBudget(Manager& manager, double amount);
    friend void decreaseBudget(Manager& manager, double amount);

    void displayManagerTableHeader() const {
        cout << "===============================================================================" << endl;
        cout << "| ID менеджера |       Имя менеджера      |  Email менеджера |  Лимит бюджета |" << endl;
        cout << "===============================================================================" << endl;
    }

    void displayManagerInfo() const {
        cout << "| " << setw(12) << id
            << " | " << setw(24) << name
            << " | " << setw(16) << email
            << " | " << setw(14) << fixed << setprecision(2) << budgetLimit << " |" << endl;
        cout << "===============================================================================" << endl;
    }

    friend ostream& operator<<(ostream& os, const Manager& obj) {
        os << static_cast<const User&>(obj);
        os.write((const char*)&obj.budgetLimit, sizeof(obj.budgetLimit));
        return os;
    }

    friend istream& operator>>(istream& is, Manager& obj) {
        is >> static_cast<User&>(obj);
        is.read((char*)&obj.budgetLimit, sizeof(obj.budgetLimit));
        return is;
    }
};

void increaseBudget(Manager& manager, double amount) {
    manager.budgetLimit += amount;
    if (manager.budgetLimit < 0)
        manager.budgetLimit = 0;
}

void decreaseBudget(Manager& manager, double amount) {
    if (amount <= 0) {
        throw CustomException("Сумма, подлежащая уменьшению, должна быть положительной");
    }
    if (amount > manager.budgetLimit) {
        throw CustomException("Сумма превышает текущий бюджетный лимит");
    }
    manager.budgetLimit -= amount;
}