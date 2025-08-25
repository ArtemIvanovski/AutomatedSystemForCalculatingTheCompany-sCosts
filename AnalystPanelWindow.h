#pragma once
#include "ErrorWindow.h"
#include "FileManager.h"
#include "Analyst.h"
#include "ChangeProfileManagerWindow.h"
#include "TopUpBudgetWindow.h"
#include "ManWithMyProjectWindow.h"
#include "ManProjectManagerWindow.h"
#include "ChangeProfileAnalystWindow.h"
#include "ManProjectAnalystWindow.h"


class AnalystPanelWindow : public BaseWindow {
private:
    Analyst analyst;
    FileManager<Analyst> analystFileManager;
    FileManager<Project> projectFileManager;
    List<Project> projects;
public:
    AnalystPanelWindow(Analyst analyst, FileManager<Analyst> analystFileManager)
        : analyst(analyst), analystFileManager(analystFileManager) {
        projects = projectFileManager.readFromFile();
    }
    int show() {
        string cases[3] = { "�������� �������", "������� ������", "�����" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "           �������" << endl;
                cout << "==================================" << endl;
                cout << "   ���: " << analyst.getName() << endl;
                cout << "   Email: " << analyst.getEmail() << endl;
                cout << "   �����������: " << analyst.getDataAnalysisToolsString() << endl;
                cout << "   ���-�� ��������: " << analyst.getCompletedAnalysesCount() << endl;
                cout << "   ������� �������������: " << analyst.getSpecializationLevel() << endl;
                cout << "   ���������� ����� ��������: " << projects.getOwnValueProject(analyst.getId()) << endl;
                cout << "   ����� ���������� ��������: " << projects.getValueProject(analyst.getId()) << endl;
                cout << "==================================" << endl;
                switch (system.getUserChoice(3, cases)) {
                case 1:
                {
                    ChangeProfileAnalystWindow changeProfileAnalystWindow(&analyst, analystFileManager);
                    changeProfileAnalystWindow.show();
                }
                break;
                case 2:
                    chooseProject();
                    break;
                case -1:
                case 3:
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
            if (projects[i].hasAnalystId(analyst.getId())) {
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
            if (projects[i].hasAnalystId(analyst.getId()))
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

            if (project.hasAnalystId(analyst.getId()))
                break;

        } while (true);


        if (id != -1) {
            system.clearWindow();
            ManProjectAnalystWindow manProjectAnalystWindow(project, analyst, analystFileManager);
            manProjectAnalystWindow.show();
        }
    }
};

