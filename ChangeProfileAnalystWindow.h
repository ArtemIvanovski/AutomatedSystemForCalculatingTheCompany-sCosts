#pragma once
#include "BaseWindow.h"
#include "Analyst.h"
#include "FileManager.h"

class ChangeProfileAnalystWindow : public BaseWindow {
private:
    string newEmail;
    string newName;
    string newTool;
    Analyst* analyst;
    FileManager<Analyst> analystFileManager;
public:
    ChangeProfileAnalystWindow(Analyst* analyst, FileManager<Analyst> analystFileManager)
        : analyst(analyst), analystFileManager(analystFileManager) { }

    int show() {
        string cases[5] = { "Изменить email", "Изменить имя", "Добавить инструмент", "Удалить инструмент", "Выход" };
        while (true) {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "      Изменение профиля       " << endl;
            cout << "==============================" << endl;
            switch (system.getUserChoice(5, cases))
            {
            case 5:
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
                
                if (newEmail != "") {
                    (*analyst).setEmail(newEmail);
                    analystFileManager.rewriteFile(*analyst);
                }
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
                if (newName != "") {
                    (*analyst).setName(newName);
                    analystFileManager.rewriteFile(*analyst);
                }
                break;
            case 3:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Добавление инструмента       " << endl;
                cout << "==============================" << endl;
                do
                {
                    system.clearArea(4, 1);
                    newTool = system.getInputWithMask("Введите новый инструмент: ", 0, 4, false);
                    if (newTool == "_") {
                        newTool = "";
                        break;
                    }
                } while (newTool == "");
                if (newTool != "") {
                    (*analyst).addDataAnalysisTool(newTool);
                    analystFileManager.rewriteFile(*analyst);
                }
                break;
            case 4: {
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Удаление инструмента       " << endl;
                cout << "==============================" << endl;

                vector<string> tools = (*analyst).getDataAnalysisTools();
                string* toolCases = new string[tools.size()]; 

                copy(tools.begin(), tools.end(), toolCases);

                int choice = system.getUserChoice(tools.size(), toolCases); 

                if (choice != -1) {
                    (*analyst).removeDataAnalysisTool(toolCases[choice - 1]); 
                    analystFileManager.rewriteFile(*analyst);
                }

                delete[] toolCases; 
            }
                  break;
            }
        }
    }

    void close() override {
        system.clearWindow();
    }
};