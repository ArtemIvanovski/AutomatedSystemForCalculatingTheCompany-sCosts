#pragma once
#include "Liberies.h"

class Data {
private:
    int id;
    string login;
    string passwordHash;
    string role;

    static const uint32_t FNV_prime = 0x01000193;
    static const uint32_t offset_basis = 0x811C9DC5;

    string hashPassword(const string& password) const {
        uint32_t hash = offset_basis;
        for (char ch : password) {
            hash ^= static_cast<uint32_t>(ch);
            hash *= FNV_prime;
        }
        stringstream ss;
        ss << hex << setw(8) << setfill('0') << hash;
        return ss.str();
    }

public:
    Data(): id(0), login(""), passwordHash(""), role("") {}

    Data(int id, const string& login, const string& password, const string& role)
        : id(id), login(login), passwordHash(hashPassword(password)), role(role) {}

    int verify(const string& inputLogin, const string& inputPassword) const {
        string inputPasswordHash = hashPassword(inputPassword);

        if (login == inputLogin && passwordHash == inputPasswordHash) {
            return id;
        }
        return 0; 
    }

    int getId() const { return id; }
    string getLogin() const { return login; }
    string getRole() const { return role; }

    friend ostream& operator<<(ostream& os, const Data& obj) {
        os.write((const char*)&obj.id, sizeof(obj.id));

        int infoSize = obj.login.size();
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(obj.login.data(), infoSize);

        infoSize = obj.passwordHash.size();
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(obj.passwordHash.data(), infoSize);

        infoSize = obj.role.size();
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(obj.role.data(), infoSize);

        return os;
    }

    friend istream& operator>>(istream& is, Data& obj) {
        if (is.read((char*)&obj.id, sizeof(obj.id))) {
            int infoSize;

            is.read((char*)&infoSize, sizeof(infoSize));
            obj.login.resize(infoSize);
            is.read(&obj.login[0], infoSize);

            is.read((char*)&infoSize, sizeof(infoSize));
            obj.passwordHash.resize(infoSize);
            is.read(&obj.passwordHash[0], infoSize);

            is.read((char*)&infoSize, sizeof(infoSize));
            obj.role.resize(infoSize);
            is.read(&obj.role[0], infoSize);
        }
        else {
            is.setstate(ios::failbit);
        }

        return is;
    }
};