#include "board.h"
#include "ui_board.h"


board::board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::board)
{
    ui->setupUi(this);
    if (!lastBackground.isEmpty()) {
        ui->label_10->setStyleSheet(StyleSheet);
    }else{
        ui->label_10->setStyleSheet("background-image: url(:/images/assets/board_background.jpg);");
    }

    QTimer *timer = new QTimer;
    QTimer *timer_stamina = new QTimer;


    connect(timer, &QTimer::timeout, this, &board::countDown);
    timer->start(1000);

    connect(timer_stamina, &QTimer::timeout, this, &board::staminaUp);
    timer_stamina->start(300*1000);

    if(!archive){
        human_num = settings.value("human_num").toInt();
        computer_num = settings.value("computer_num").toInt();
        players_num = human_num+computer_num;

        Init(players_num,chessBoard);
        Init(players_num,chessBoard_record);

        //高亮轮次
        users[0].setIsTurn(true);
        QLabel* name_label_next = findChild<QLabel*>(QString("player_%1_name").arg(users[0].getNum()));
        name_label_next->setStyleSheet("background-color: rgb(0, 255, 255);");


        winners.clear();
        for(User &user:users){
            settings.setValue(user.getColor(),true);
        }

    }else{

        //高亮轮次
        for(User &player : players){
            if(player.getIsTurn()){
                QLabel* name_label_next = findChild<QLabel*>(QString("player_%1_name").arg(player.getNum()));
                name_label_next->setStyleSheet("background-color: rgb(0, 255, 255);");
                break;
            }
        }

        for(User &player:players){
            if(player.getRank()){
                settings.setValue(player.getColor(),false);
            }else{
                settings.setValue(player.getColor(),true);
            }
        }

        players_num = players.size();
        human_num = computer_num = 0;
        for(User &player:players){
            if(player.getType()=="human")
                human_num++;
            if(player.getType()=="computer")
                computer_num++;
        }

        if(winners.count()>0){
            ui->over->setStyleSheet("QPushButton {border-image: url(:/images/assets/button_none.png);}QPushButton:hover {border-image: url(:/images/assets/button_hover.png);}QPushButton:pressed {border-image: url(:/images/assets/button_press.png);}");
            ui->over->setText("结算");
        }else{
            ui->over->setStyleSheet("border-image: url(:/images/assets/transparent.png);");
            ui->over->setText("");
        }

    }

    SettingMaching(players_num);
    updateBoard(chessBoard);
    audioOutput->setVolume(1000);
    player1->setAudioOutput(audioOutput);

    if(computer_num||!settings.value("CountDown").toBool()){
        ui->lcdNumber->hide();
    }

}

board::~board()
{
    delete ui;
}

void board::countDown(void){
    if(!computer_num&&settings.value("CountDown").toBool()){
        int x_last;
        int y_last;
        if(firstClickedButton){
            QString objectName_last = firstClickedButton->objectName();
            QStringList parts_last = objectName_last.split('_');
            x_last = parts_last.at(1).toInt();
            y_last = parts_last.at(2).toInt();
        }

        if(!count_down){
            count_down=settings.value("CountDown_set").toInt();
            if(firstClickedButton){
                moveUpDown(firstClickedButton,10);
                chessBoard[x_last][y_last].setUp(false);
                firstClickedButton = nullptr;       //firstclicked 置空
            }

            currentPlayer = rule.getCurrentPlayer();
            rule.NextPlayer(currentPlayer);
            currentPlayer->setRegretted(false);
            nextPlayer = rule.getCurrentPlayer();
            if(nextPlayer&&currentPlayer){
                QLabel* name_label_now = findChild<QLabel*>(QString("player_%1_name").arg(currentPlayer->getNum()));
                name_label_now->setStyleSheet("");
                //高亮当前玩家
                if(nextPlayer->getType() == "human"){
                    QLabel* name_label_next = findChild<QLabel*>(QString("player_%1_name").arg(nextPlayer->getNum()));
                    name_label_next->setStyleSheet("background-color: rgb(0, 255, 255);");
                }
            }

        }
        if(settings.value("CountDown").toBool()){
            ui->lcdNumber->display(count_down);
            count_down--;
        }else{
            ui->lcdNumber->hide();

        }

    }else{
        ui->lcdNumber->hide();
    }
}

void board::staminaUp(void){
    for(User &player : players){
        if(player.getStamina()<4)
            player.setStamina(player.getStamina()+1);
    }
    for(int i = 0; i<players_num; i++){
        QLabel* stamina_label = findChild<QLabel*>(QString("player_%1_stamina").arg(players[i].getNum()));

        if(stamina_label){
            if(players[i].getType() == "human"){
                stamina_label->setStyleSheet("background-image: url(:/images/assets/Stamina1.png);");
                stamina_label->resize(50*players[i].getStamina(),41);
            }
        }
    }
}

