#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Help)
{
    ui->setupUi(this);
    QString lastBackground = settings.value("Menu_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui->label->setStyleSheet(StyleSheet);
    }
    page = 1;
}

Help::~Help()
{
    delete ui;
}

void Help::on_Next_clicked()
{
    page++;
    if(page==2){
        ui->Last->setStyleSheet("QPushButton {border-image: url(:/images/assets/button_none.png);}QPushButton:hover {border-image: url(:/images/assets/button_hover.png);}QPushButton:pressed {border-image: url(:/images/assets/button_press.png);}");
        ui->Last->setText("上一页");
    }
    if(page<=page_num){
        ui->pages->setStyleSheet(QString("border-image: url(:/images/assets/help_%1.png);").arg(page));
    }
    if(page==page_num){
        ui->Next->setText("结束");
    }
    if(page==page_num+1){
        this->close();
    }
}


void Help::on_Last_clicked()
{
    page--;
    if(page>0)
        ui->pages->setStyleSheet(QString("border-image: url(:/images/assets/help_%1.png);").arg(page));
    if(page==0)
        page=1;
    if(page==1)
    {
        ui->Last->setStyleSheet("border-image: url(:/images/assets/transparent.png);");
        ui->Last->setText("");
    }

    if(page<page_num)
         ui->Next->setText("下一页");
}


void Help::on_Back_clicked()
{
    this->close();
}

