#pragma once
#include "ErrorWindow.h"
#include "FileManager.h"
#include "Manager.h"
#include "ChangeProfileManagerWindow.h"
#include "TopUpBudgetWindow.h"
#include "ManWithMyProjectWindow.h"
#include "ManProjectManagerWindow.h"


class ManagerPanelWindow : public BaseWindow {
private:
    Manager manager;
    FileManager<Manager> managerFileManager;
    FileManager<Project> projectFileManager;
    List<Project> projects;
    int valueOwnProject = 0;
    int valueProject = 0;
public:
    ManagerPanelWindow(Manager manager, FileManager<Manager> managerFileManager)
        : manager(manager), managerFileManager(managerFileManager) { 
        projects = projectFileManager.readFromFile();
    }
    int show() {
        string cases[5] = { "�������� �������", "��������� ����� �������", "����������� �� ������ ���������", "������� ������", "�����" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "           �������" << endl;
                cout << "==================================" << endl;
                cout << "   ���: " << manager.getName() << endl;
                cout << "   Email: " << manager.getEmail() << endl;
                cout << "   ����� �������: " << manager.getBudgetLimit() << endl;
                cout << "   ���������� ����� ��������: " << projects.getOwnValueProject(manager.getId()) << endl;
                cout << "   ����� ���������� ��������: " << projects.getValueProject(manager.getId()) << endl;
                cout << "==================================" << endl;
                switch (system.getUserChoice(5, cases)) {
                case 1:
                {
                    ChangeProfileManagerWindow changeProfileManagerWindow(&manager, managerFileManager);
                    changeProfileManagerWindow.show();
                }
                break;
                case 2:
                {
                    TopUpBudgetWindow topUpBudgetWindow;
                    if (topUpBudgetWindow.show(false) == 1) {
                        increaseBudget(manager, (topUpBudgetWindow.getValue()));
                        managerFileManager.rewriteFile(manager);
                    }
                }
                break;
                case 3:
                {
                    ManWithMyProjectWindow manWithMyProjectWindow(projects, projectFileManager, manager.getId());
                    manWithMyProjectWindow.show();
                }
                break;
                case 4:
                    chooseProject();
                    break;
                case -1:
                case 5:
                    return 0;
                }

            }
            catch (const CustomException& err)
            {
                ErrorWindow errorWindow(err.what());
            }
        }
    }


    void close() override {
        system.clearWindow();
    }
private:
    void chooseProject() {
        bool flagDisplay = false;
        int length = 0;
        for (int i = 0; i < projects.length(); i++) {
            if (manager.getId() == projects[i].getIdCreator() || projects[i].hasManagerId(manager.getId())) {
                length++;
                flagDisplay = true;
            }
        }
        system.clearWindow();

        if (projects.length() == 0 || !flagDisplay) {
            throw CustomException("��� ��������");
        }

        projects[0].displayProjectTableHeader();

        for (int i = 0; i < projects.length(); i++) {
            if (manager.getId() == projects[i].getIdCreator() || projects[i].hasManagerId(manager.getId()))
                projects[i].displayProjectInfo();
        }


        int id = -1;


        Project project;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("������� id �������, ������� ������ �������: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }

            if (!projects.find(id))
                continue;

            project = projects.getDataById(id);

            if (project.getIdCreator() == manager.getId())
                break;

            if (project.hasManagerId(manager.getId()))
                break;

        } while (true);


        if (id != -1) {
            system.clearWindow();
            ManProjectManagerWindow manProjectManagerWindow(project, manager, managerFileManager, projectFileManager);
            manProjectManagerWindow.show();
        }
    }
};