void board::SettingMaching(int n)
{
    settings.setValue("have_showed",false);

    if(!archive){
        //将用户加入玩家队列
        QString color[6];
        color[0] = "red";

        if(players_num == 2)
        {
            color[1] = "green";
        }else if(players_num == 3){
            color[1] = "blue";
            color[2] = "yellow";
        }else if(players_num == 4){
            color[1] = "blue";
            color[2] = "green";
            color[3] = "orange";
        }else if(players_num == 5){
            color[1] = "purple";
            color[2] = "blue";
            color[3] = "green";
            color[4] = "orange";
        }else if(players_num == 6){
            color[1] = "purple";
            color[2] = "blue";
            color[3] = "green";
            color[4] = "yellow";
            color[5] = "orange";
        }
        for(int i = 0;i<players_num;i++)
        {
            for(User &user : users){
                if(user.getColor() == color[i]){
                    players.append(user);
                    break;
                }
            }
        }

        //设置玩家信息
        for(int i = 0;i<human_num;i++){
            players[i].setType("human");
        }

        for(int i = human_num; i<players_num; i++){
            players[i] = User(players[i].getNum(),QString("电脑%1").arg(i-human_num+1), players[i].getRank(),players[i].getIsTurn(), players[i].getOperated(),players[i].getColor(),"computer");
        }
    }

    //删除未参与游戏的用户的图片和名字
    for(int i = 0; i<6 ; i++){
        bool participate = false;
        for(User &player : players){
            if(player.getNum() == (users[i].getNum())){
                participate = true;
                break;
            }
        }
        if(!participate){
            QLabel* image_label = findChild<QLabel*>(QString("player_%1_image").arg(users[i].getNum()));
            QLabel* name_label = findChild<QLabel*>(QString("player_%1_name").arg(users[i].getNum()));
            QLabel* stamina_label = findChild<QLabel*>(QString("player_%1_stamina").arg(users[i].getNum()));
            if(name_label&&image_label&&stamina_label){
                name_label->clear();
                image_label->setStyleSheet("");
                stamina_label->setStyleSheet("");
            }
        }
    }

    //设置参与游戏的用户的图片和名字
    for(int i = 0; i < players_num; i++) {
        QLabel* image_label = findChild<QLabel*>(QString("player_%1_image").arg(players[i].getNum()));
        QLabel* name_label = findChild<QLabel*>(QString("player_%1_name").arg(players[i].getNum()));
        QLabel* stamina_label = findChild<QLabel*>(QString("player_%1_stamina").arg(players[i].getNum()));

        //给人加体力条
        if(stamina_label){
             if(players[i].getType() == "human"){
                stamina_label->setStyleSheet("background-image: url(:/images/assets/Stamina1.png);");
                stamina_label->resize(50*players[i].getStamina(),41);
             }else{
                 stamina_label->setStyleSheet("");
             }
        }

        if (name_label) {
            if(players[i].getType() == "human"){
                QString name_record_name = QString("%1_name").arg(players[i].getColor());
                QString last_name = settings.value(name_record_name).toString();
                if (!last_name.isEmpty()) {
                    name_label->setText(last_name);
                    players[i].setUsername(last_name);
                } else {
                    name_label->setText(QString("Player%1").arg(players[i].getNum()));
                    players[i].setUsername(QString("Player%1").arg(players[i].getNum()));
                }
            }else if(players[i].getType() == "computer"){
                name_label->setText(players[i].getUsername());
            }
        }

        if (image_label) {
            if(players[i].getType() == "human"){
                QString image_record_name = QString("%1_Image_Path").arg(players[i].getColor());
                QString last_image = settings.value(image_record_name).toString();
                if (!last_image.isEmpty()) {
                    QString stylesheet = QString("border-image: url(%1);").arg(last_image);
                    image_label->setStyleSheet(stylesheet);
                } else {
                    image_label->setStyleSheet(QString("border-image: url(:/images/assets/%1.jpg);").arg(players[i].getNum()));
                }
            }else if(players[i].getType() == "computer"){
                 image_label->setStyleSheet("border-image: url(:/images/assets/robot.png);");
            }
        }
    }

}

