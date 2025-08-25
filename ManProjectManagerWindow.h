#pragma once
#include "List.h"
#include "FileManager.h"
#include "ErrorWindow.h"

class ManProjectManagerWindow : public BaseWindow {
private:
    Project project;
    Manager manager;
    FileManager<Analyst> analystFileManager;
    FileManager<Manager> managerFileManager;
    FileManager<Project> projectFileManager;
    FileManager<DirectExpense> directExpenseFileManager;
    FileManager<IndirectExpense> indirectExpenseFileManager;
public:
    ManProjectManagerWindow(Project project, Manager manager, FileManager<Manager> managerFileManager, FileManager<Project> projectFileManager)
        : project(project), manager(manager), managerFileManager(managerFileManager), projectFileManager(projectFileManager) { }

    int show() {
        string casesCreator[5] = { "Редактирование проекта", "Редактирование администраторов", "Редактирование пользователей", "Манипуляции с расходами", "Выход" };
        string cases[5] = { "Добавить расход", "Удалить расход", "Вывести все косвенные расходы","Вывести все прямые расходы", "Выход" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "=====================================" << endl;
                cout << "   Информация о проекте" << endl;
                cout << "=====================================" << endl;
                cout << "   Название: " << project.getName() << endl;
                cout << "   Описание: " << project.getDescription() << endl;
                cout << "   Бюджет: " << project.getBudget() << endl;
                cout << "   ID создателя: " << project.getIdCreator() << endl;
                cout << "   Статус: " << project.getStatus() << endl;
                cout << "=====================================" << endl;

                if (manager.getId() == project.getIdCreator()) {
                    switch (system.getUserChoice(5, casesCreator)) {
                    case -1:
                    case 5:
                        close();
                        return -1;
                    case 1:
                        editProject();
                        break;
                    case 2:
                        editManager();
                        break;
                    case 3:
                        editAnalyst();
                        break;
                    case 4:
                        manExpense();
                        break;
                    }
                }
                else {
                    switch (system.getUserChoice(5, cases)) {
                    case -1:
                    case 5:
                        close();
                        return -1;
                    case 1:
                        addExpense();
                        break;
                    case 2:
                        removeExpense();
                        break;
                    case 3:
                        displayIndirectExpense();
                        break;
                    case 4:
                        displayDirectExpense();
                        break;
                    }
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

    void manExpense() {
        string cases[5] = { "Добавить расход", "Удалить расход", "Вывести все косвенные расходы","Вывести все прямые расходы", "Выход" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "======================" << endl;
                cout << "        Расходы" << endl;
                cout << "======================" << endl;

                switch (system.getUserChoice(5, cases)) {
                case -1:
                case 5:
                    return;
                case 1:
                    addExpense();
                    break;
                case 2:
                    removeExpense();
                    break;
                case 3:
                    displayIndirectExpense();
                    break;
                case 4:
                    displayDirectExpense();
                    break;
                }
            }
            catch (const CustomException& msg)
            {
                ErrorWindow errorWindow(msg.what());
            }
        }
    }

    void removeExpense() {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "    Удаление расхода" << endl;
        cout << "==============================" << endl;
        bool isIndirectExpense = false;
        string cases[2] = { "Прямые", "Косвенные" };
        system.printWithColor("Выберете тип расходов : \n", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 0, 3, true);
        switch (system.getUserChoice(2, cases, 3, 4, true)) {
        case -1:
            return;
        case 1:
            isIndirectExpense = false;
            break;
        case 2:
            isIndirectExpense = true;
            break;
        }

        if (isIndirectExpense) {
            displayIndirectExpense(false);
            List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();
            int length = 0;
            for (int i = 0; i < indirectExpenses.length(); i++) {
                if (indirectExpenses[i].getIdProject() == project.getId())
                {
                    length++;
                }
            }

            int id = -1;
            do
            {
                system.clearArea(length * 2 + 4, 1);
                id = system.getIntInput("Введите id расхода, который хотите удалить: ", 0, length * 2 + 4);
                if (id == -1) {
                    break;
                }
            } while (!indirectExpenses.find(id) || indirectExpenses.getDataById(id).getIdProject() != project.getId());

            if (id != -1) {
                IndirectExpense indirectExpense = indirectExpenses.getDataById(id);
                indirectExpenseFileManager.deleteByData(indirectExpense);
                increaseBudget(manager, indirectExpense.getAmount());
                project.addProjectBudget(indirectExpense.getAmount());
                projectFileManager.rewriteFile(project);
                managerFileManager.rewriteFile(manager);
            }
        }
        else
        {
            displayDirectExpense(false);
            List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();
            int length = 0;
            for (int i = 0; i < directExpenses.length(); i++) {
                if (directExpenses[i].getIdProject() == project.getId())
                {
                    length++;
                }
            }

            int id = -1;
            do
            {
                system.clearArea(length * 2 + 4, 1);
                id = system.getIntInput("Введите id расхода, который хотите удалить: ", 0, length * 2 + 4);
                if (id == -1) {
                    break;
                }
            } while (!directExpenses.find(id) || directExpenses.getDataById(id).getIdProject() != project.getId());

            if (id != -1) {
                DirectExpense directExpense = directExpenses.getDataById(id);
                directExpenseFileManager.deleteByData(directExpense);
                increaseBudget(manager, directExpense.getAmount());
                project.addProjectBudget(directExpense.getAmount());
                projectFileManager.rewriteFile(project);
                managerFileManager.rewriteFile(manager);
            }
        }
    }

    void displayDirectExpense(bool withSort = true) {
        string cases[4] = { "По id", "По описанию", "По сумме", "По типу" };
        List<DirectExpense> directExpenses = directExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < directExpenses.length(); i++) {
            if (directExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (directExpenses.length() == 0 || !display) {
            throw CustomException("Нет прямых расходов");
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
        string cases[4] = { "По id", "По описанию", "По сумме", "По типу" };
        List<IndirectExpense> indirectExpenses = indirectExpenseFileManager.readFromFile();

        bool display = false;

        for (int i = 0; i < indirectExpenses.length(); i++) {
            if (indirectExpenses[i].getIdProject() == project.getId())
            {
                display = true;
            }
        }

        if (indirectExpenses.length() == 0 || !display) {
            throw CustomException("Нет косвенных расходов");
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

    void addExpense() {
        bool isIndirectExpense = false;
        int id;
        int idProject;
        double amount;
        string description;
        string directExpenseType;
        string indirectExpenseType;
        double allocationPercentage;

        do
        {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "    Добавление расхода" << endl;
            cout << "==============================" << endl;

            string cases[2] = { "Прямые", "Косвенные" };
            system.printWithColor("Выберете тип расходов : \n", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 0, 3, true);
            switch (system.getUserChoice(2, cases, 3, 4, true)) {
            case -1:
                return;
            case 1:
                isIndirectExpense = false;
                break;
            case 2:
                isIndirectExpense = true;
                break;
            }

            description = system.getInputWithMask("Введите описание расхода: ", 0, 6, false);
            if (description == "_")
                return;

            system.printWithColor("Введите сумму расхода: ", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 0, 7, true);
            amount = system.inputDouble();
            if (amount == -1.0)
                return;

            if (isIndirectExpense) {
                indirectExpenseType = system.getInputWithMask("Введите тип косвенных расходов: ", 0, 8, false);
                if (indirectExpenseType == "_")
                    return;

                system.printWithColor("Введите процент распределения: ", FOREGROUND_INTENSITY | FOREGROUND_GREEN, 0, 9, true);
                allocationPercentage = system.inputDouble();
                if (allocationPercentage == -1.0)
                    return;

            }
            else
            {
                directExpenseType = system.getInputWithMask("Введите тип прямых расходов: ", 0, 8, false);
                if (directExpenseType == "_")
                    return;
            }


        } while (description.empty() || amount == 0.0);

        decreaseBudget(manager, amount);
        project.decreaseProjectBudget(amount);
        projectFileManager.rewriteFile(project);
        managerFileManager.rewriteFile(manager);

        if (isIndirectExpense) {
            IndirectExpense indirectExpense(indirectExpenseFileManager.getUniqueID(), project.getId(), amount, description, indirectExpenseType, allocationPercentage);
            indirectExpenseFileManager.writeToFile(indirectExpense);
        }
        else {
            DirectExpense directExpense(directExpenseFileManager.getUniqueID(), project.getId(), amount, description, directExpenseType);
            directExpenseFileManager.writeToFile(directExpense);
        }
    }

    void editProject() {
        string newName = "", newDescription = "";
        double budget = 0.0;
        ProjectStatus status = ProjectStatus::Error;
        string statusCases[5] = { "Не начат", "В прогрессе", "Выполнен", "На удерживании", "Выход"};
        string cases[6] = { "Изменить название", "Изменить статус", "Изменить описание", "Добавить бюджет", "Сохранить изменения", "Выход" };
        while (true) {
            system.clearWindow();
            cout << "==============================" << endl;
            cout << "      Изменение проекта       " << endl;
            cout << "==============================" << endl;
            switch (system.getUserChoice(6, cases))
            {
            case 6:
            case -1:
                return;
            case 1:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Изменение названия       " << endl;
                cout << "==============================" << endl;
                do
                {
                    system.clearArea(4, 1);
                    newName = system.getInputWithMask("Введите новое название: ", 0, 4, false);
                    if (newName == "_") {
                        newName = "";
                        break;
                    }
                } while (newName == "");
                break;
            case 2:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Изменение статуса       " << endl;
                cout << "==============================" << endl;
                switch (system.getUserChoice(5, statusCases)) {
                case -1:
                case 5:
                    break;
                case 1:
                    status = ProjectStatus::NotStarted;
                    break;
                case 2:
                    status = ProjectStatus::InProgress;
                    break;
                case 3:
                    status = ProjectStatus::Completed;
                    break;
                case 4:
                    status = ProjectStatus::OnHold;
                    break;
                }
                break;
            case 3:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "      Изменение имени       " << endl;
                cout << "==============================" << endl;
                do
                {
                    system.clearArea(4, 1);
                    newDescription = system.getInputWithMask("Введите новое описание: ", 0, 4, false);
                    if (newDescription == "_") {
                        newDescription = "";
                        break;
                    }
                } while (newDescription == "");
                break;
            case 4:
                system.clearWindow();
                cout << "==============================" << endl;
                cout << "       Пополнение бюджета  " << endl;
                cout << "==============================" << endl;

                cout << "Введите сумму для пополнения бюджета проекта: ";

                budget = system.inputDouble();
                if (budget == -1.0) {
                    budget = 0;
                    break;
                }
                break;
            case 5:
                int boolChange = false;
                if (newName != "") {
                    boolChange = true;
                    project.setName(newName);
                }

                if (newDescription != "") {
                    boolChange = true;
                    project.setDescription(newDescription);
                }

                if (budget != 0) {
                    boolChange = true;
                    project.addProjectBudget(budget);
                }

                if (status != ProjectStatus::Error) {
                    boolChange = true;
                    project.setStatus(status);
                }

                if (boolChange) {
                    projectFileManager.rewriteFile(project);
                }
                return;
            }
        }
    }

    void editAnalyst() {
        string cases[6] = { "Вывести пользователей", "Убрать пользователя", "Добавить пользователя", "Повысить квалификацию пользователя","Понизить квалификацию пользователя", "Выход" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "========================================" << endl;
                cout << " Изменение пользовательского состава       " << endl;
                cout << "========================================" << endl;
                cout << "   Количество: " << project.getAnalystIds().size() << endl;
                cout << "   Ids пользователей: " << project.getAnalystIdsString() << endl;
                cout << "========================================" << endl;
                switch (system.getUserChoice(6, cases))
                {
                case 6:
                case -1:
                    return;
                case 1:
                    displayAnalysts();
                    break;
                case 2:
                    removeAnalyst();
                    break;
                case 3:
                    addAnalyst();
                    break;
                case 4:
                    promoteAnalyst();
                    break;
                case 5:
                    demoteAnalyst();
                    break;
                }
            }
            catch (const CustomException& msg)
            {
                ErrorWindow errorWindow(msg.what());
            }
        }
    }

    void promoteAnalyst() {
        List<Analyst> analysts = analystFileManager.readFromFile();
        system.clearWindow();
        displayAnalysts(false, false);
        int length = 0;
        for (int i = 0; i < analysts.length(); i++) {
            if (project.hasAnalystId(analysts[i].getId())) {
                length++;
            }
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id пользователя, которого хотите повысить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!analysts.find(id) && !project.hasAnalystId(id));

        if (id != -1) {
            system.clearWindow();
            Analyst analyst = analysts.getDataById(id);
            promoteSpecializationLevel(analyst);
            analystFileManager.rewriteFile(analyst);
        }
    }

    void demoteAnalyst() {
        List<Analyst> analysts = analystFileManager.readFromFile();
        system.clearWindow();
        displayAnalysts(false, false);
        int length = 0;
        for (int i = 0; i < analysts.length(); i++) {
            if (project.hasAnalystId(analysts[i].getId())) {
                length++;
            }
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id пользователя, которого хотите понизить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!analysts.find(id) && !project.hasAnalystId(id));

        if (id != -1) {
            system.clearWindow();
            Analyst analyst = analysts.getDataById(id);
            demoteSpecializationLevel(analyst);
            analystFileManager.rewriteFile(analyst);
        }
    }

    void addAnalyst() {
        List<Analyst> analysts = analystFileManager.readFromFile();
        system.clearWindow();
        displayAnalysts(true, false);
        int length = 0;
        for (int i = 0; i < analysts.length(); i++) {
            length++;
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id пользователя, которого хотите добавить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!analysts.find(id));

        if (id != -1) {
            system.clearWindow();
            project.addAnalystId(id);
            projectFileManager.rewriteFile(project);
        }
    }

    void removeAnalyst() {
        List<Analyst> analysts = analystFileManager.readFromFile();
        system.clearWindow();
        displayAnalysts(false, false);
        int length = 0;
        for (int i = 0; i < analysts.length(); i++) {
            if (project.hasAnalystId(analysts[i].getId())) {
                length++;
            }
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id пользователя, которого хотите удалить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!analysts.find(id));

        if (id != -1) {
            system.clearWindow();
            project.removeAnalystId(id);
            projectFileManager.rewriteFile(project);
        }
    }

    void displayAnalysts(bool displayAll = true, bool withSort = true) {
        string cases[5] = { "По id", "По имени", "По email", "По уровню специализации", "По кол-во анализов"};
        List<Analyst> analysts = analystFileManager.readFromFile();

        bool display = true;

        for (int i = 0; i < analysts.length(); i++)
        {
            if (displayAll || project.hasAnalystId(analysts[i].getId())) {
                display = false;
                break;
            }
        }

        if (analysts.length() == 0 || display) {
            throw CustomException("Нет аналитиков");
        }

        while (true) {

            system.clearWindow();

            analysts[0].displayAnalystTableHeader();

            for (int i = 0; i < analysts.length(); i++) {
                if (displayAll || project.hasAnalystId(analysts[i].getId()))
                    analysts[i].displayAnalystInfo();
            }


            if (withSort) {
                switch (system.getUserChoice(5, cases))
                {
                case -1:
                    return;
                case 1:
                    analysts.sortById();
                    break;
                case 2:
                    analysts.sortByName();
                    break;
                case 3:
                    analysts.sortByEmail();
                    break;
                case 4:
                    analysts.sortBySpecializationLevel();
                    break;
                case 5:
                    analysts.sortByCompletedAnalysesCount();
                    break;
                }
            }
            else {
                return;
            }
        }
    }

    void editManager() {
        string cases[4] = { "Вывести администраторов", "Убрать администратора", "Добавить администратора", "Выход" };
        while (true) {
            try
            {
                system.clearWindow();
                cout << "========================================" << endl;
                cout << "   Изменение администраторского состава       " << endl;
                cout << "========================================" << endl;
                cout << "   Количество: " << project.getManagerIds().size() << endl;
                cout << "   Ids администраторов: " << project.getManagerIdsString() << endl;
                cout << "========================================" << endl;
                switch (system.getUserChoice(4, cases))
                {
                case 4:
                case -1:
                    return;
                case 1:
                    displayManagers();
                    break;
                case 2:
                    removeManager();
                    break;
                case 3:
                    addManager();
                    break;
                }
            }
            catch (const CustomException& msg)
            {
                ErrorWindow errorWindow(msg.what());
            }
        }
    }

    void addManager() {
        List<Manager> managers = managerFileManager.readFromFile();
        system.clearWindow();
        displayManagers(true, false);
        int length = 0;
        for (int i = 0; i < managers.length(); i++) {
            length++;
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id администратора, которого хотите добавить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!managers.find(id));

        if (id != -1) {
            system.clearWindow();
            project.addManagerId(id);
            projectFileManager.rewriteFile(project);
        }
    }

    void removeManager() {
        List<Manager> managers = managerFileManager.readFromFile();
        system.clearWindow();
        displayManagers(false, false);
        int length = 0;
        
        for (int i = 0; i < managers.length(); i++) {
            if (project.hasManagerId(managers[i].getId())) {
                length++;
            }
        }

        int id = -1;
        do
        {
            system.clearArea(length * 2 + 4, 1);
            id = system.getIntInput("Введите id администратора, которого хотите удалить: ", 0, length * 2 + 4);
            if (id == -1) {
                break;
            }
        } while (!managers.find(id));

        if (id != -1) {
            system.clearWindow();
            project.removeManagerId(id);
            projectFileManager.rewriteFile(project);
        }
    }

    void displayManagers(bool displayAll = true, bool withSort = true) {
        string cases[3] = { "По id", "По имени", "По email" };
        List<Manager> managers = managerFileManager.readFromFile();

        
        bool display = true;
        for (int i = 0; i < managers.length(); i++)
        {
            if (displayAll || project.hasManagerId(managers[i].getId())) {
                display = false;
                break;
            }
        }

        if (managers.length() == 0 || display) {
            throw CustomException("Нет менеджеров");
        }

        while (true) {

            system.clearWindow();

            managers[0].displayManagerTableHeader();

            for (int i = 0; i < managers.length(); i++) {
                if (displayAll || project.hasManagerId(managers[i].getId()))
                    managers[i].displayManagerInfo();
            }


            if (withSort) {
                switch (system.getUserChoice(3, cases))
                {
                case -1:
                    return;
                case 1:
                    managers.sortById();
                    break;
                case 2:
                    managers.sortByName();
                    break;
                case 3:
                    managers.sortByEmail();
                    break;
                }
            }
            else {
                return;
            }
        }
    }
};