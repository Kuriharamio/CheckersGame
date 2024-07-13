#include "select_player_num.h"
#include "ui_select_player_num.h"

Select_player_num::Select_player_num(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Select_player_num)
{
    ui->setupUi(this);
    QString lastBackground = settings.value("Menu_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui->label->setStyleSheet(StyleSheet);
    }
}

Select_player_num::~Select_player_num()
{
    delete ui;
}


void Select_player_num::on_two_clicked()
{
    archive = false;
    settings.setValue("computer_num",0);
    settings.setValue("human_num",2);
    board *Board = new board(this);
    Board->show();
}


void Select_player_num::on_three_clicked()
{
    archive = false;
    settings.setValue("computer_num",0);
    settings.setValue("human_num",3);
    board *Board = new board(this);
    Board->show();
}


void Select_player_num::on_four_clicked()
{
    archive = false;
    settings.setValue("computer_num",0);
    settings.setValue("human_num",4);
    board *Board = new board(this);
    Board->show();
}


void Select_player_num::on_five_clicked()
{
    archive = false;
    settings.setValue("computer_num",0);
    settings.setValue("human_num",5);
    board *Board = new board(this);
    Board->show();
}


void Select_player_num::on_six_clicked()
{
    archive = false;
    settings.setValue("computer_num",0);
    settings.setValue("human_num",6);
    board *Board = new board(this);
    Board->show();
}


void Select_player_num::on_Back_clicked()
{
    this->close();
}

