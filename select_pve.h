#ifndef SELECT_PVE_H
#define SELECT_PVE_H

#include <QWidget>
#include <QDialog>
#include <QSettings>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>

#include "board.h"

extern QSettings settings;
namespace Ui {
class Select_PVE;
}

class Select_PVE : public QWidget
{
    Q_OBJECT

public:
    explicit Select_PVE(QWidget *parent = nullptr);
    ~Select_PVE();


private slots:
    void on_human_1_clicked(bool checked);

    void on_human_2_clicked(bool checked);

    void on_human_3_clicked(bool checked);

    void on_human_4_clicked(bool checked);

    void on_human_5_clicked(bool checked);


    void on_computer_1_clicked(bool checked);

    void on_computer_2_clicked(bool checked);

    void on_computer_3_clicked(bool checked);

    void on_computer_4_clicked(bool checked);

    void on_computer_5_clicked(bool checked);


    void on_computer_simple_clicked(bool checked);

    void on_computer_normal_clicked(bool checked);

    void on_computer_difficult_clicked(bool checked);

    void on_computer_master_clicked(bool checked);

    void on_pushButton_clicked();

    void on_Back_clicked();

private:
    Ui::Select_PVE *ui;
};

#endif // SELECT_PVE_H
