#pragma once
#include "Liberies.h"

class System {
public:
    System() {
        setlocale(LC_ALL, "ru");
        SetConsoleCP(1251);
    }
    string getInputWithMask(const string& prompt, int x, int y, bool isPassword);
    bool isValidEmail(const string& email);
    int delayPress();
    string toLower(const string& str);
    int getIntInput(const string& prompt, int x, int y);
    string getInput(const string& prompt, int x, int y, bool isPassword);
    int getUserChoice(int size, string cases[], int x = 0, int y = 0, bool setPostion = false);
    void clearArea(int startY, int lines);
    void setCursorPosition(int x, int y);
    void clearWindow();
    double inputDouble();
    void printWithColor(const string& text, int color, int x = 0, int y = 0, bool setPosition = false);
    COORD getCursorPosition();
};

