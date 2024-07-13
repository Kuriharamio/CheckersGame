#include "select_pve.h"
#include "ui_select_pve.h"

Select_PVE::Select_PVE(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Select_PVE)
{
    ui->setupUi(this);
    QString lastBackground = settings.value("Menu_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui->label->setStyleSheet(StyleSheet);
    }

    settings.setValue("human_num",0);
    settings.setValue("computer_num",0);
    settings.setValue("computer_difficulty","NONE");
    settings.setValue("PVE_select_finished",false);
    QButtonGroup *humanGroup = new QButtonGroup(this);
    QButtonGroup *computerGroup = new QButtonGroup(this);
    for(int i = 1;i<6;i++){
        QRadioButton* human_button = findChild<QRadioButton*>(QString("human_%1").arg(i));
        QRadioButton* computer_button = findChild<QRadioButton*>(QString("computer_%1").arg(i));
        humanGroup->addButton(human_button);
        computerGroup->addButton(computer_button);
    }
}

Select_PVE::~Select_PVE()
{
    delete ui;
}



void Select_PVE::on_human_1_clicked(bool checked)
{
    settings.setValue("human_num",1);
}


void Select_PVE::on_human_2_clicked(bool checked)
{
    settings.setValue("human_num",2);
}


void Select_PVE::on_human_3_clicked(bool checked)
{
    settings.setValue("human_num",3);
}


void Select_PVE::on_human_4_clicked(bool checked)
{
    settings.setValue("human_num",4);
}


void Select_PVE::on_human_5_clicked(bool checked)
{
    settings.setValue("human_num",5);
}



void Select_PVE::on_computer_1_clicked(bool checked)
{
    settings.setValue("computer_num",1);
}


void Select_PVE::on_computer_2_clicked(bool checked)
{
    settings.setValue("computer_num",2);
}


void Select_PVE::on_computer_3_clicked(bool checked)
{
    settings.setValue("computer_num",3);
}


void Select_PVE::on_computer_4_clicked(bool checked)
{
    settings.setValue("computer_num",4);
}


void Select_PVE::on_computer_5_clicked(bool checked)
{
    settings.setValue("computer_num",5);
}


void Select_PVE::on_computer_simple_clicked(bool checked)
{
    settings.setValue("computer_difficulty","simple");
}


void Select_PVE::on_computer_normal_clicked(bool checked)
{
    settings.setValue("computer_difficulty","normal");
}


void Select_PVE::on_computer_difficult_clicked(bool checked)
{
    settings.setValue("computer_difficulty","difficult");
}


void Select_PVE::on_computer_master_clicked(bool checked)
{
    settings.setValue("computer_difficulty","master");
}



void Select_PVE::on_pushButton_clicked()
{
    int human_num = settings.value("human_num").toInt();
    int computer_num = settings.value("computer_num").toInt();
    QString difficulty = settings.value("computer_difficulty").toString();
    if(difficulty != "NONE"){
        if((human_num+computer_num)<=6&&(human_num+computer_num)>=2&&human_num&&computer_num){
            settings.setValue("players_num",human_num+computer_num);
            settings.setValue("computer_difficulty",difficulty);

            if(difficulty != "NONE"&&(human_num+computer_num)<=6&&(human_num+computer_num)>=2&&human_num&&computer_num){
                archive = false;
                board *Board = new board(this);
                Board->show();
            }
        }else if(!human_num&&computer_num){
            QMessageBox::warning(nullptr, "警告", "未选择玩家数量，请重新选择！");
        }else if(!computer_num&&human_num){
            QMessageBox::warning(nullptr, "警告", "未选择电脑数量，请重新选择！");
            board *Board = new board(this);
            Board->show();     }else if(!human_num&&!computer_num){
            QMessageBox::warning(nullptr, "警告", "未选择玩家数量和电脑数量，请重新选择！");
        }else{
            QMessageBox::warning(nullptr, "警告", "总数多于6人，请重新选择！");
        }
    }else{
        QMessageBox::warning(nullptr, "警告", "未选择难度，请重新选择！");
    }
}


void Select_PVE::on_Back_clicked()
{
    settings.setValue("human_num",0);
    settings.setValue("computer_num",0);
    settings.setValue("computer_difficulty","NONE");
    this->close();
}

