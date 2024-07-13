#include "mode_selection.h"
#include "ui_mode_selection.h"

Mode_Selection::Mode_Selection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mode_Selection)
{
    ui->setupUi(this);
    QString lastBackground = settings.value("Menu_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui->label->setStyleSheet(StyleSheet);
    }
}

Mode_Selection::~Mode_Selection()
{
    delete ui;
}

void Mode_Selection::on_Back_clicked()
{
    this->close();
}


void Mode_Selection::on_PVE_clicked()
{
    settings.setValue("human_num",0);
    settings.setValue("computer_num",0);
    settings.setValue("computer_difficulty","NONE");
    Select_PVE *dialog_1 = new Select_PVE(this);
    dialog_1->show();

}



void Mode_Selection::on_Local_Battle_clicked()
{
    Select_player_num *dialog_2 = new Select_player_num(this);
    dialog_2->show();
}


void Mode_Selection::on_Online_Battle_clicked()
{
    archive = true;
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Open Chess Board",
        QDir::homePath(),
        "Chess Board Files (*.chessboard)"
        );

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            // 处理错误
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_12);
        QString difficulty;
        in >> difficulty;
        settings.setValue("computer_difficulty",difficulty);
        in >> players >> winners;

        for (int i = 0; i < 17; ++i) {
            for (int j = 0; j < 17; ++j) {
                in >> chessBoard[i][j];
            }
        }

        file.close();



        board *Board = new board(this);
        Board->show();
    }
}

