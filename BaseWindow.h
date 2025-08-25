#pragma once
#include "System.h"
#include "Window.h"

class BaseWindow : public Window {
protected:
    System system;

public:
    int show() override {
        system.clearWindow();
        system.printWithColor("Showing base window.\n", FOREGROUND_GREEN);
        return 0;
    }

    void close() override {
        system.printWithColor("Closing base window.\n", FOREGROUND_RED);
    }
};