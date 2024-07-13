#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "./ui_mainwindow.h"
#include "settingwidget.h"
#include "mode_selection.h"
#include "help.h"
#include "board.h"

extern QSettings settings;
extern Ui::Checkers_Game* ui_mainwindow;
QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_PVP_clicked();
    void on_PVE_clicked();
    void on_Setting_clicked();
    void on_effect_on_clicked();
    void on_bgm_on_clicked();
    void on_effect_off_clicked();
    void on_bgm_off_clicked();
    void on_button_archive_clicked();
    void on_Exit_clicked();
    void on_button_Load_clicked();
    void on_Start_Game_clicked();
    void on_Help_clicked();

private:

};

#endif // MAINWINDOW_H
