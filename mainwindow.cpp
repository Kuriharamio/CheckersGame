#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    ui_mainwindow->setupUi(this);
    setWindowTitle("跳棋游戏");
    QString lastBackground = settings.value("Menu_Background_Path").toString();
    QString StyleSheet = (QString("background-image: url(%1)；").arg(lastBackground));
    if (!lastBackground.isEmpty()) {
        ui_mainwindow->label->setStyleSheet(StyleSheet);
    }

    connect(ui_mainwindow->action,&QAction::triggered, this, &MainWindow::on_PVP_clicked);
    connect(ui_mainwindow->action_3,&QAction::triggered, this, &MainWindow::on_PVE_clicked);
    connect(ui_mainwindow->actionExit,&QAction::triggered, this, &MainWindow::on_Exit_clicked);
    connect(ui_mainwindow->actionON_2,&QAction::triggered, this, &MainWindow::on_bgm_on_clicked);
    connect(ui_mainwindow->actionOFF_2,&QAction::triggered, this, &MainWindow::on_bgm_off_clicked);
    connect(ui_mainwindow->actionON_3,&QAction::triggered, this, &MainWindow::on_effect_on_clicked);
    connect(ui_mainwindow->actionOFF_3,&QAction::triggered, this, &MainWindow::on_effect_off_clicked);
    connect(ui_mainwindow->actionOpen_Settings,&QAction::triggered, this, &MainWindow::on_Setting_clicked);
    connect(ui_mainwindow->actionOpen_Help,&QAction::triggered, this, &MainWindow::on_Help_clicked);
    connect(ui_mainwindow->actionSave,&QAction::triggered, this, &MainWindow::on_button_archive_clicked);
    connect(ui_mainwindow->actionLoad,&QAction::triggered, this, &MainWindow::on_button_Load_clicked);
}

MainWindow::~MainWindow()
{
    delete ui_mainwindow;
}


void MainWindow::on_Setting_clicked()
{
    SettingWidget *settingwidget = new SettingWidget(this);
    settingwidget->move(0,33);
    settingwidget->show();
}

void MainWindow::on_Help_clicked()
{
    Help *help = new Help(this);
    help->move(0,33);
    help->show();

}


void MainWindow::on_Exit_clicked()
{
    this->close();
}



void MainWindow::on_Start_Game_clicked()
{
    Mode_Selection *mode_selection = new Mode_Selection(this);
    mode_selection->move(0,33);
    mode_selection->show();
}

void MainWindow::on_PVP_clicked(){
    Select_player_num *dialog_2 = new Select_player_num(this);
    dialog_2->move(0,33);
    dialog_2->show();

}
void MainWindow::on_PVE_clicked(){
    settings.setValue("human_num",0);
    settings.setValue("computer_num",0);
    settings.setValue("computer_difficulty","NONE");
    settings.setValue("PVE_select_finished",false);

    Select_PVE *dialog_1 = new Select_PVE(this);
    dialog_1->move(0,33);
    dialog_1->show();
}


void MainWindow::on_effect_on_clicked()
{
    settings.setValue("effect","on");
}

void MainWindow::on_effect_off_clicked()
{
    settings.setValue("effect","off");
}

void MainWindow::on_bgm_on_clicked()
{
    settings.setValue("bgm","on");
    player_bgm->loops();
    player_bgm->play();
}

void MainWindow::on_bgm_off_clicked()
{

    settings.setValue("bgm","off");
    player_bgm->pause();


}
void MainWindow::on_button_Load_clicked(){
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
void MainWindow::on_button_archive_clicked(){
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save Chess Board",
        QDir::homePath(),
        "Chess Board Files (*.chessboard)"
        );

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error！";
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_7);

    out << settings.value("computer_difficulty").toString();

    out << players << winners;


    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 17; ++j) {
            out << chessBoard[i][j];
        }
    }

    file.close();
}
