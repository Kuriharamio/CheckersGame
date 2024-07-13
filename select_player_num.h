#ifndef SELECT_PLAYER_NUM_H
#define SELECT_PLAYER_NUM_H

#include <QWidget>

#include "board.h"

namespace Ui {
class Select_player_num;
}

class Select_player_num : public QWidget
{
    Q_OBJECT

public:
    explicit Select_player_num(QWidget *parent = nullptr);
    ~Select_player_num();

private slots:
    void on_two_clicked();

    void on_three_clicked();

    void on_four_clicked();

    void on_five_clicked();

    void on_six_clicked();

    void on_Back_clicked();

private:
    Ui::Select_player_num *ui;
};

#endif // SELECT_PLAYER_NUM_H
