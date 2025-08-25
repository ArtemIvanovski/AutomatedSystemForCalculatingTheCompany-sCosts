#include "System.h"


int System::delayPress() {
    char ch;
    while ((ch = _getch()) != 13) { 
        if (ch == 27) { 
            return 0;
        }
    }
    return 1;
}
string System::toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return tolower(c);
        });
    return result;
}

int System::getIntInput(const std::string& prompt, int x, int y) {
    setCursorPosition(x, y);
    printWithColor(prompt, FOREGROUND_INTENSITY | FOREGROUND_GREEN);

    string input;
    char ch;

    while ((ch = _getch()) != 13) { 
        if (ch == 27) { 
            return -1;  
        }

        if (ch == 8 && !input.empty()) { 
            input.pop_back();
            cout << "\b \b"; 
        }
        else if (isdigit(ch)) { 
            cout << ch;
            input.push_back(ch);
        }
    }

    cout << endl;

    try {
        return stoi(input); 
    }
    catch (const invalid_argument& e) {
        return -1;
    }
}

string System::getInput(const string& prompt, int x, int y, bool isPassword) {
    setCursorPosition(x, y);
    printWithColor(prompt, FOREGROUND_INTENSITY | FOREGROUND_GREEN);

    string input;
    char ch;

    while ((ch = _getch()) != 13) { 
        if (ch == 27) { 
            return "";  
        }

        if (ch == 8 && !input.empty()) { 
            input.pop_back();
            cout << "\b \b"; 
        }
        else {
            if (isPassword) {
                cout << '*';
            }
            else {
                cout << ch;
            }
            input.push_back(ch);
        }
    }

    cout << endl;

    return input;
}

int System::getUserChoice(int size, string cases[], int x, int y, bool setPostion) {
    int selectedIdx = 0;
    COORD coord = getCursorPosition();
    int input;

    while (true) {
        clearArea(coord.Y, size + 1); 

        for (int i = 0; i < size; i++) {
            if (i == selectedIdx) {
                printWithColor("> ", FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, x - 2, y + i, true);
                if (setPostion)
                    printWithColor(cases[i], FOREGROUND_INTENSITY | FOREGROUND_GREEN, x, y + i, true);
                else
                    printWithColor(cases[i], FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                cout << endl;
            }
            else {
                if (setPostion)
                    printWithColor(cases[i], FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, x, y + i, true);
                else
                    cout << "  " << cases[i] << endl;
            }
        }

        input = _getch(); 

        if (input == 27) { 
            return -1; 
        }
        else if (input == 72) { 
            if (selectedIdx > 0) {
                selectedIdx--; 
            }
        }
        else if (input == 80) {
            if (selectedIdx < size - 1) {
                selectedIdx++; 
            }
        }
        else if (input == 13) { 
            return selectedIdx + 1;
        }
    }
}

void System::clearArea(int startY, int lines) {
    COORD coord;
    coord.X = 0;
    coord.Y = startY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 

    for (int i = 0; i < lines; i++) {
        cout << string(80, ' '); 
    }

    coord.Y = startY; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD System::getCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.dwCursorPosition; 
}

void System::setCursorPosition(int x, int y) {
    COORD coord{};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void System::clearWindow()
{
    system("cls");
}

double System::inputDouble()
{
    char ch;
    double value = 0.0;
    string inputStr;
    bool decimalPoint = false; 

    while (true) {
        ch = _getch(); 

        if (ch == 13 && !inputStr.empty()) { 
            value = stod(inputStr); 
            return value;
        }
        else if (ch == 27) {
            return -1.0;
        }
        else if (ch == 8 && !inputStr.empty()) { 
            inputStr.pop_back();
            cout << "\b \b"; 
        }
        else if (isdigit(ch) || (ch == '.' && !decimalPoint)) {
            if (ch == '.') {
                decimalPoint = true;
            }
            inputStr += ch; 
            cout << ch; 
        }
    }
}

void System::printWithColor(const string& text, int color, int x, int y, bool setPosition) {
    if (setPosition)
        setCursorPosition(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

string System::getInputWithMask(const string& prompt, int x, int y, bool isPassword) {
    setCursorPosition(x, y);
    printWithColor(prompt, FOREGROUND_INTENSITY | FOREGROUND_GREEN);

    string input;
    char ch;

    while ((ch = _getch()) != 13) { 
        if (ch == 27) { 
            return "_";  
        }

        if (ch == 8 && !input.empty()) {
            input.pop_back();
            cout << "\b \b"; 
        }
        else {
            if (isPassword) {
                cout << '*';
            }
            else {
                cout << ch;
            }
            input.push_back(ch);
        }
    }

    cout << endl;

    return input;
}

bool System::isValidEmail(const string& email) {
    const regex pattern(
        R"(([\w\.-]+)@([\w\.-]+)\.([a-zA-Z]{2,}))");

    return regex_match(email, pattern);
}