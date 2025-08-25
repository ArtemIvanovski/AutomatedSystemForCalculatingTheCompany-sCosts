#pragma once
#include "User.h"
#include "SpecializationLevel.h"
#include "CustomException.h"

class Analyst : public User {
private:
    vector<string> dataAnalysisTools; 
    int completedAnalysesCount;       
    SpecializationLevel specializationLevel; 

public:
    Analyst() : User(), completedAnalysesCount(0), specializationLevel(SpecializationLevel::Junior) {}

    Analyst(int analystId, const string& analystName, const string& analystEmail,
       int analysesCount)
        : User(analystId, analystName, analystEmail),
        completedAnalysesCount(analysesCount), specializationLevel(SpecializationLevel::Junior) {}

    vector<string> getDataAnalysisTools() const { return dataAnalysisTools; }


    string getDataAnalysisToolsString() const {
        string toolsStr;
        for (int i = 0; i < dataAnalysisTools.size(); i++) {
            toolsStr += dataAnalysisTools[i];
            if (i < dataAnalysisTools.size() - 1) toolsStr += ", ";
        }
        if (toolsStr.empty())
            return "-";

        return toolsStr;
    }

    void addDataAnalysisTool(const string& tool) {
        dataAnalysisTools.push_back(tool);
    }

    void removeDataAnalysisTool(const string& tool) {
        auto it = find(dataAnalysisTools.begin(), dataAnalysisTools.end(), tool);
        if (it != dataAnalysisTools.end()) {
            dataAnalysisTools.erase(it);
        }
        else {
            throw CustomException("Инструмент '" + tool + "' не найден в списке инструментов.");
        }
    }

    int getCompletedAnalysesCount() const { return completedAnalysesCount; }


    void displayAnalystTableHeader() const {
        cout << "======================================================================================================================================\n";
        cout << "| ID пользов.  |       Имя пользовю       |  Email пользов.  | Инструменты                  | Кол-во анализов| Уровень специализации |\n";
        cout << "======================================================================================================================================\n";
    }

    void displayAnalystInfo() const {
        string toolsStr;
        for (int i = 0; i < dataAnalysisTools.size(); i++) {
            toolsStr += dataAnalysisTools[i];
            if (i < dataAnalysisTools.size() - 1) toolsStr += ", ";
        }

        cout << "| " << setw(12) << id
            << " | " << setw(24) << name
            << " | " << setw(15) << email
            << " | " << setw(28) << toolsStr
            << " | " << setw(14) << completedAnalysesCount
            << " | " << setw(21) << getSpecializationLevel() << " |\n";
        cout << "======================================================================================================================================\n";
    }

    friend void incrementCompletedAnalysesCount(Analyst& analyst) {
        ++analyst.completedAnalysesCount;
    }

    friend void resetCompletedAnalysesCount(Analyst& analyst) {
        analyst.completedAnalysesCount = 0;
    }

    friend void promoteSpecializationLevel(Analyst& analyst) {
        if (analyst.specializationLevel == SpecializationLevel::Junior) {
            analyst.specializationLevel = SpecializationLevel::Middle;
        }
        else if (analyst.specializationLevel == SpecializationLevel::Middle) {
            analyst.specializationLevel = SpecializationLevel::Senior;
        }
        else {
            throw CustomException("Пользователь уже находится на самом высоком уровне (Senior).");
            return;
        }
    }

    friend void demoteSpecializationLevel(Analyst& analyst) {
        if (analyst.specializationLevel == SpecializationLevel::Senior) {
            analyst.specializationLevel = SpecializationLevel::Middle;
        }
        else if (analyst.specializationLevel == SpecializationLevel::Middle) {
            analyst.specializationLevel = SpecializationLevel::Junior;
        }
        else {
            throw CustomException("Пользователь уже находится на самом низком уровне (Junior).");
            return;
        }
    }

    string getSpecializationLevel() const { return specializationLevelToString(specializationLevel); }

    friend ostream& operator<<(ostream& os, const Analyst& obj) {
        os << static_cast<const User&>(obj); 
        int toolCount = obj.dataAnalysisTools.size();
        os.write((char*)&toolCount, sizeof(toolCount));
        for (const auto& tool : obj.dataAnalysisTools) {
            int toolLength = tool.size();
            os.write((char*)&toolLength, sizeof(toolLength));
            os.write(tool.c_str(), toolLength);
        }
        os.write((char*)&obj.completedAnalysesCount, sizeof(obj.completedAnalysesCount));

        int infoSize = specializationLevelToString(obj.specializationLevel).size();
        
        os.write((const char*)&infoSize, sizeof(infoSize));
        os.write(specializationLevelToString(obj.specializationLevel).data(), infoSize);
        
        return os;
    }

    friend istream& operator>>(istream& is, Analyst& obj) {
        is >> static_cast<User&>(obj); 
        int toolCount;
        if (is.read((char*)&toolCount, sizeof(toolCount))) {
            obj.dataAnalysisTools.resize(toolCount);
            for (int i = 0; i < toolCount; ++i) {
                int toolLength;
                is.read((char*)&toolLength, sizeof(toolLength));
                obj.dataAnalysisTools[i].resize(toolLength);
                is.read(&obj.dataAnalysisTools[i][0], toolLength);
            }
            is.read((char*)&obj.completedAnalysesCount, sizeof(obj.completedAnalysesCount));
            
            int infoSize;
            string levelStr;

            is.read((char*)&infoSize, sizeof(infoSize));
            levelStr.resize(infoSize);
            is.read(&levelStr[0], infoSize);
            if (levelStr == "Junior") obj.specializationLevel = SpecializationLevel::Junior;
            else if (levelStr == "Middle") obj.specializationLevel = SpecializationLevel::Middle;
            else if (levelStr == "Senior") obj.specializationLevel = SpecializationLevel::Senior;
        }
        else {
            is.setstate(ios::failbit);
        }
        return is;
    }
};
