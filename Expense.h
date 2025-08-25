#pragma once
#include "Liberies.h"


class Expense {
protected:
    int id;
    int idProject;
    double amount;
    time_t date;               
    string description;        

public:
    Expense() : id(0), idProject(0), amount(0.0), date(time(nullptr)), description("") {}

    Expense(int id, int idProject, double amount, const string& desc)
        : id(id), idProject(idProject), amount(amount), date(time(nullptr)), description(desc) {}

    int getId() const { return id; }

    int getIdProject() { return idProject; }

    double getAmount() const { return amount; }
    void setAmount(double amount) { this->amount = amount; }

    int getMonth() const {
        tm* timeinfo = localtime(&date); 
        return timeinfo->tm_mon + 1; 
    }

    time_t getDate() const { return date; }
    string getDescription() const { return description; }
    void setDescription(const string& desc) { description = desc; }

    friend ostream& operator<<(ostream& os, const Expense& obj) {
        os.write((const char*)&obj.id, sizeof(obj.id));
        os.write((const char*)&obj.idProject, sizeof(obj.idProject));
        os.write((const char*)&obj.amount, sizeof(obj.amount));
        os.write((const char*)&obj.date, sizeof(obj.date));

        int descSize = obj.description.size();
        os.write((const char*)&descSize, sizeof(descSize));
        os.write(obj.description.data(), descSize);

        return os;
    }

    friend istream& operator>>(istream& is, Expense& obj) {
        if (is.read((char*)&obj.id, sizeof(obj.id))) {
            is.read((char*)&obj.idProject, sizeof(obj.idProject));
            is.read((char*)&obj.amount, sizeof(obj.amount));
            is.read((char*)&obj.date, sizeof(obj.date));

            int descSize;
            is.read((char*)&descSize, sizeof(descSize));
            obj.description.resize(descSize);
            is.read(&obj.description[0], descSize);
        }
        else {
            is.setstate(ios::failbit);
        }
        return is;
    }
};