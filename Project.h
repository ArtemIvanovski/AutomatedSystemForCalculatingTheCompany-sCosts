#pragma once
#include "Liberies.h"
#include "ProjectStatus.h"
#include "CustomException.h"

class Project {
private:
    int id;                    
    string name;                      
    string description;               
    int idCreator;                    
    vector<int> managerIds;           
    vector<int> analystIds;           
    time_t startDate;                 
    time_t endDate;                   
    ProjectStatus status;             
    double budget;                 

public:
    Project()
        : id(0), idCreator(0), startDate(time(nullptr)), endDate(0),
        status(ProjectStatus::NotStarted), budget(0.0) {}

    Project(int id, const string& projectName, const string& projectDescription, int creatorId, double budget)
        : id(id), name(projectName), description(projectDescription), idCreator(creatorId), budget(budget),
        startDate(time(nullptr)), endDate(0), status(ProjectStatus::NotStarted) {}

    int getId() const { return id; }

    string getName() const { return name; }
    void setName(const string& projectName) { name = projectName; }

    string getDescription() const { return description; }
    void setDescription(const string& projectDescription) { description = projectDescription; }

    int getIdCreator() const { return idCreator; }

    vector<int> getManagerIds() const { return managerIds; }
    
    
    bool hasManagerId(int managerId) const {
        for (int id : managerIds) {
            if (id == managerId) {
                return true;
            }
        }
        return false;
    }

    void addManagerId(int managerId) {
        if (hasManagerId(managerId)) {
            throw CustomException("Manager ID already exists.");
        }
        managerIds.push_back(managerId);
    }

    bool hasAnalystId(int analystId) const {
        for (int id : analystIds) {
            if (id == analystId) {
                return true;
            }
        }
        return false;
    }

    void addAnalystId(int analystId) {
        if (hasManagerId(analystId)) {
            throw CustomException("Analyst ID already exists.");
        }
        analystIds.push_back(analystId);
    }
    

    vector<int> getAnalystIds() const { return analystIds; }

    double getBudget() const { return budget; }
    void addProjectBudget(double cost);

    void decreaseProjectBudget(double cost);

    time_t getStartDate() const { return startDate; }

    time_t getEndDate() const { return endDate; }

    string getStatus() const { return projectStatusToString(status); }

    void setStatus(ProjectStatus newStatus) {
        status = newStatus;
        if (status == ProjectStatus::Completed) {
            endDate = time(nullptr);  
        }
    }

    void removeManagerId(int managerId) {
        auto it = find(managerIds.begin(), managerIds.end(), managerId);
        if (it != managerIds.end()) {
            managerIds.erase(it);
        }
        else {
            throw CustomException("Идентификатор менеджера не найден.");
        }
    }

    void removeAnalystId(int analystId) {
        auto it = find(analystIds.begin(), analystIds.end(), analystId);
        if (it != analystIds.end()) {
            analystIds.erase(it);
        }
        else {
            throw CustomException("Идентификатор аналитика не найден.");
        }
    }


    void displayProjectTableHeader() const {
        cout << "====================================================================================================================================================================================================" << endl;
        cout << "|   ID проекта    |      Название проекта        |   Статус     |   Бюджет  |      Администраторы      |      Пользователи        |  Дата начала   | Дата окончания |       Описание проекта       |" << endl;
        cout << "====================================================================================================================================================================================================" << endl;
    }

    void displayProjectInfo() const {
        string managerIdsStr;
        for (size_t i = 0; i < managerIds.size(); ++i) {
            managerIdsStr += to_string(managerIds[i]) + (i < managerIds.size() - 1 ? ", " : "");
        }

        string analystIdsStr;
        for (size_t i = 0; i < analystIds.size(); ++i) {
            analystIdsStr += to_string(analystIds[i]) + (i < analystIds.size() - 1 ? ", " : "");
        }

        tm* startDateTm = nullptr;
        tm* endDateTm = nullptr;
        string startDateStr = "-";
        string endDateStr = "-";

        if (startDate != 0) {
            startDateTm = localtime(&startDate);
            stringstream ss;
            ss << put_time(startDateTm, "%Y-%m-%d"); 
            startDateStr = ss.str();
        }
        if (endDate != 0) {
            endDateTm = localtime(&endDate);
            stringstream ss;
            ss << put_time(endDateTm, "%Y-%m-%d"); 
            endDateStr = ss.str();
        }

        cout << "|  " << setw(13) << id
            << "  |  " << setw(26) << name
            << "  |  " << setw(10) << getStatus()
            << "  |  " << setw(7) << fixed << setprecision(2) << budget
            << "  |  " << setw(22) << managerIdsStr
            << "  |  " << setw(22) << analystIdsStr
            << "  |  " << setw(12) << startDateStr
            << "  |  " << setw(12) << endDateStr
            << "  |  " << setw(26) << description << "  |" << endl;

        cout << "====================================================================================================================================================================================================" << endl;
    }

