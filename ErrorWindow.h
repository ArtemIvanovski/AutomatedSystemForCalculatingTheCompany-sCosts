#pragma once
#include "BaseWindow.h"

class ErrorWindow : public BaseWindow {
public:
    ErrorWindow(const string errorMsg) {
        show(errorMsg);
    }
    void show(const string errorMsg) {
        system.clearWindow();
        cout << "==============================" << endl;
        cout << "          ÎØÈÁÊÀ              " << endl;
        cout << "==============================" << endl;
        system.printWithColor(errorMsg, FOREGROUND_INTENSITY | FOREGROUND_RED);
        system.delayPress();
        close();
    }

    void close() override {
        system.clearWindow();
    }
};