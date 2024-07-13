#ifndef WINNER_H
#define WINNER_H

#include <QDialog>
#include <QSettings>
#include "user.h"


extern QSettings settings;
extern QList<User> players;
extern QList<User> winners;


namespace Ui {
class Winner;
}

class Winner : public QDialog
{
    Q_OBJECT

public:
    explicit Winner(QWidget *parent = nullptr);
    void ShowWinner(QList<User> winners, Winner* winner);
    ~Winner();

private slots:


    void on_over_clicked();


private:
    Ui::Winner *ui;
};

#endif // WINNER_H