    friend ostream& operator<<(ostream& os, const Project& obj) {
        os.write((const char*)&obj.id, sizeof(obj.id));

        int nameSize = obj.name.size();
        os.write((const char*)&nameSize, sizeof(nameSize));
        os.write(obj.name.data(), nameSize);

        int descSize = obj.description.size();
        os.write((const char*)&descSize, sizeof(descSize));
        os.write(obj.description.data(), descSize);

        os.write((const char*)&obj.idCreator, sizeof(obj.idCreator));

        int managerCount = obj.managerIds.size();
        os.write((const char*)&managerCount, sizeof(managerCount));
        for (int id : obj.managerIds) {
            os.write((const char*)&id, sizeof(id));
        }

        int analystCount = obj.analystIds.size();
        os.write((const char*)&analystCount, sizeof(analystCount));
        for (int id : obj.analystIds) {
            os.write((const char*)&id, sizeof(id));
        }

        os.write((const char*)&obj.startDate, sizeof(obj.startDate));
        os.write((const char*)&obj.endDate, sizeof(obj.endDate));

        int statusInt = static_cast<int>(obj.status);
        os.write((const char*)&statusInt, sizeof(statusInt));

        os.write((const char*)&obj.budget, sizeof(obj.budget));

        return os;
    }


    friend istream& operator>>(istream& is, Project& obj) {
        if (is.read((char*)&obj.id, sizeof(obj.id))) {
            int nameSize;
            is.read((char*)&nameSize, sizeof(nameSize));
            obj.name.resize(nameSize);
            is.read(&obj.name[0], nameSize);

            int descSize;
            is.read((char*)&descSize, sizeof(descSize));
            obj.description.resize(descSize);
            is.read(&obj.description[0], descSize);

            is.read((char*)&obj.idCreator, sizeof(obj.idCreator));

            int managerCount;
            is.read((char*)&managerCount, sizeof(managerCount));
            obj.managerIds.resize(managerCount);
            for (int& id : obj.managerIds) {
                is.read((char*)&id, sizeof(id));
            }

            int analystCount;
            is.read((char*)&analystCount, sizeof(analystCount));
            obj.analystIds.resize(analystCount);
            for (int& id : obj.analystIds) {
                is.read((char*)&id, sizeof(id));
            }

            is.read((char*)&obj.startDate, sizeof(obj.startDate));
            is.read((char*)&obj.endDate, sizeof(obj.endDate));

            int statusInt;
            is.read((char*)&statusInt, sizeof(statusInt));
            obj.status = static_cast<ProjectStatus>(statusInt);

            is.read((char*)&obj.budget, sizeof(obj.budget));
        }
        else {
            is.setstate(ios::failbit);
        }

        return is;
    }

    string getManagerIdsString() const {
        stringstream ss;
        for (size_t i = 0; i < managerIds.size(); ++i) {
            ss << managerIds[i] << (i < managerIds.size() - 1 ? ", " : "");
        }
        if (ss.str().length() == 0)
            return "-";

        return ss.str();
    }

    string getAnalystIdsString() const {
        stringstream ss;
        for (size_t i = 0; i < analystIds.size(); ++i) {
            ss << analystIds[i] << (i < analystIds.size() - 1 ? ", " : "");
        }
        if (ss.str().length() == 0)
            return "-";

        return ss.str();
    }

};

void Project::addProjectBudget(double cost) {
    if (cost >= 0) {
        budget += cost;
    }
    else {
        throw CustomException("Число должна быть положительным");
    }
}

void Project::decreaseProjectBudget(double cost) {
    if (budget -cost >= 0) {
        budget -= cost;
    }
    else {
        throw CustomException("Недостаточно бюджета проекта");
    }
}
