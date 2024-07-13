#ifndef board_H
#define board_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QSettings>
#include <QTimer>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>

#include <QMessageBox>

#include "user.h"
#include "chess.h"
#include "rule.h"
#include "computer.h"

extern QSettings settings;
extern QList<User> users;
extern QList<User> players;
extern Chess chessBoard[17][17];
extern bool archive;

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = nullptr);

    User *currentPlayer = nullptr;
    User *nextPlayer = nullptr;
    User *regretUser = nullptr;
    QMediaPlayer *player1 = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;


    Rule rule;
    Computer computer;

    int human_num;
    int computer_num;
    int players_num;

    int count_down = settings.value("CountDown_set").toInt();
    QString difficulty = settings.value("computer_difficulty").toString();
    QString lastBackground = settings.value("Board_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));


    Chess chessBoard_record[17][17];
    int pctopc = 1;
    int Last_Step;


    ~board();

private slots:
    void staminaUp(void);
    void countDown(void);
    void updateBoard(Chess chessBoard_model[17][17]);
    void swapButtonStyle(QPushButton *button1,QPushButton *button2);
    void moveUpDown(QPushButton *button, int pos);
    void swap(QPushButton *button1,QPushButton *button2,QString player_type);
    QString GetChessColor(QPushButton *button, Chess chessBoard_model[17][17]);
    void copyBoard(Chess chessBoard1[17][17],Chess chessBoard2[17][17]);
    void SwapChessColors(int raw_start, int col_start, int raw_end, int col_end);
    void Init(int n,Chess chessboard[17][17]);
    void SettingMaching(int n);

    void clicked(QPushButton *button);

    void on_button_back_clicked();

    void on_board_0_12_clicked();

    void on_board_1_11_clicked();

    void on_board_1_12_clicked();

    void on_board_2_10_clicked();

    void on_board_5_6_clicked();

    void on_board_2_11_clicked();

    void on_board_2_12_clicked();

    void on_board_3_9_clicked();

    void on_board_3_10_clicked();

    void on_board_3_11_clicked();

    void on_board_4_11_clicked();

    void on_board_3_12_clicked();

    void on_board_4_4_clicked();

    void on_board_4_5_clicked();

    void on_board_4_6_clicked();

    void on_board_4_7_clicked();

    void on_board_4_8_clicked();

    void on_board_4_9_clicked();

    void on_board_4_10_clicked();

    void on_board_4_12_clicked();

    void on_board_4_13_clicked();

    void on_board_4_14_clicked();

    void on_board_4_15_clicked();

    void on_board_4_16_clicked();

    void on_board_5_4_clicked();

    void on_board_5_5_clicked();

    void on_board_5_7_clicked();

    void on_board_5_8_clicked();

    void on_board_5_9_clicked();

    void on_board_5_10_clicked();

    void on_board_5_11_clicked();

    void on_board_5_12_clicked();

    void on_board_5_13_clicked();

    void on_board_5_14_clicked();

    void on_board_5_15_clicked();

    void on_board_6_4_clicked();

    void on_board_6_5_clicked();

    void on_board_6_6_clicked();

    void on_board_6_7_clicked();

    void on_board_6_8_clicked();

    void on_board_6_9_clicked();

    void on_board_6_10_clicked();

    void on_board_6_11_clicked();

    void on_board_6_12_clicked();

    void on_board_6_13_clicked();

    void on_board_6_14_clicked();

    void on_board_7_4_clicked();

    void on_board_7_5_clicked();

    void on_board_7_6_clicked();

    void on_board_7_7_clicked();

    void on_board_7_8_clicked();

    void on_board_7_9_clicked();

    void on_board_7_10_clicked();

    void on_board_7_11_clicked();

    void on_board_7_12_clicked();

    void on_board_7_13_clicked();

    void on_board_8_4_clicked();

    void on_board_8_5_clicked();

    void on_board_8_6_clicked();

    void on_board_8_7_clicked();

    void on_board_8_8_clicked();

    void on_board_8_9_clicked();

    void on_board_8_10_clicked();

    void on_board_8_11_clicked();

    void on_board_8_12_clicked();

    void on_board_9_3_clicked();

    void on_board_9_4_clicked();

    void on_board_9_5_clicked();

    void on_board_9_6_clicked();

    void on_board_9_7_clicked();

    void on_board_9_8_clicked();

    void on_board_9_9_clicked();

    void on_board_9_10_clicked();

    void on_board_9_11_clicked();

    void on_board_9_12_clicked();

    void on_board_10_2_clicked();

    void on_board_10_3_clicked();

    void on_board_10_4_clicked();

    void on_board_10_5_clicked();

    void on_board_10_6_clicked();

    void on_board_10_7_clicked();

    void on_board_10_8_clicked();

    void on_board_10_9_clicked();

    void on_board_10_10_clicked();

    void on_board_10_11_clicked();

    void on_board_10_12_clicked();

    void on_board_11_1_clicked();

    void on_board_11_2_clicked();

    void on_board_11_3_clicked();

    void on_board_11_4_clicked();

    void on_board_11_5_clicked();

    void on_board_11_6_clicked();

    void on_board_11_7_clicked();

    void on_board_11_8_clicked();

    void on_board_11_9_clicked();

    void on_board_11_10_clicked();

    void on_board_11_11_clicked();

    void on_board_11_12_clicked();

    void on_board_12_0_clicked();

    void on_board_12_1_clicked();

    void on_board_12_2_clicked();

    void on_board_12_3_clicked();

    void on_board_12_4_clicked();

    void on_board_12_5_clicked();

    void on_board_12_6_clicked();

    void on_board_12_7_clicked();

    void on_board_12_8_clicked();

    void on_board_12_9_clicked();

    void on_board_12_10_clicked();

    void on_board_12_11_clicked();

    void on_board_12_12_clicked();

    void on_board_13_4_clicked();

    void on_board_13_5_clicked();

    void on_board_13_6_clicked();

    void on_board_13_7_clicked();

    void on_board_14_4_clicked();

    void on_board_14_5_clicked();

    void on_board_14_6_clicked();

    void on_board_15_4_clicked();

    void on_board_15_5_clicked();

    void on_board_16_4_clicked();

    void on_button_regret_clicked();

    void on_button_archive_clicked();

    void on_over_clicked();

private:
    Ui::board *ui;
    QPixmap pixmap;
    QPoint imagePos;
    QSize imageSize;
    QPushButton *firstClickedButton = nullptr;
};

#endif // board_H