// 初始化棋盘函数
void board::Init(int n,Chess chessboard[17][17])
{
    //初始化玩家列表
    players.clear();

    //第一次初始化，全部设为NONE
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            chessboard[i][j].setRaw(i);
            chessboard[i][j].setCol(j);
            chessboard[i][j].setColor(Color::NONE);
            chessboard[i][j].setUp(false);
        }
    }
    if (n <= 1 || n > 6) {
        return;
    }
    if (n == 3)
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 12 - i; j < 13; j++) {
                // 对每个格子设置行号、列号和颜色（默认为RED）

                chessboard[i][j].setColor(RED);
            }
        }

        for (int i = 9; i < 13; i++) {
            for (int j = 12 - i; j < 4; j++) {
                // 对每个格子设置行号、列号和颜色（默认为BLUE）

                chessboard[i][j].setColor(BLUE);
            }
        }

        for (int i = 9; i < 13; i++) {
            for (int j = 21 - i; j < 13; j++) {
                // 对每个格子设置行号、列号和颜色（默认为YELLOW）

                chessboard[i][j].setColor(YELLOW);
            }
        }
        return;
    }

    if (n>0) {
        for (int i = 0; i < 4; i++) {
            for (int j = 12 - i; j < 13; j++) {
                // 对每个格子设置行号、列号和颜色（默认为RED）

                chessboard[i][j].setColor(RED);
            }
        }

        for (int i = 13; i < 17; i++) {
            for (int j = 4; j < 21 - i; j++) {
                // 对每个格子设置行号、列号和颜色（默认为GREEN）
                chessboard[i][j].setColor(GREEN);
            }
        }

        n -= 2;
    }

    if (n > 0) {
        for (int i = 9; i < 13; i++) {
            for (int j = 12 - i; j < 4; j++) {
                // 对每个格子设置行号、列号和颜色（默认为BLUE）

                chessboard[i][j].setColor(BLUE);
            }
        }

        for (int i = 4; i < 8; i++) {
            for (int j = 13; j < 21 - i; j++) {
                // 对每个格子设置行号、列号和颜色（默认为ORANGE）

                chessboard[i][j].setColor(ORANGE);
            }

        }
        n -= 2;
    }

    if (n > 0) {
        for (int i = 4; i < 8; i++) {
            for (int j = 4; j < 12 - i; j++) {
                // 对每个格子设置行号、列号和颜色（默认为PURPLE）

                chessboard[i][j].setColor(PURPLE);
            }
        }
        n --;
    }

    if (n > 0) {
        for (int i = 9; i < 13; i++) {
            for (int j = 21 - i; j < 13; j++) {
                // 对每个格子设置行号、列号和颜色（默认为YELLOW）

                chessboard[i][j].setColor(YELLOW);
            }
        }
        n--;
    }

    return;

}

void board::copyBoard(Chess chessBoard1[17][17],Chess chessBoard2[17][17])
{
    for(int i = 0; i<17; ++i){
        for(int j = 0; j<17; ++j){
            if(rule.IfInChessBoard(chessBoard1[i][j])){
                chessBoard2[i][j] = chessBoard1[i][j];
            }
        }
    }
}

void board::updateBoard(Chess chessBoard_model[17][17])
{
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 17; ++j) {
            if (rule.IfInChessBoard(chessBoard_model[i][j])) {
                QPushButton* button = findChild<QPushButton*>(QString("board_%1_%2").arg(i).arg(j));
                QString chess_color = GetChessColor(button,chessBoard_model);
                if (button) {
                    QString styleSheet = QString("image: url(:/images/assets/%1_ball.png); border: none; background-color: transparent").arg(chess_color);
                    button->setStyleSheet(styleSheet);
                }
            }
        }
    }
}

void board::SwapChessColors(int raw_start, int col_start, int raw_end, int col_end)
{
    Color temp = chessBoard[raw_start][col_start].getColor();//定义一个临时变量，用于存储棋子的颜色

    chessBoard[raw_start][col_start].setColor(chessBoard[raw_end][col_end].getColor());//交换棋子的颜色
    chessBoard[raw_end][col_end].setColor(temp);
}

QString board::GetChessColor(QPushButton *button, Chess chessBoard_model[17][17])
{
    QString objectName_last = button->objectName();
    QStringList parts_last = objectName_last.split('_');
    int x = parts_last.at(1).toInt();
    int y = parts_last.at(2).toInt();
    Color temp = chessBoard_model[x][y].getColor();
    QString color;
    switch(temp)
    {
    case NONE:
        color = "NONE";
        break;
    case RED:
        color = "red";
        break;
    case BLUE:
        color = "blue";
        break;
    case PURPLE:
        color = "purple";
        break;
    case YELLOW:
        color = "yellow";
        break;
    case ORANGE:
        color = "orange";
        break;
    case GREEN:
        color = "green";
        break;
    }
    return color;
}

void board::moveUpDown(QPushButton *button, int pos)
{
    QString color = GetChessColor(button,chessBoard);
    if(color!="NONE")
    {
        if(pos>0)//down
        {
            if(settings.value("effect").toString() == "on"){
                player1->setSource(QUrl("qrc:/media/assets/put.mp3"));
                player1->play();
            }
            button->setStyleSheet(QString("image: url(:/images/assets/%1_ball.png);border:none;background-color:transparent").arg(color));

        }else{
            if(settings.value("effect").toString() == "on"){
                player1->setSource(QUrl("qrc:/media/assets/pick.mp3"));
                player1->play();
            }
            button->setStyleSheet(QString("image: url(:/images/assets/%1_ball_light.png);border:none;background-color:transparent").arg(color));

        }
    }
    QPoint currentPos = button->pos();
    currentPos.setY(currentPos.y()+pos);
    button->move(currentPos);
}


void board::swap(QPushButton *button1,QPushButton *button2,QString player_type)
{
    if(button1&&button2){
        if(player_type == "human"){
            swapButtonStyle(button1, button2);
            moveUpDown(button1,10);
            moveUpDown(button2,-10);
        }else if(player_type == "computer"){
            swapButtonStyle(button1, button2);
        }
    }

}

void board::swapButtonStyle(QPushButton *button1,QPushButton *button2)
{
    QString style1 = button1->styleSheet();
    QString style2 = button2->styleSheet();
    button1->setStyleSheet(style2);
    button2->setStyleSheet(style1);
}

