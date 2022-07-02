#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnDrvLoad_clicked();

    void on_btnDrvUnload_clicked();

private:
   // Q_DISABLE_COPY(MainWindow);

    Ui::MainWindow *ui;
    QSystemTrayIcon         * trayIcon;
    QString translateMessage(HRESULT code);
};
#endif // MAINWINDOW_H
