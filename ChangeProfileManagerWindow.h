#pragma once
#include "BaseWindow.h"
#include "Manager.h"
#include "FileManager.h"

class ChangeProfileManagerWindow : public BaseWindow {
private:
    string newEmail;
    string newName;
    Manager* manager;
    FileManager<Manager> managerFileManager;
public:
    ChangeProfileManagerWindow(Manager* manager, FileManager<Manager> managerFileManager)
        : manager(manager), managerFileManager(managerFileManager) { }

    int show() {
        string cases[4] = { "Изменить email", "Изменить имя", "Сохранить изменения", "Выход" };
        while (true) {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "      Изменение профиля       " << endl;
            cout << "==============================" << endl;
            switch (system.getUserChoice(4, cases))
            {
            case 4:
            case -1:
                close();
                return 0;
            case 1:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Изменение email       " << endl;
                cout << "==============================" << endl;
                do
                {
                    system.clearArea(4, 1);
                    newEmail = system.getInputWithMask("Введите новый email: ", 0, 4, false);
                    if (newEmail == "_") {
                        newEmail = "";
                        break;
                    }
                } while (!system.isValidEmail(newEmail));
                break;
            case 2:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Изменение имени       " << endl;
                cout << "==============================" << endl;
                do
                {
                    system.clearArea(4, 1);
                    newName = system.getInputWithMask("Введите новое имя: ", 0, 4, false);
                    if (newName == "_") {
                        newName = "";
                        break;
                    }
                } while (newName == "");
                break;
            case 3:

                int boolChange = false;
                    if (newEmail != "") {
                        boolChange = true;
                        (*manager).setEmail(newEmail);
                    }

                    if (newName != "") {
                        boolChange = true;
                        (*manager).setName(newName);
                    }

                    if (boolChange) {
                        managerFileManager.rewriteFile(*manager);
                    }
                close();
                return 1;
            }
        }
    }

    void close() override {
        system.clearWindow();
    }
};