void board::clicked(QPushButton *button)
{
    if(players.isEmpty()){
        QMessageBox::warning(nullptr, "提醒",QString("游戏已经结束啦"));
    }else{
        currentPlayer = rule.getCurrentPlayer();

        //获取上一个按钮的坐标
        int x_last=0;
        int y_last=0;
        if(firstClickedButton != nullptr)
        {
            QString objectName_last = firstClickedButton->objectName();
            QStringList parts_last = objectName_last.split('_');
            x_last = parts_last.at(1).toInt();
            y_last = parts_last.at(2).toInt();
        }
        //获取当前按钮的坐标
        QString objectName_now = button->objectName();
        QStringList parts_now = objectName_now.split('_');
        int x_now = parts_now.at(1).toInt();
        int y_now = parts_now.at(2).toInt();


        if(GetChessColor(button,chessBoard) == currentPlayer->getColor() || GetChessColor(button,chessBoard) == "NONE")
        {

            if(firstClickedButton == nullptr)       //如果是第一次点击
            {
                if(rule.HasPiece(chessBoard,x_now,y_now))        //如果不是空地
                {
                    firstClickedButton = button;    //设置 firstclicked 为当前按钮
                    regretUser = currentPlayer;
                    copyBoard(chessBoard,chessBoard_record);
                    moveUpDown(button,-10);       //棋子浮空
                }else{
                    if(settings.value("effect").toString() == "on"){
                        player1->setSource(QUrl("qrc:/media/assets/board.mp3"));
                        player1->play();
                    }
                }
            }else if(firstClickedButton == button)  //如果再次点击原来的棋子
            {
                if(!rule.IfInBlankZone(x_now,y_now)&&!rule.IfInColorZone(x_now,y_now,computer.turnStringToColor(currentPlayer->getColor()))&&!rule.IfInOppoColorZone(x_now,y_now,computer.turnStringToColor(currentPlayer->getColor()))){
                    if(settings.value("effect").toString() == "on"){
                        player1->setSource(QUrl("qrc:/media/assets/board.mp3"));
                        player1->play();
                    }
                }else{
                    moveUpDown(button, 10);           //棋子落下
                    firstClickedButton = nullptr;       //firstclicked 置空
                    count_down = settings.value("CountDown_set").toInt();
                    currentPlayer->setRegretted(false);
                    if(currentPlayer->getOperated())       //如果操作过了，说明能连跳的时候落子
                    {
                        rule.GetWinner();
                        rule.NextPlayer(currentPlayer);
                    }
                }
            }else if(firstClickedButton != button){     //如果按的是别的按钮
                Last_Step = rule.Judge(chessBoard,firstClickedButton, button);
                if(currentPlayer->getOperated())  //如果目前在进行多次跳跃
                {
                    if(Last_Step==JUMP)
                    {
                        SwapChessColors(x_last,y_last,x_now,y_now);//交换棋子颜色
                        swap(firstClickedButton,button,"human");    //交换图片
                        if(rule.JudgeAgain(chessBoard,button))              //如果能连跳
                        {
                            currentPlayer->setOperated(currentPlayer->getOperated()+1);  //更改玩家的 Operated 为 true
                            firstClickedButton = button;

                        }else{
                            currentPlayer->setOperated(0);  //更改玩家的 Operated 为 false
                            moveUpDown(button, 10);       //棋子落下
                            firstClickedButton = nullptr;       //firstclicked 置空
                            count_down = settings.value("CountDown_set").toInt();
                            currentPlayer->setRegretted(false);
                            rule.GetWinner();
                            rule.NextPlayer(currentPlayer);

                        }
                    }
                }else if(rule.Judge(chessBoard,firstClickedButton, button))   //如果能移动
                {
                    if(rule.JudgeAgain(chessBoard,button) && Last_Step==JUMP)              //如果能连跳
                    {
                        SwapChessColors(x_last,y_last,x_now,y_now);//交换棋子颜色
                        swap(firstClickedButton,button,currentPlayer->getType());    //交换图片
                        currentPlayer->setOperated(currentPlayer->getOperated()+1);  //更改玩家的 Operated 为 true
                        firstClickedButton = button;

                    }else{
                        if(!rule.IfInBlankZone(x_now,y_now)&&!rule.IfInColorZone(x_now,y_now,computer.turnStringToColor(currentPlayer->getColor()))&&!rule.IfInOppoColorZone(x_now,y_now,computer.turnStringToColor(currentPlayer->getColor()))){
                            if(settings.value("effect").toString() == "on"){
                                player1->setSource(QUrl("qrc:/media/assets/board.mp3"));
                                player1->play();
                            }
                        }else{
                            SwapChessColors(x_last,y_last,x_now,y_now);//交换棋子颜色
                            swap(firstClickedButton,button,currentPlayer->getType());    //交换图片
                            moveUpDown(button, 10);       //棋子落下
                            rule.GetWinner();
                            rule.NextPlayer(currentPlayer);
                            firstClickedButton = nullptr;       //firstclicked 置空
                            count_down = settings.value("CountDown_set").toInt();
                            currentPlayer->setRegretted(false);
                        }

                    }
                }

            }

            //设定下一位玩家
            nextPlayer = rule.getCurrentPlayer();

            if(winners.count()>0){
                ui->over->setStyleSheet("QPushButton {border-image: url(:/images/assets/button_none.png);}QPushButton:hover {border-image: url(:/images/assets/button_hover.png);}QPushButton:pressed {border-image: url(:/images/assets/button_press.png);}");
                ui->over->setText("结算");
            }else{
                ui->over->setStyleSheet("border-image: url(:/images/assets/transparent.png);");
                ui->over->setText("");
            }

            if(nextPlayer){
                //电脑走
                while(nextPlayer->getType()=="computer"){
                    bool game_over = true;
                    for(User &player : players)
                    {
                        if(player.getType()=="human"){
                            game_over = false;
                        }
                    }
                    if(game_over){
                        players.clear();
                        qDebug() << "game_over";
                        rule.NextPlayer(nextPlayer);
                        nextPlayer = rule.getCurrentPlayer();
                        break;
                    }
                    qDebug() << "turn to computer";
                    std::array<int,5> result;
                    int value_pc = 0;
                    int value_human = 0;
                    for(int i = 0; i<17; i++){
                        for(int j = 0; j<17 ; j++){
                            if(chessBoard[i][j].getColor()==computer.turnStringToColor(nextPlayer->getColor())){
                                value_pc+=computer.EvaluateBoard(i,j,chessBoard[i][j].getColor());
                            }else if(chessBoard[i][j].getColor()==RED){
                                value_human+=computer.EvaluateBoard(i,j,RED);
                            }
                        }
                    }


                    if((human_num == 1)&& computer_num==1 && value_pc<800 && value_human<500 && computer.turnStringToDifficulty(settings.value("computer_difficulty").toString())>2){

                        result = computer.FindDeeply(chessBoard,computer.turnStringToColor(nextPlayer->getColor()),RED,computer.turnStringToDifficulty(settings.value("computer_difficulty").toString()),3);

                    }else if((human_num == 1)&& computer_num==1 && value_pc<800 && value_human<500 && computer.turnStringToDifficulty(settings.value("computer_difficulty").toString())<=2){
                        result = computer.FindDeeply(chessBoard,computer.turnStringToColor(nextPlayer->getColor()),RED,computer.turnStringToDifficulty(settings.value("computer_difficulty").toString()),1);
                    }else if(human_num==1&&computer_num>1 && value_pc<800 && value_human<50 && computer.turnStringToDifficulty(settings.value("computer_difficulty").toString())>2){
                        result = computer.FindDeeply(chessBoard,computer.turnStringToColor(nextPlayer->getColor()),RED,computer.turnStringToDifficulty(settings.value("computer_difficulty").toString()),3);
                    }
                    else{
                        result = computer.ComputersMove(chessBoard,computer.turnStringToColor(nextPlayer->getColor()),computer.turnStringToDifficulty(settings.value("computer_difficulty").toString()));
                    }

                    computer.setBegin_x(result[0]);
                    computer.setBegin_y(result[1]);
                    computer.setDestin_x(result[2]);
                    computer.setDestin_y((result[3]));

                    QPushButton* beginButton = findChild<QPushButton*>(QString("board_%1_%2").arg(computer.getBegin_x()).arg(computer.getBegin_y()));
                    QPushButton* destinButton = findChild<QPushButton*>(QString("board_%1_%2").arg(computer.getDestin_x()).arg(computer.getDestin_y()));

                    SwapChessColors(computer.getBegin_x(),computer.getBegin_y(),computer.getDestin_x(),computer.getDestin_y());//交换棋子颜色
                    qDebug() << "swap";
                    swap(beginButton,destinButton,"computer");

                    rule.GetWinner();
                    rule.NextPlayer(nextPlayer);
                    nextPlayer = rule.getCurrentPlayer();

                }
                if(nextPlayer&&currentPlayer){
                    QLabel* name_label_now = findChild<QLabel*>(QString("player_%1_name").arg(currentPlayer->getNum()));
                    name_label_now->setStyleSheet("");
                    //高亮当前玩家
                    if(nextPlayer->getType() == "human"){
                        QLabel* name_label_next = findChild<QLabel*>(QString("player_%1_name").arg(nextPlayer->getNum()));
                        name_label_next->setStyleSheet("background-color: rgb(0, 255, 255);");
                    }
                }

            }

        }

    }
}


