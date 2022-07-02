#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QSystemTrayIcon>
#include <QMenu>

// для вызова FltLoadFilter
#define _AMD64_
//#include <fltKernel.h>
#include <Windows.h>
//#include <winerror.h>
#include <fltuser.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);

    QIcon * myicon = new QIcon(":/OK.ico");

    trayIcon->setIcon(*myicon);

    trayIcon->setToolTip("Загрузка и выгрузка драйвер-фильтра");

    QMenu * menu = new QMenu(this);
    QAction * load = new QAction(("Загрузить"), this);
    QAction * unload = new QAction(("Выгрузить"), this);
    QAction * quitAction = new QAction(("Выход"), this);

    menu->addAction(load);
    menu->addAction(unload);
    menu->addAction(quitAction);

    connect(load, SIGNAL(triggered()), this, SLOT(on_btnDrvLoad_clicked()));
    connect(unload, SIGNAL(triggered()), this, SLOT(on_btnDrvUnload_clicked()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(deleteLater()));

    trayIcon->setContextMenu(menu);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::translateMessage(HRESULT code){
    qDebug() << "HRESULT code = " << Qt::hex << code;
    qDebug() << "unsigned HRESULT code = " << Qt::hex << (unsigned)code;
    qDebug()  << Qt::hex << ERROR_ALREADY_EXISTS;
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_ALREADY_EXISTS);
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_FILE_NOT_FOUND);
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_SERVICE_ALREADY_RUNNING);
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_BAD_EXE_FORMAT);
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_BAD_DRIVER);
    qDebug()  << Qt::hex << (unsigned)HRESULT_FROM_WIN32 (ERROR_INVALID_IMAGE_HASH);


    switch(code){
        case HRESULT_FROM_WIN32 (ERROR_ALREADY_EXISTS):
            return "The minifilter driver is already running.";
        case HRESULT_FROM_WIN32 (ERROR_FILE_NOT_FOUND):
            return "No matching minifilter driver was found.";
        case HRESULT_FROM_WIN32 (ERROR_SERVICE_ALREADY_RUNNING):
            return "The minifilter driver is already running.";
        case HRESULT_FROM_WIN32 (ERROR_BAD_EXE_FORMAT):
            return "The load image for the minifilter driver specified by lpFilterName is invalid.";
        case HRESULT_FROM_WIN32 (ERROR_BAD_DRIVER):
            return "The load image for the minifilter driver specified by lpFilterName is invalid.";
        case HRESULT_FROM_WIN32 (ERROR_INVALID_IMAGE_HASH):
            return "The minifilter driver has an invalid digital signature.";
        default:
            return QString("Неизвестная ошибка ") + QString::number((unsigned)code, 16);
    }
}

void MainWindow::on_btnDrvLoad_clicked()
{
    //UNICODE_STRING filter_name = RTL_CONSTANT_STRING(L"PassThrough");
    //NTSTATUS result = FltLoadFilter(&filter_name);

    HRESULT result = FilterLoad(L"PassThrough");
    if (result==S_OK){
        QMessageBox::information(nullptr, "OK", "Драйвер загружен");
    }
    else {
        QMessageBox::critical(nullptr, "Внимание!", translateMessage(result));
    }
}


void MainWindow::on_btnDrvUnload_clicked()
{
    // UNICODE_STRING filter_name = RTL_CONSTANT_STRING(L"PassThrough");
    // NTSTATUS result = FltUnloadFilter(&filter_name);
    HRESULT result = FilterUnload(L"PassThrough");
    if (result==S_OK){
        QMessageBox::information(nullptr, "OK", "Драйвер выгружен");
    }
    else {
        QMessageBox::critical(nullptr, "Внимание!", translateMessage(result));
    }
}



