#pragma once
#include "List.h"
#include "FileManager.h"
#include "ErrorWindow.h"

class ManProjectAnalystWindow : public BaseWindow {
private:
    Project project;
    Analyst analyst;
    FileManager<Analyst> analystFileManager;
    FileManager<DirectExpense> directExpenseFileManager;
    FileManager<IndirectExpense> indirectExpenseFileManager;
public:
    ManProjectAnalystWindow(Project project, Analyst analyst, FileManager<Analyst> analystFileManager)
        : project(project), analyst(analyst), analystFileManager(analystFileManager) { }

    int show() {
        string cases[6] = { "���������� ���������� ��������", "���������� ������� �� ������������ �����", "������� ��� ��������� �������","������� ��� ������ �������","������� �����", "�����" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "=====================================" << endl;
                cout << "   ���������� � �������" << endl;
                cout << "=====================================" << endl;
                cout << "   ��������: " << project.getName() << endl;
                cout << "   ��������: " << project.getDescription() << endl;
                cout << "   ������: " << project.getBudget() << endl;
                cout << "   ID ���������: " << project.getIdCreator() << endl;
                cout << "   ������: " << project.getStatus() << endl;
                cout << "=====================================" << endl;

                switch (system.getUserChoice(5, cases)) {
                case -1:
                case 6:
                    incrementCompletedAnalysesCount(analyst);
                    analystFileManager.rewriteFile(analyst);
                    close();
                    return -1;
                case 1:
                    displayStatistics();
                    break;
                case 2:
                    displayExpenseInRangeDate();
                    break;
                case 3:
                    displayIndirectExpense();
                    break;
                case 4:
                    displayDirectExpense();
                    break;
                case 5:
                    downloadAllExpense();
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

    void downloadAllExpense() {

        system.clearWindow();
        cout << "=====================================" << endl;
        cout << "         ���������� �����" << endl;
        cout << "=====================================" << endl;

        string filePath;
        string fileName;

        do
        {
            system.clearArea(4, 1);
            filePath = system.getInputWithMask("������� ���� � ����� (��������, C:\\path\\to\\file): ", 0, 4, false);
            if (filePath == "_") {
                filePath = "";
                return;
            }
        } while (filePath == "");

        do
        {
            system.clearArea(5, 1);
            fileName = system.getInputWithMask("������� ��� ����� (��������, expenses.txt): ", 0, 5, false);
            if (fileName == "_") {
                fileName = "";
                return;
            }
        } while (fileName == "");



        ofstream outputFile(filePath + "/" + fileName);

        if (!outputFile.is_open()) {
            throw CustomException("������ �������� �����!");
        }

        List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (directExpenses.length() == 0 || !display) {
            outputFile << "��� ������ ��������" << endl;
        }
        outputFile << "������ �������: " << endl;

        directExpenses[0].writeDirectExpenseTableHeader(outputFile);

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId())
                directExpenses[i].writeDirectExpenseInfo(outputFile);
        }

        List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();

        display = false;

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (indirectExpenses.length() == 0 || !display) {
            outputFile << "��� ��������� ��������" << endl;
        }

        outputFile << "��������� �������: " << endl;

        indirectExpenses[0].writeIndirectExpenseTableHeader(outputFile);

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId())
                indirectExpenses[i].writeIndirectExpenseInfo(outputFile);
        }

