#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "./ui_mainwindow.h"
#include "ui_settingwidget.h"
#include "chess.h"
#include "user.h"

QList<User> users;
QList<User> players;
QList<User> winners;
Chess chessBoard[17][17];
int players_num;

QSettings settings("Kurihara_Mio", "Checkers_Game");

QMediaPlayer *player_bgm = new QMediaPlayer;
QAudioOutput *audioOutput = new QAudioOutput;

Ui::SettingWidget *ui_setting = new Ui::SettingWidget;
Ui::Checkers_Game* ui_mainwindow = new Ui::Checkers_Game;

bool archive;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!settings.value("CountDown_set").toInt()){
         settings.setValue("CountDown_set",20);
    }
    player_bgm->setAudioOutput(audioOutput);
    QUrl bgm_path = settings.value("BGM_Path").toUrl();
    if(!bgm_path.isEmpty()){
        player_bgm->setSource(bgm_path);
    }else{
        player_bgm->setSource(QUrl("qrc:/media/assets/bgm.mp3"));
    }
    if(settings.value("bgm").toString() == "on"){
        player_bgm->play();
    }

    users.append(User(1,"1", 0, false, false,"red","NONE",4,false));
    users.append(User(2, "2", 0, false, false,"purple","NONE",4,false));
    users.append(User(3, "3", 0, false, false,"blue","NONE",4,false));
    users.append(User(4,"4", 0, false, false,"green","NONE",4,false));
    users.append(User(5, "5", 0, false, false,"yellow","NONE",4,false));
    users.append(User(6, "6", 0, false, false,"orange","NONE",4,false));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Checkers_Game_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