void board::on_over_clicked()
{
    if(winners.size()>0){
        Winner *winner = new Winner();
        winner->ShowWinner(winners, winner);
    }

}


void board::on_button_regret_clicked()
{
    bool have_won = false;
    if(regretUser){
        for(User &winner : winners){
            if(winner.getUsername() == regretUser->getUsername())
                have_won = true;
        }
    }
    if(have_won){
        QMessageBox::warning(nullptr, "提醒",QString("%1已经赢啦").arg(regretUser->getUsername()));
    }else{
        if(players.isEmpty()){
            QMessageBox::warning(nullptr, "提醒",QString("游戏已经结束啦"));
        }else{
            if(regretUser){
                qDebug() << regretUser->getUsername();
                if(regretUser->getRegretted()){
                    QMessageBox::warning(nullptr, "提醒",QString("%1还没下棋呢").arg(regretUser->getUsername()));
                }else{
                    if(regretUser->getStamina()>0){
                        updateBoard(chessBoard_record);
                        copyBoard(chessBoard_record,chessBoard);
                        if(nextPlayer){
                            nextPlayer->setIsTurn(false);
                            QLabel* name_label_now = findChild<QLabel*>(QString("player_%1_name").arg(nextPlayer->getNum()));
                            name_label_now->setStyleSheet("");
                        }

                        regretUser->setIsTurn(true);
                        QLabel* name_label_next = findChild<QLabel*>(QString("player_%1_name").arg(regretUser->getNum()));
                        name_label_next->setStyleSheet("background-color: rgb(0, 255, 255);");
                        regretUser->setStamina(regretUser->getStamina()-1);
                        QLabel* stamina_label = findChild<QLabel*>(QString("player_%1_stamina").arg(regretUser->getNum()));
                        stamina_label->resize(50*regretUser->getStamina(),41);
                        regretUser->setRegretted(true);

                    }else{
                        QMessageBox::warning(nullptr, "提醒",QString("%1的体力值用光了哦").arg(regretUser->getUsername()));
                    }

                }

            }

        }

    }




}

