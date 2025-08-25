#include "BeginWindow.h"
#include "AuthWindow.h"
#include "RegWindow.h"
#include "Data.h"
#include "FileManager.h"
#include "ErrorWindow.h"
#include "ManagerPanelWindow.h"
#include "AnalystPanelWindow.h"

int main() {
    HWND consoleWindow = GetConsoleWindow();

    if (consoleWindow != NULL) {
        RECT desktopRect;
        GetWindowRect(GetDesktopWindow(), &desktopRect);
        SetWindowPos(consoleWindow, HWND_TOP, desktopRect.left, desktopRect.top, desktopRect.right - desktopRect.left, desktopRect.bottom - desktopRect.top, SWP_SHOWWINDOW);
    }
    int id = 0;
    BeginWindow beginWindow;
    FileManager<Data> dataFileManager;
    FileManager<Manager> managerFileManager;
    FileManager<Analyst> analystFileManager;

    while (true) {
        id = 0;
        while (!id) {
            switch (beginWindow.show())
            {
            case -1:
            case 3:
                beginWindow.close();
                return 0;
            case 1: {
                AuthWindow authWindow;
                if (authWindow.show() == 1) {
                    try
                    {
                        id = dataFileManager.readFromFile().checkAuthorize(authWindow.getLogin(), authWindow.getPassword());
                        beginWindow.close();
                    }
                    catch (const CustomException& msg)
                    {
                        ErrorWindow errorWindow(msg.what());
                    }
                }
                break;
            }
            case 2: {
                RegWindow regWindow;
                if (regWindow.show() == 1) {
                    id = dataFileManager.getUniqueID();
                    Data data(id, regWindow.getLogin(), regWindow.getPassword(), regWindow.getRole());
                    dataFileManager.writeToFile(data);
                    if (regWindow.getRole() == "manager") {
                        Manager manager(id, regWindow.getName(), regWindow.getEmail(), 0);
                        managerFileManager.writeToFile(manager);
                    }
                    else {
                        Analyst analyst(id, regWindow.getName(), regWindow.getEmail(), 0);
                        analystFileManager.writeToFile(analyst);
                    }
                }
            }
                  break;
            }
        }

        if (dataFileManager.readFromFile().getDataById(id).getRole() == "manager") {
            Manager manager = managerFileManager.readFromFile().getDataById(id);
            ManagerPanelWindow managerPanelWindow(manager, managerFileManager);
            managerPanelWindow.show();
        }
        else {
            Analyst analyst = analystFileManager.readFromFile().getDataById(id);
            AnalystPanelWindow analystPanelWindow(analyst, analystFileManager);
            analystPanelWindow.show();
        }
    }
}