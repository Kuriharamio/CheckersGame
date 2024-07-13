#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QWidget>
#include <QPalette>
#include <QSettings>
#include <QInputDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include "user.h"
#include "cleardialog.h"
#include "./ui_mainwindow.h"

extern QList<User> users;
extern QList<User> players;
extern QSettings settings;
extern Ui::Checkers_Game* ui_mainwindow;
extern QMediaPlayer *player_bgm;
extern QAudioOutput *audioOutput;


namespace Ui {
class SettingWidget;
}
extern Ui::SettingWidget *ui_setting;
class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

private slots:
    void on_Back_clicked();

    void on_Setting_Background_Path_clicked();

    void on_BGM_Path_clicked();

    void on_effect_clicked(bool checked);

    void on_bgm_clicked(bool checked);

    void on_menu_background_Path_clicked();

    void on_Board_Background_Path_clicked();

    void on_Change_Word_Color_clicked();

    void on_Red_Image_clicked();

    void on_Purple_Image_clicked();

    void on_Blue_Image_clicked();

    void on_Green_Image_clicked();

    void on_Yellow_Image_clicked();

    void on_Orange_Image_clicked();

    void on_red_name_clicked();

    void on_purple_name_clicked();

    void on_blue_name_clicked();

    void on_green_name_clicked();

    void on_yellow_name_clicked();

    void on_orange_name_clicked();


    void on_Winner_Background_Path_clicked();

    void on_CountDown_set_clicked();

    void on_CountDown_clicked(bool checked);

    void on_clear_clicked();

private:
    QString Setting_Background_Path;
    QString BGM_Path;
    bool effect;
    bool bgm;
    QString Menu_Background_Path;
    QString Board_Background_Path;
    QString Winner_Background_Path;
    QString Word_Color;
    QString Red_Image_Path;
    QString Purple_Image_Path;
    QString Blue_Image_Path;
    QString Green_Image_Path;
    QString Yellow_Image_Path;
    QString Orange_Image_Path;
    QString Icon_Path;
    QString Button_Color;
};

#endif // SETTINGWIDGET_H