void board::on_button_archive_clicked()
{
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

void board::on_button_back_clicked()
{
    count_down=settings.value("CountDown_set").toInt();
    this->close();
}


void board::on_board_0_12_clicked()
{
    QPushButton *button = ui->board_0_12;
    clicked(button);
}


void board::on_board_1_11_clicked()
{
    QPushButton *button = ui->board_1_11;
    clicked(button);
}


void board::on_board_1_12_clicked()
{
    QPushButton *button = ui->board_1_12;
    clicked(button);
}



void board::on_board_2_10_clicked()
{
    QPushButton *button = ui->board_2_10;
    clicked(button);
}


void board::on_board_2_11_clicked()
{
    QPushButton *button = ui->board_2_11;
    clicked(button);
}




void board::on_board_2_12_clicked()
{
    QPushButton *button = ui->board_2_12;
    clicked(button);
}




void board::on_board_3_9_clicked()
{
    QPushButton *button = ui->board_3_9;
    clicked(button);
}


void board::on_board_3_10_clicked()
{
    QPushButton *button = ui->board_3_10;
    clicked(button);
}


void board::on_board_3_11_clicked()
{
    QPushButton *button = ui->board_3_11;
    clicked(button);
}


void board::on_board_3_12_clicked()
{
    QPushButton *button = ui->board_3_12;
    clicked(button);
}


void board::on_board_4_4_clicked()
{
    QPushButton *button = ui->board_4_4;
    clicked(button);
}


void board::on_board_4_5_clicked()
{
    QPushButton *button = ui->board_4_5;
    clicked(button);
}


void board::on_board_4_6_clicked()
{
    QPushButton *button = ui->board_4_6;
    clicked(button);
}


void board::on_board_4_7_clicked()
{
    QPushButton *button = ui->board_4_7;
    clicked(button);
}




void board::on_board_4_8_clicked()
{
    QPushButton *button = ui->board_4_8;
    clicked(button);
}


void board::on_board_4_9_clicked()
{
    QPushButton *button = ui->board_4_9;
    clicked(button);
}


void board::on_board_4_10_clicked()
{
    QPushButton *button = ui->board_4_10;
    clicked(button);
}

void board::on_board_4_11_clicked()
{
    QPushButton *button = ui->board_4_11;
    clicked(button);
}


void board::on_board_4_12_clicked()
{
    QPushButton *button = ui->board_4_12;
    clicked(button);
}




void board::on_board_4_13_clicked()
{
    QPushButton *button = ui->board_4_13;
    clicked(button);
}


void board::on_board_4_14_clicked()
{
    QPushButton *button = ui->board_4_14;
    clicked(button);
}




void board::on_board_4_15_clicked()
{
    QPushButton *button = ui->board_4_15;
    clicked(button);
}



void board::on_board_4_16_clicked()
{
    QPushButton *button = ui->board_4_16;
    clicked(button);
}




void board::on_board_5_4_clicked()
{
    QPushButton *button = ui->board_5_4;
    clicked(button);
}



void board::on_board_5_5_clicked()
{
    QPushButton *button = ui->board_5_5;
    clicked(button);
}


void board::on_board_5_6_clicked()
{
    QPushButton *button = ui->board_5_6;
    clicked(button);
}




void board::on_board_5_7_clicked()
{
    QPushButton *button = ui->board_5_7;
    clicked(button);
}




void board::on_board_5_8_clicked()
{
    QPushButton *button = ui->board_5_8;
    clicked(button);
}



void board::on_board_5_9_clicked()
{
    QPushButton *button = ui->board_5_9;
    clicked(button);
}


void board::on_board_5_10_clicked()
{
    QPushButton *button = ui->board_5_10;
    clicked(button);
}


void board::on_board_5_11_clicked()
{
    QPushButton *button = ui->board_5_11;
    clicked(button);
}


void board::on_board_5_12_clicked()
{
    QPushButton *button = ui->board_5_12;
    clicked(button);
}


void board::on_board_5_13_clicked()
{
    QPushButton *button = ui->board_5_13;
    clicked(button);
}


void board::on_board_5_14_clicked()
{
    QPushButton *button = ui->board_5_14;
    clicked(button);
}


void board::on_board_5_15_clicked()
{
    QPushButton *button = ui->board_5_15;
    clicked(button);
}



void board::on_board_6_4_clicked()
{
    QPushButton *button = ui->board_6_4;
    clicked(button);
}




void board::on_board_6_5_clicked()
{
    QPushButton *button = ui->board_6_5;
    clicked(button);
}



void board::on_board_6_6_clicked()
{
    QPushButton *button = ui->board_6_6;
    clicked(button);
}


void board::on_board_6_7_clicked()
{
    QPushButton *button = ui->board_6_7;
    clicked(button);
}


void board::on_board_6_8_clicked()
{
    QPushButton *button = ui->board_6_8;
    clicked(button);
}


void board::on_board_6_9_clicked()
{
    QPushButton *button = ui->board_6_9;
    clicked(button);
}


void board::on_board_6_10_clicked()
{
    QPushButton *button = ui->board_6_10;
    clicked(button);
}


void board::on_board_6_11_clicked()
{
    QPushButton *button = ui->board_6_11;
    clicked(button);
}


void board::on_board_6_12_clicked()
{
    QPushButton *button = ui->board_6_12;
    clicked(button);
}


void board::on_board_6_13_clicked()
{
    QPushButton *button = ui->board_6_13;
    clicked(button);
}



void board::on_board_6_14_clicked()
{
    QPushButton *button = ui->board_6_14;
    clicked(button);
}


void board::on_board_7_4_clicked()
{
    QPushButton *button = ui->board_7_4;
    clicked(button);
}


void board::on_board_7_5_clicked()
{
    QPushButton *button = ui->board_7_5;
    clicked(button);
}


void board::on_board_7_6_clicked()
{
    QPushButton *button = ui->board_7_6;
    clicked(button);
}


void board::on_board_7_7_clicked()
{
    QPushButton *button = ui->board_7_7;
    clicked(button);
}


void board::on_board_7_8_clicked()
{
    QPushButton *button = ui->board_7_8;
    clicked(button);
}


void board::on_board_7_9_clicked()
{
    QPushButton *button = ui->board_7_9;
    clicked(button);
}


void board::on_board_7_10_clicked()
{
    QPushButton *button = ui->board_7_10;
    clicked(button);
}


void board::on_board_7_11_clicked()
{
    QPushButton *button = ui->board_7_11;
    clicked(button);
}


void board::on_board_7_12_clicked()
{
    QPushButton *button = ui->board_7_12;
    clicked(button);
}


void board::on_board_7_13_clicked()
{
    QPushButton *button = ui->board_7_13;
    clicked(button);
}


void board::on_board_8_4_clicked()
{
    QPushButton *button = ui->board_8_4;
    clicked(button);
}


void board::on_board_8_5_clicked()
{
    QPushButton *button = ui->board_8_5;
    clicked(button);
}


void board::on_board_8_6_clicked()
{
    QPushButton *button = ui->board_8_6;
    clicked(button);
}


void board::on_board_8_7_clicked()
{
    QPushButton *button = ui->board_8_7;
    clicked(button);
}


void board::on_board_8_8_clicked()
{
    QPushButton *button = ui->board_8_8;
    clicked(button);
}


void board::on_board_8_9_clicked()
{
    QPushButton *button = ui->board_8_9;
    clicked(button);
}


void board::on_board_8_10_clicked()
{
    QPushButton *button = ui->board_8_10;
    clicked(button);
}


void board::on_board_8_11_clicked()
{
    QPushButton *button = ui->board_8_11;
    clicked(button);
}


void board::on_board_8_12_clicked()
{
    QPushButton *button = ui->board_8_12;
    clicked(button);
}


void board::on_board_9_3_clicked()
{
    QPushButton *button = ui->board_9_3;
    clicked(button);
}



void board::on_board_9_4_clicked()
{
    QPushButton *button = ui->board_9_4;
    clicked(button);
}


void board::on_board_9_5_clicked()
{
    QPushButton *button = ui->board_9_5;
    clicked(button);
}


void board::on_board_9_6_clicked()
{
    QPushButton *button = ui->board_9_6;
    clicked(button);
}


void board::on_board_9_7_clicked()
{
    QPushButton *button = ui->board_9_7;
    clicked(button);
}


void board::on_board_9_8_clicked()
{
    QPushButton *button = ui->board_9_8;
    clicked(button);
}


void board::on_board_9_9_clicked()
{
    QPushButton *button = ui->board_9_9;
    clicked(button);
}


void board::on_board_9_10_clicked()
{
    QPushButton *button = ui->board_9_10;
    clicked(button);
}


void board::on_board_9_11_clicked()
{
    QPushButton *button = ui->board_9_11;
    clicked(button);
}


void board::on_board_9_12_clicked()
{
    QPushButton *button = ui->board_9_12;
    clicked(button);
}



void board::on_board_10_2_clicked()
{
    QPushButton *button = ui->board_10_2;
    clicked(button);
}


void board::on_board_10_3_clicked()
{
    QPushButton *button = ui->board_10_3;
    clicked(button);
}


void board::on_board_10_4_clicked()
{
    QPushButton *button = ui->board_10_4;
    clicked(button);
}


void board::on_board_10_5_clicked()
{
    QPushButton *button = ui->board_10_5;
    clicked(button);
}


void board::on_board_10_6_clicked()
{
    QPushButton *button = ui->board_10_6;
    clicked(button);
}


void board::on_board_10_7_clicked()
{
    QPushButton *button = ui->board_10_7;
    clicked(button);
}


void board::on_board_10_8_clicked()
{
    QPushButton *button = ui->board_10_8;
    clicked(button);
}


void board::on_board_10_9_clicked()
{
    QPushButton *button = ui->board_10_9;
    clicked(button);
}


void board::on_board_10_10_clicked()
{
    QPushButton *button = ui->board_10_10;
    clicked(button);
}


void board::on_board_10_11_clicked()
{
    QPushButton *button = ui->board_10_11;
    clicked(button);
}


void board::on_board_10_12_clicked()
{
    QPushButton *button = ui->board_10_12;
    clicked(button);
}


void board::on_board_11_1_clicked()
{
    QPushButton *button = ui->board_11_1;
    clicked(button);
}


void board::on_board_11_2_clicked()
{
    QPushButton *button = ui->board_11_2;
    clicked(button);
}


void board::on_board_11_3_clicked()
{
    QPushButton *button = ui->board_11_3;
    clicked(button);
}


void board::on_board_11_4_clicked()
{
    QPushButton *button = ui->board_11_4;
    clicked(button);
}


void board::on_board_11_5_clicked()
{
    QPushButton *button = ui->board_11_5;
    clicked(button);
}


void board::on_board_11_6_clicked()
{
    QPushButton *button = ui->board_11_6;
    clicked(button);
}


void board::on_board_11_7_clicked()
{
    QPushButton *button = ui->board_11_7;
    clicked(button);
}


void board::on_board_11_8_clicked()
{
    QPushButton *button = ui->board_11_8;
    clicked(button);
}


void board::on_board_11_9_clicked()
{
    QPushButton *button = ui->board_11_9;
    clicked(button);
}


void board::on_board_11_10_clicked()
{
    QPushButton *button = ui->board_11_10;
    clicked(button);
}


void board::on_board_11_11_clicked()
{
    QPushButton *button = ui->board_11_11;
    clicked(button);
}


void board::on_board_11_12_clicked()
{
    QPushButton *button = ui->board_11_12;
    clicked(button);
}


void board::on_board_12_0_clicked()
{
    QPushButton *button = ui->board_12_0;
    clicked(button);
}


void board::on_board_12_1_clicked()
{
    QPushButton *button = ui->board_12_1;
    clicked(button);
}


void board::on_board_12_2_clicked()
{
    QPushButton *button = ui->board_12_2;
    clicked(button);
}


void board::on_board_12_3_clicked()
{
    QPushButton *button = ui->board_12_3;
    clicked(button);
}


void board::on_board_12_4_clicked()
{
    QPushButton *button = ui->board_12_4;
    clicked(button);
}


void board::on_board_12_5_clicked()
{
    QPushButton *button = ui->board_12_5;
    clicked(button);
}


void board::on_board_12_6_clicked()
{
    QPushButton *button = ui->board_12_6;
    clicked(button);
}


void board::on_board_12_7_clicked()
{
    QPushButton *button = ui->board_12_7;
    clicked(button);
}


void board::on_board_12_8_clicked()
{
    QPushButton *button = ui->board_12_8;
    clicked(button);
}


void board::on_board_12_9_clicked()
{
    QPushButton *button = ui->board_12_9;
    clicked(button);
}


void board::on_board_12_10_clicked()
{
    QPushButton *button = ui->board_12_10;
    clicked(button);
}


void board::on_board_12_11_clicked()
{
    QPushButton *button = ui->board_12_11;
    clicked(button);
}


void board::on_board_12_12_clicked()
{
    QPushButton *button = ui->board_12_12;
    clicked(button);
}


void board::on_board_13_4_clicked()
{
    QPushButton *button = ui->board_13_4;
    clicked(button);
}


void board::on_board_13_5_clicked()
{
    QPushButton *button = ui->board_13_5;
    clicked(button);
}


void board::on_board_13_6_clicked()
{
    QPushButton *button = ui->board_13_6;
    clicked(button);
}


void board::on_board_13_7_clicked()
{
    QPushButton *button = ui->board_13_7;
    clicked(button);
}


void board::on_board_14_4_clicked()
{
    QPushButton *button = ui->board_14_4;
    clicked(button);
}


void board::on_board_14_5_clicked()
{
    QPushButton *button = ui->board_14_5;
    clicked(button);
}


void board::on_board_14_6_clicked()
{
    QPushButton *button = ui->board_14_6;
    clicked(button);
}


void board::on_board_15_4_clicked()
{
    QPushButton *button = ui->board_15_4;
    clicked(button);
}


void board::on_board_15_5_clicked()
{
    QPushButton *button = ui->board_15_5;
    clicked(button);
}


void board::on_board_16_4_clicked()
{
    QPushButton *button = ui->board_16_4;
    clicked(button);
}