        outputFile.close();
        cout << "������ ������� ��������� � ���� " << filePath + "/" + fileName << endl;
        system.delayPress();
    }

    void displayDirectExpense(bool withSort = true) {
        string cases[4] = { "�� id", "�� ��������", "�� �����", "�� ����" };
        List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (directExpenses.length() == 0 || !display) {
            throw CustomException("��� ������ ��������");
        }

        while (true) {
            system.clearWindow();

            directExpenses[0].displayDirectExpenseTableHeader();

            for (int i = 0; i < directExpenses.length(); i++) {
                if (directExpenses[i].getIdProject() == project.getId())
                    directExpenses[i].displayDirectExpenseInfo();
            }

            if (withSort) {
                switch (system.getUserChoice(4, cases))
                {
                case -1:
                    return;
                case 1:
                    directExpenses.sortById();
                    break;
                case 2:
                    directExpenses.sortByDescription();
                    break;
                case 3:
                    directExpenses.sortByAmount();
                    break;
                case 4:
                    directExpenses.sortByDirectExpenseType();
                    break;
                }
            }
            else {
                return;
            }
        }
    }

    void displayIndirectExpense(bool withSort = true) {
        string cases[4] = { "�� id", "�� ��������", "�� �����", "�� ����" };
        List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (indirectExpenses.length() == 0 || !display) {
            throw CustomException("��� ��������� ��������");
        }

        while (true) {
            system.clearWindow();

            indirectExpenses[0].displayIndirectExpenseTableHeader();

            for (int i = 0; i < indirectExpenses.length(); i++) {
                if (indirectExpenses[i].getIdProject() == project.getId())
                    indirectExpenses[i].displayIndirectExpenseInfo();
            }

            if (withSort) {
                switch (system.getUserChoice(4, cases))
                {
                case -1:
                    return;
                case 1:
                    indirectExpenses.sortById();
                    break;
                case 2:
                    indirectExpenses.sortByDescription();
                    break;
                case 3:
                    indirectExpenses.sortByAmount();
                    break;
                case 4:
                    indirectExpenses.sortByIndirectExpenseType();
                    break;
                }
            }
            else {
                return;
            }
        }
    }

    void displayExpenseInRangeDate() {
        system.clearWindow();
        string startDateStr, endDateStr;
        int level = 0; 
        bool flag = true;
        while (true) {


            if (flag) {
                cout << "���� ��: " << startDateStr << endl;
                cout << "���� ��: " << endDateStr << endl;
                flag = false;
            }
            

            char input = _getch();
            system.clearWindow();

            if (input == 27) { 
                return;
            }

            if (input == 72) { 
                level = 0;
            }
            else if (input == 80) {
                level = 1;
            }
            else if (input == 8) { 
                string* str = (level == 0) ? &startDateStr : &endDateStr;
                if (!str->empty()) {
                    str->pop_back();
                }
            }
            else if (input >= '0' && input <= '9' || input == '.') { 
                string* str = (level == 0) ? &startDateStr : &endDateStr;
                if (str->length() < 10) { 
                    str->push_back(input);
                }
            }
            
            cout << "���� ��: " << startDateStr << endl;
            cout << "���� ��: " << endDateStr << endl;

            regex dateRegex("(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{4}");
            if (regex_match(startDateStr, dateRegex) && regex_match(endDateStr, dateRegex)) {
                tm t{};
                istringstream ss1(startDateStr);
                ss1 >> get_time(&t, "%d.%m.%Y");
                time_t startDate = mktime(&t);

                istringstream ss2(endDateStr);
                ss2 >> get_time(&t, "%d.%m.%Y");
                time_t endDate = mktime(&t);

                if (startDate != (time_t)(-1) && endDate != (time_t)(-1) && startDate <= endDate) {
                    showExpensesInRange(startDate, endDate);
                }
                else {
                    cout << "������ �������������� ��� ��������� ���!" << endl;
                }
            }
        }
    }

    void showExpensesInRange(time_t startDate, time_t endDate) {
        List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId() && directExpenses[i].getDate() >= startDate && directExpenses[i].getDate() <= endDate)
            {
                display = true;
            }
        }

        if (directExpenses.length() == 0 || !display) {
            cout << "��� ������ �������� � ���� ������" << endl;
        }
        cout << "������ �������: " << endl;

        directExpenses[0].displayDirectExpenseTableHeader();

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId() && directExpenses[i].getDate() >= startDate && directExpenses[i].getDate() <= endDate)
                directExpenses[i].displayDirectExpenseInfo();
        }

        List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();

        display = false;

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId() && indirectExpenses[i].getDate() >= startDate && indirectExpenses[i].getDate() <= endDate)
            {
                display = true;
            }
        }

        if (indirectExpenses.length() == 0 || !display) {
            cout << "��� ��������� �������� � ���� ������" << endl;
        }

        cout << "��������� �������: " << endl;
        
        indirectExpenses[0].displayIndirectExpenseTableHeader();

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId() && indirectExpenses[i].getDate() >= startDate && indirectExpenses[i].getDate() <= endDate)
                indirectExpenses[i].displayIndirectExpenseInfo();
        }
    }

    void displayStatistics() {
        List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();
        List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();

        double totalIndirectExpenses = 0;
        double totalDirectExpenses = 0;
        map<int, double> monthlyIndirectExpenses;
        map<int, double> monthlyDirectExpenses;

        for (int i = 0; i < indirectExpenses.length(); ++i) {
            if (indirectExpenses[i].getIdProject() == project.getId()) {
                totalIndirectExpenses += indirectExpenses[i].getAmount();
                monthlyIndirectExpenses[indirectExpenses[i].getMonth()] += indirectExpenses[i].getAmount();
            }
        }

        for (int i = 0; i < directExpenses.length(); ++i) {
            if (directExpenses[i].getIdProject() == project.getId()) {
                totalDirectExpenses += directExpenses[i].getAmount();
                monthlyDirectExpenses[directExpenses[i].getMonth()] += directExpenses[i].getAmount();
            }
        }

        system.clearWindow();
        cout << "=====================================" << endl;
        cout << "         ���������� ��������         " << endl;
        cout << "=====================================" << endl;
        cout << fixed << setprecision(1);
        cout << "������ �������: " << totalDirectExpenses << endl;
        cout << "��������� �������: " << totalIndirectExpenses << endl;
        cout << "�����: " << totalDirectExpenses + totalIndirectExpenses << endl << endl;

        cout << "������� �� �������:" << endl;
        cout << "-------------------------------------" << endl;
        cout << "�����  | ������  | ���������  | �����" << endl;
        cout << "-------------------------------------" << endl;

        for (int month = 1; month <= 12; ++month) {
            double monthDirect = monthlyDirectExpenses.count(month) ? monthlyDirectExpenses[month] : 0;
            double monthIndirect = monthlyIndirectExpenses.count(month) ? monthlyIndirectExpenses[month] : 0;
            cout << setw(6) << month << " | "
                << setw(7) << monthDirect << " | "
                << setw(10) << monthIndirect << " | "
                << setw(5) << monthDirect + monthIndirect << endl;
        }
        cout << "=====================================" << endl;
        
        system.delayPress();
    }
};