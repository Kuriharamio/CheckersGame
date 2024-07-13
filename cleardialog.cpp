#include "cleardialog.h"
#include "ui_cleardialog.h"

ClearDialog::ClearDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClearDialog)
{
    ui->setupUi(this);
}

ClearDialog::~ClearDialog()
{
    delete ui;
}

void ClearDialog::on_buttonBox_accepted()
{
    settings.clear();
    player_bgm->pause();
    ui_setting->bgm->setChecked(false);
    ui_setting->effect->setChecked(false);
    ui_setting->CountDown->setChecked(false);

}

