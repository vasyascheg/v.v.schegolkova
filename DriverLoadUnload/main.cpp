#include <Windows.h>

#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>


bool setDriverPrivilege()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES privileges;
    privileges.PrivilegeCount = 1;
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        //std::cout << "Failed to open process." << std::endl;
        return false;
    }

    if (!LookupPrivilegeValue(0, SE_LOAD_DRIVER_NAME, &privileges.Privileges[0].Luid))
    {
        //std::cout << "Failed to look up privileges." << std::endl;
        return false;
    }

    if (!AdjustTokenPrivileges(hToken, false, &privileges, sizeof(privileges), 0, 0))
    {
        //std::cout << "Failed to adjust token privileges." << std::endl;
        return false;
    }

    CloseHandle(hToken);
    return true;
}

//int setDriverPrivilege()
//{
//TOKEN_PRIVILEGES tp;
//LUID luid;

//if (!LookupPrivilegeValue(
//  NULL,            // lookup privilege on local system
//  SE_LOAD_DRIVER_NAME,   // privilege to lookup
//  &luid))        // receives LUID of privilege
//{
//  //printf("LookupPrivilegeValue error: %un", GetLastError());
//  return false;
//}

//tp.PrivilegeCount = 1;
//tp.Privileges[0].Luid = luid;
////if (bEnablePrivilege)
//  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
////else
////  tp.Privileges[0].Attributes = 0;

//// Enable the privilege or disable all privileges.

//if (!AdjustTokenPrivileges(
//  hToken,
//  FALSE,
//  &tp,
//  sizeof(TOKEN_PRIVILEGES),
//  (PTOKEN_PRIVILEGES)NULL,
//  (PDWORD)NULL))
//{
//  //printf("AdjustTokenPrivileges error: %un", GetLastError());
//  return false;
//}
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!setDriverPrivilege()){
        QMessageBox::critical(nullptr, "Ошибка!", "Не удалось повысить уровень привилегий");
    }
    MainWindow w;
    a.setQuitOnLastWindowClosed(false);
       // w.show();
    return a.exec();
}
