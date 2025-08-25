#pragma once
#include "Liberies.h"

class User {
protected:
    int id;             
    string name;        
    string email;       

public:
    User (): id(0), name(""), email("") {}
    User(int userId, const string& userName, const string& userEmail)
        : id(userId), name(userName), email(userEmail) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void setName(const string& newName) { name = newName; }
    void setEmail(const string& newEmail) { email = newEmail; }

    friend ostream& operator<<(ostream& os, const User& obj) {
        os.write((const char*)&obj.id, sizeof(obj.id));

        int infoSize = obj.name.size();
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(obj.name.data(), infoSize);

        infoSize = obj.email.size();
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(obj.email.data(), infoSize);

        return os;
    }

    friend istream& operator>>(istream& is, User& obj) {
        if (is.read((char*)&obj.id, sizeof(obj.id))) {
            int infoSize;

            is.read((char*)&infoSize, sizeof(infoSize));
            obj.name.resize(infoSize);
            is.read(&obj.name[0], infoSize);

            is.read((char*)&infoSize, sizeof(infoSize));
            obj.email.resize(infoSize);
            is.read(&obj.email[0], infoSize);
        }
        else {
            is.setstate(ios::failbit);
        }

        return is;
    }
};