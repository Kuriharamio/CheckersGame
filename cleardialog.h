#ifndef CLEARDIALOG_H
#define CLEARDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QtMultimedia/QMediaPlayer>
#include "ui_settingwidget.h"
extern Ui::SettingWidget *ui_setting;
extern QSettings settings;
extern QMediaPlayer *player_bgm;
namespace Ui {
class ClearDialog;
}

class ClearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClearDialog(QWidget *parent = nullptr);
    ~ClearDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ClearDialog *ui;
};

#endif // CLEARDIALOG_H
