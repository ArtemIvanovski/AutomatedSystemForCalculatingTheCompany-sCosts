#pragma once
#include "Expense.h"

class IndirectExpense : public Expense {
private:
    string indirectExpenseType;
    double allocationPercentage;

public:
    IndirectExpense() : Expense(), indirectExpenseType(""), allocationPercentage(0.0) {}

    IndirectExpense(int id, int idProject, double amount, const string& desc, const string& expenseType, double allocation)
        : Expense(id, idProject, amount, desc), indirectExpenseType(expenseType), allocationPercentage(allocation) {}

    string getIndirectExpenseType() const { return indirectExpenseType; }
    void setIndirectExpenseType(const string& expenseType) { indirectExpenseType = expenseType; }

    double getAllocationPercentage() const { return allocationPercentage; }
    void setAllocationPercentage(double allocation) { allocationPercentage = allocation; }


    void displayIndirectExpenseTableHeader() const {
        cout << "==============================================================================================================\n";
        cout << "| ID расхода  | ID проекта | Сумма  | Описание             | Тип косвенных расходов  | Процент распределения |\n";
        cout << "==============================================================================================================\n";
    }

    void writeIndirectExpenseTableHeader(ofstream &outputFile) const {
        outputFile << "==============================================================================================================\n";
        outputFile << "| ID расхода  | ID проекта | Сумма  | Описание             | Тип косвенных расходов  | Процент распределения |\n";
        outputFile << "==============================================================================================================\n";
    }

    void writeIndirectExpenseInfo(ofstream &outputFile) const {
        outputFile << "| " << setw(11) << id
            << " | " << setw(10) << idProject
            << " | " << setw(6) << amount
            << " | " << setw(20) << description
            << " | " << setw(23) << indirectExpenseType
            << " | " << setw(21) << allocationPercentage << " |\n";
        outputFile << "==============================================================================================================\n";
    }

    void displayIndirectExpenseInfo() const {
        cout << "| " << setw(11) << id
            << " | " << setw(10) << idProject
            << " | " << setw(6) << amount
            << " | " << setw(20) << description
            << " | " << setw(23) << indirectExpenseType
            << " | " << setw(21) << allocationPercentage << " |\n";
        cout << "==============================================================================================================\n";
    }

    friend ostream& operator<<(ostream& os, const IndirectExpense& obj) {
        os << static_cast<const Expense&>(obj);

        int typeSize = obj.indirectExpenseType.size();
        os.write((const char*)&typeSize, sizeof(typeSize));
        os.write(obj.indirectExpenseType.data(), typeSize);

        os.write((const char*)&obj.allocationPercentage, sizeof(obj.allocationPercentage));

        return os;
    }

    friend istream& operator>>(istream& is, IndirectExpense& obj) {
        is >> static_cast<Expense&>(obj);

        int typeSize;
        if (is.read((char*)&typeSize, sizeof(typeSize))) {
            obj.indirectExpenseType.resize(typeSize);
            is.read(&obj.indirectExpenseType[0], typeSize);

            is.read((char*)&obj.allocationPercentage, sizeof(obj.allocationPercentage));
        }
        else {
            is.setstate(ios::failbit);
        }
        return is;
    }
};