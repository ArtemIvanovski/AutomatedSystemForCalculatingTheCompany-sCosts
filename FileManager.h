#pragma once
#include "CustomException.h"
#include "List.h"
#include "Manager.h"
#include "Analyst.h"
#include "Project.h"
#include "DirectExpense.h"
#include "IndirectExpense.h"

template <typename T>
class FileManager {
private:
    string filename;  

public:
    FileManager() {
        filename = "./database/" + determineFilename();
    }

    List<T> readFromFile() {
        ifstream file(filename, ios::binary);
        List<T> dataList;

        if (!file.is_open()) {
            ofstream newFile(filename, ios::binary);
            newFile.close();
            throw CustomException("File is missing, a new file was created.");
        }

        T data;
        while (file >> data) {
            dataList.append(data);
        }
        file.close();

        return dataList;
    }

    void rewriteFile(const T& newObject) {
        List<T> dataList = readFromFile();

        bool objectFound = false;  

        for (int i = 0; i < dataList.length(); i++) {
            if (dataList[i].getId() == newObject.getId()) {
                dataList[i] = newObject;
                objectFound = true;
                break;
            }
        }

        if (!objectFound) {
            throw CustomException("Object with the given ID not found.");
        }

        clearFile();

        for (int i = 0; i < dataList.length(); i++) {
            writeToFile(dataList[i]);
        }
    }

    int getUniqueID() {
        List<T> dataList = readFromFile();

        set<int> ids; 

        for (int i = 0; i < dataList.length(); i++) {
            ids.insert(dataList[i].getId());
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 1000);

        int newID;
        do {
            newID = distrib(gen); 
        } while (ids.find(newID) != ids.end());

        return newID;
    }

    void writeToFile(const T& data) {
        ofstream file(filename, ios::binary | ios::app);
        if (!file.is_open()) {
            throw CustomException("Unable to open file for writing.");
        }
        file << data;
        file.close();
    }

    void clearFile() {
        ofstream file(filename, ios::binary | ios::trunc);
        if (!file.is_open()) {
            throw CustomException("Unable to open file for clearing.");
        }
        file.close();
    }

    void deleteByData(T& data) {
        List<T> dataList = readFromFile();

        dataList.removeData(data);

        clearFile();

        for (int i = 0; i < dataList.length(); i++) {
            writeToFile(dataList[i]);
        }
    }

private:
    string determineFilename() {
        if constexpr (is_same<T, Data>::value) {
            return "data.bin";
        }
        else if constexpr (is_same<T, Manager>::value) {
            return "manager.bin";
        }
        else if constexpr (is_same<T, Project>::value) {
            return "project.bin";
        }
        else if constexpr (is_same<T, DirectExpense>::value) {
            return "directExpense.bin";
        }
        else if constexpr (is_same<T, IndirectExpense>::value) {
            return "indirectExpense.bin";
        }
        else if constexpr (is_same<T, Analyst>::value) {
            return "analyst.bin";
        }
        else {
            throw CustomException("Unsupported type for file management.");
        }
    }
};