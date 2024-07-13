#ifndef MODE_SELECTION_H
#define MODE_SELECTION_H

#include <QWidget>

#include <QDataStream>
#include <QFile>

#include "select_player_num.h"
#include "select_pve.h"

extern bool archive;

namespace Ui {
class Mode_Selection;
}

class Mode_Selection : public QWidget
{
    Q_OBJECT

public:
    explicit Mode_Selection(QWidget *parent = nullptr);
    ~Mode_Selection();


private slots:
    void on_Back_clicked();
    void on_PVE_clicked();

    void on_Local_Battle_clicked();


    void on_Online_Battle_clicked();

private:
    Ui::Mode_Selection *ui;
};

#endif // MODE_SELECTION_H
