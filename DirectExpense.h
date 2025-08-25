#pragma once
#include "Expense.h"


class DirectExpense : public Expense {
private:
    string directExpenseType;

public:
    DirectExpense() : Expense(), directExpenseType("") {}

    DirectExpense(int id, int idProject, double amount, const string& desc, const string& expenseType)
        : Expense(id, idProject, amount, desc), directExpenseType(expenseType) {}

    string getDirectExpenseType() const { return directExpenseType; }
    void setDirectExpenseType(const string& expenseType) { directExpenseType = expenseType; }


    void displayDirectExpenseTableHeader() const {
        cout << "===================================================================================\n";
        cout << "| ID расхода  | ID проекта | Сумма  | Описание             |  Тип прямых расходов |\n";
        cout << "===================================================================================\n";
    }

    void writeDirectExpenseTableHeader(ofstream &outputFile) {
        outputFile << "===================================================================================\n";
        outputFile << "| ID расхода  | ID проекта | Сумма  | Описание             |  Тип прямых расходов |\n";
        outputFile << "===================================================================================\n";
    }

    void writeDirectExpenseInfo(ofstream &outputFile) {
        outputFile << "| " << setw(11) << id
            << " | " << setw(10) << idProject
            << " | " << setw(6) << amount
            << " | " << setw(20) << description
            << " | " << setw(20) << directExpenseType << " |\n";
        outputFile << "===================================================================================\n";
    }

    void displayDirectExpenseInfo() const {
        cout << "| " << setw(11) << id
            << " | " << setw(10) << idProject
            << " | " << setw(6) << amount
            << " | " << setw(20) << description
            << " | " << setw(20) << directExpenseType << " |\n";
        cout << "===================================================================================\n";
    }

    friend ostream& operator<<(ostream& os, const DirectExpense& obj) {
        os << static_cast<const Expense&>(obj);

        int typeSize = obj.directExpenseType.size();
        os.write((const char*)&typeSize, sizeof(typeSize));
        os.write(obj.directExpenseType.data(), typeSize);

        return os;
    }

    friend istream& operator>>(istream& is, DirectExpense& obj) {
        is >> static_cast<Expense&>(obj);

        int typeSize;
        if (is.read((char*)&typeSize, sizeof(typeSize))) {
            obj.directExpenseType.resize(typeSize);
            is.read(&obj.directExpenseType[0], typeSize);
        }
        else {
            is.setstate(ios::failbit);
        }
        return is;
    }
};