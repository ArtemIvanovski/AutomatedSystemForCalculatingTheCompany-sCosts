#pragma once
#include "List.h"
#include "FileManager.h"
#include "ErrorWindow.h"

class ManWithMyProjectWindow : public BaseWindow {
private:
    List<Project> projects;
    FileManager<Project> projectFileManager;
    int id;
public:
    ManWithMyProjectWindow(List<Project> projects, FileManager<Project> projectFileManager, int id)
        : projects(projects), projectFileManager(projectFileManager), id(id){ }
    
    int show() {
        string cases[5] = { "Просмотр всех проектов", "Добавление проекта", "Поиск проекта", "Удалить проект", "Выход" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "=====================================" << endl;
                cout << "   Манипуляции со своими проектами" << endl;
                cout << "=====================================" << endl;
                switch (system.getUserChoice(5, cases)) {
                case -1:
                case 5:
                    close();
                    return -1;
                case 1:
                    displayProject();
                    break;
                case 2:
                    addProject();
                    break;
                case 3:
                    findProject();
                    break;
                case 4:
                    removeProject();
                    break;
                }
            }
            catch (const CustomException& msg)
            {
                ErrorWindow errorWindow(msg.what());
            }
        }
    }

    void close() override {
        system.clearWindow();
    }

private:
    void removeProject() {
        system.clearWindow();
        displayProject(false);
        int length = 0;
        for (int i = 0; i < projects.length(); i++) {
            if (id == projects[i].getIdCreator())
                length++;
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id проекта, который хотите удалить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!projects.find(id));

        if (id != -1) {
            system.clearWindow();
            Project removeProject = projects.getDataById(id);
            projectFileManager.deleteByData(removeProject);
            projects = projectFileManager.readFromFile();
        }
    }


    void addProject() {
        string name = "", description = "";
        double budget = 0.0;
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "    Добавление проекта" << endl;
        cout << "==============================" << endl;
        do
        {
            system.clearArea(3, 7);
            name = system.getInputWithMask("Введите название проекта: ", 0, 3, false);
            if (name == "_")
                return;

            description = system.getInputWithMask("Введите описание проекта: ", 0, 4, false);
            if (description == "_")
                return;

            system.printWithColor("Введите бюджет проекта: ", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 0, 5, true);
            budget = system.inputDouble();
            if (budget == -1.0)
                return;

        } while (name.empty() || description.empty() || budget == 0.0);
        Project project(projectFileManager.getUniqueID(), name, description, id, budget);
        projectFileManager.writeToFile(project);
        projects = projectFileManager.readFromFile();
    }


    void findProject() {
        system.clearWindow();
        string searchStr = "";
        char input;
        bool flag = true;
        bool flagCaption = true;
        int projectCount = projects.length();

        if (projects.length() == 0 || !projects.getOwnValueProject(id)) {
            throw CustomException("Нет проектов");
        }

        Project project;

        while (true) {
            if (flag) {
                cout << "Поиск: " << searchStr << endl;
                flag = false;
            }

            input = _getch();
            system.clearWindow();

            if (input == 27) {
                return;
            }
            else if (input == 8 && !searchStr.empty()) {
                searchStr.pop_back();
            }
            else {
                searchStr += input;
            }

            cout << "Поиск: " << searchStr << endl;

            bool found = false;
            flagCaption = true;

            for (int i = 0; i < projectCount; i++) {
                if (projects[i].getIdCreator() != id)
                    continue;

                project = projects[i];

                if (to_string(project.getId()).find(system.toLower(searchStr)) != string::npos ||
                    system.toLower(project.getName()).find(system.toLower(searchStr)) != string::npos ||
                    to_string(project.getBudget()).find(system.toLower(searchStr)) != string::npos ||
                    system.toLower(project.getDescription()).find(system.toLower(searchStr)) != string::npos ||
                    system.toLower(project.getStatus()).find(system.toLower(searchStr)) != string::npos) {

                    if (flagCaption) {
                        cout << endl;
                        project.displayProjectTableHeader();
                        flagCaption = false;
                    }

                    project.displayProjectInfo();
                    found = true;
                }
            }

            if (!found) {
                cout << endl << "Ничего не найдено" << endl;
            }
        }
    }

    void displayProject(bool withSort = true) {
        string cases[4] = { "По id", "По названию", "По дате созданию", "По статусу" };
        while (true) {

            system.clearWindow();
            

            if (projects.length() == 0 || !projects.getOwnValueProject(id)) {
                throw CustomException("Нет проектов");
            }

            projects[0].displayProjectTableHeader();

            for (int i = 0; i < projects.length(); i++) {
                if (id == projects[i].getIdCreator())
                    projects[i].displayProjectInfo();
            }


            if (withSort) {
                switch (system.getUserChoice(4, cases))
                {
                case -1:
                    return;
                case 1:
                    projects.sortById();
                    break;
                case 2:
                    projects.sortByName();
                    break;
                case 3:
                    projects.sortByDate();
                    break;
                case 4:
                    projects.sortByStatus();
                    break;
                }
            }
            else {
                return;
            }
        }
    }
};