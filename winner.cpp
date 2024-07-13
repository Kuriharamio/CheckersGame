#include "winner.h"
#include "ui_winner.h"

Winner::Winner(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Winner)
{
    ui->setupUi(this);
    setWindowTitle("排行榜");
    QString lastBackground = settings.value("Winner_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui->label_2->setStyleSheet(StyleSheet);
    }
}

Winner::~Winner()
{
    delete ui;
}



void Winner::ShowWinner(QList<User> winners, Winner* winner)
{
    QString Result = QString("恭喜玩家 %1 获得了冠军\n\n排行榜：\n").arg(winners[0].getUsername());
    for(int i = 0; i<winners.size(); i++){
        Result.append(QString("第%1名、%2\t\n").arg(i+1).arg(winners[i].getUsername()));
    }
    ui->label->setText(Result);
    winner->show();
}

void Winner::on_over_clicked()
{
    this->close();
}



