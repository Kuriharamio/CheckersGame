#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QSettings>
extern QSettings settings;

namespace Ui {
class Help;
}

class Help : public QWidget
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    int page = 0;
    int page_num = 4;
    ~Help();

private slots:
    void on_Next_clicked();

    void on_Last_clicked();

    void on_Back_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H
