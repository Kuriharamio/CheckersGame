#include "rule.h"

Rule::Rule() {

}

bool Rule::CanJumpOnly(Chess ChessBoard[17][17],int raw_start, int col_start, int raw_end, int col_end)
{
    //检查参数是否有效
    if (raw_start < 0 || raw_start >16 || col_start < 0 || col_start >16 ||
        raw_end < 0 || raw_end >16 || col_end < 0 || col_end >16) {
        return false;
    }
    //检查参数是否有效
    if (!IfInChessBoard(ChessBoard[raw_start][col_start]))
    {
        return false;
    }
    //检查参数是否有效
    if (!IfInChessBoard(ChessBoard[raw_end][col_end]))
    {
        return false;
    }

    // 检查终点处是否有棋子
    if (HasPiece(ChessBoard[raw_end][col_end]))
    {
        return false;
    }

    // 检查是否可以进行水平或垂直的两个格子跳动
    if (raw_start == raw_end && std::abs(col_start - col_end) == 2 ||
        col_start == col_end && std::abs(raw_start - raw_end) == 2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return false;//无法跳跃
        }
        else
        {
            return true; //可以跳跃
        }

    }

    // 检查是否可以进行对角线的两个格子跳动
    if ((raw_start - raw_end) == -2 && (col_start - col_end) == 2 ||
        (raw_start - raw_end) == 2 && (col_start - col_end) == -2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return false;//无法跳跃
        }
        else
        {
            return true;
        }
    }

    //输出移动类型
    return false;

}

bool Rule::IfInRedZone(int raw, int col)
{
    if (raw >= 0 && raw <= 3 && col >= 9 && col <= 12)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Rule::IfInBlankZone(int raw, int col)
{

    if (raw >= 0 && raw <= 3 && col >= 9 && col <= 12)
    {
        return false;
    }

    if(raw >= 13 && raw <= 16 && col >= 4 && col <= 7)
    {
        return false;
    }
    if(raw >= 4 && raw <= 7 && col >= 4 && col <= 11 - raw)
    {
        return false;
    }
    if (raw >= 9 && raw <= 12 && col >= 21 - raw && col <= 12)
    {
        return false;
    }

    if(raw >= 9 && raw <= 12 && col >= 0 && col <= 3)
    {
        return false;
    }
    if(raw >= 4 && raw <= 7 && col >= 13 && col <= 16)
    {
        return false;
    }
    return true;
}

bool Rule::IfInColorZone(int raw, int col,Color color){
    switch(color){
    case RED:
        if (raw >= 0 && raw <= 3 && col >= 9 && col <= 12)
        {
            return true;
        }
        else
        {
            return false;
        }
    case GREEN:
        if (raw >= 13 && raw <= 16 && col >= 4 && col <= 7)
        {
            return true;
        }
        else
        {
            return false;
        }
    case PURPLE:
        if (raw >= 4 && raw <= 7 && col >= 4 && col <= 11 - raw)
        {
            return true;
        }
        else
        {
            return false;
        }
    case YELLOW:
        if (raw >= 9 && raw <= 12 && col >= 21 - raw && col <= 12)
        {
            return true;
        }
        else
        {
            return false;
        }
    case BLUE:
        if (raw >= 9 && raw <= 12 && col >= 0 && col <= 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    case ORANGE:
        if (raw >= 4 && raw <= 7 && col >= 13 && col <= 16)
        {
            return true;
        }
        else
        {
            return false;
        }
    default:
        return 0;
    }
}

bool Rule::IfInOppoColorZone(int raw, int col,Color color){
    switch(color){
    case RED:
        if (raw >= 13 && raw <= 16 && col >= 4 && col <= 7)
        {
            return true;
        }
        else
        {
            return false;
        }
    case GREEN:
        if (raw >= 0 && raw <= 3 && col >= 9 && col <= 12)
        {
            return true;
        }
        else
        {
            return false;
        }
    case PURPLE:
        if (raw >= 9 && raw <= 12 && col >= 21 - raw && col <= 12)
        {
            return true;
        }
        else
        {
            return false;
        }
    case YELLOW:
        if (raw >= 4 && raw <= 7 && col >= 4 && col <= 11 - raw)
        {
            return true;
        }
        else
        {
            return false;
        }

    case BLUE:
        if (raw >= 4 && raw <= 7 && col >= 13 && col <= 16)
        {
            return true;
        }
        else
        {
            return false;
        }
    case ORANGE:
        if (raw >= 9 && raw <= 12 && col >= 0 && col <= 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    default:
        return 0;
    }
}

bool Rule::IfInGreenZone(int raw, int col)
{

    if (raw >= 13 && raw <= 16 && col >= 4 && col <= 7)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rule::IfInPurpleZone(int raw, int col)
{
    if (raw >= 4 && raw <= 7 && col >= 4 && col <= 11 - raw)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rule::IfInYellowZone(int raw, int col)
{
    if (raw >= 9 && raw <= 12 && col >= 21 - raw && col <= 12)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rule::IfInBlueZone(int raw, int col)
{
    if (raw >= 9 && raw <= 12 && col >= 0 && col <= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Rule::IfInOrangeZone(int raw, int col)
{
    if (raw >= 4 && raw <= 7 && col >= 13 && col <= 16)
    {
        return true;
    }
    else
    {
        return false;
    }
}


MoveType Rule::CanJump(Chess ChessBoard[17][17],int raw_start, int col_start, int raw_end, int col_end)
{
    //检查参数是否有效
    if(raw_start < 0 || raw_start >16 || col_start < 0 || col_start >16 ||
        raw_end < 0 || raw_end >16 || col_end < 0 || col_end >16) {
        return STOP;
    }
    //检查参数是否有效
    if(!IfInChessBoard(ChessBoard[raw_start][col_start]))
    {
        return STOP;
    }
    //检查参数是否有效
    if(!IfInChessBoard(ChessBoard[raw_end][col_end]))
    {
        return STOP;
    }

    //检查起始处是否有棋子
    if (!HasPiece( ChessBoard[raw_start][col_start]))
    {
        return STOP;
    }
    // 检查终点处是否有棋子
    if (HasPiece(ChessBoard[raw_end][col_end]))
    {
        return STOP;
    }
    // 检查是否可以进行水平或垂直的单格移动
    if (raw_start == raw_end && std::abs(col_start - col_end) == 1 ||
        col_start == col_end && std::abs(raw_start - raw_end) == 1) {
        return MOVE; //可以移动
    }

    // 检查是否可以进行对角线单格移动
    if ((raw_start - raw_end) == -1 && (col_start - col_end) == 1 ||
        (raw_start - raw_end) == 1 && (col_start - col_end) == -1) {
        return MOVE;//可以移动
    }

    // 检查是否可以进行水平或垂直的两个格子跳动
    if (raw_start == raw_end && std::abs(col_start - col_end) == 2 ||
        col_start == col_end && std::abs(raw_start - raw_end) == 2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return STOP;//无法跳跃
        }
        else
        {
            return JUMP; //可以跳跃
        }

    }

    // 检查是否可以进行对角线的两个格子跳动
    if ((raw_start - raw_end) == -2 && (col_start - col_end) == 2 ||
        (raw_start - raw_end) == 2 && (col_start - col_end) == -2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return STOP;;//无法跳跃
        }
        else
        {
            return JUMP;
        }
    }

    //输出移动类型
    return STOP;
}


int Rule::Judge(Chess ChessBoard[17][17],QPushButton *button1,QPushButton *button2)
{
    QString objectName1 = button1->objectName();
    QStringList parts1 = objectName1.split('_');
    int x1 = parts1.at(1).toInt();
    int y1 = parts1.at(2).toInt();
    QString objectName2 = button2->objectName();
    QStringList parts2 = objectName2.split('_');
    int x2 = parts2.at(1).toInt();
    int y2 = parts2.at(2).toInt();
    MoveType flag = CanJump(ChessBoard,x1,y1,x2,y2);

    return flag;
}

int Rule::NextJudge(Chess ChessBoard[17][17],QPushButton *button1,QPushButton *button2)
{
    QString objectName1 = button1->objectName();
    QStringList parts1 = objectName1.split('_');
    int x1 = parts1.at(1).toInt();
    int y1 = parts1.at(2).toInt();
    QString objectName2 = button2->objectName();
    QStringList parts2 = objectName2.split('_');
    int x2 = parts2.at(1).toInt();
    int y2 = parts2.at(2).toInt();
    bool flag = CanNextJump(ChessBoard,x1,y1,x2,y2);

    return flag;
}

int Rule::JudgeAgain(Chess ChessBoard[17][17],QPushButton *button)
{

    QString objectName = button->objectName();
    QStringList parts = objectName.split('_');
    int x2 = parts.at(1).toInt();
    int y2 = parts.at(2).toInt();
    bool flag = CanJumpAgain(ChessBoard,x2,y2);
    return flag;
}

bool Rule::CanNextJump(Chess ChessBoard[17][17], int raw_start, int col_start, int raw_end, int col_end)
{
    // 检查起点是否在棋盘范围内
    if (!IfInChessBoard(ChessBoard[raw_start][col_start]))
    {
        //return false;
    }

    // 检查起点处是否有棋子
    if (!HasPiece(ChessBoard[raw_start][col_start]))
    {
        return false;
    }

    // 检查终点是否在棋盘范围内
    if (!IfInChessBoard(ChessBoard[raw_end][col_end]))
    {
        //return false;
    }

    // 检查终点处是否有棋子
    if (HasPiece(ChessBoard[raw_end][col_end]))
    {
        return false;
    }

    // 检查是否可以进行水平或垂直的两个格子跳动
    if (raw_start == raw_end && std::abs(col_start - col_end) == 2 ||
        col_start == col_end && std::abs(raw_start - raw_end) == 2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return false;
        }
        else
        {
            return true;
        }

    }

    // 检查是否可以进行对角线的两个格子跳动
    if ((raw_start - raw_end) == -2 && (col_start - col_end) == 2 ||
        (raw_start - raw_end) == 2 && (col_start - col_end) == -2) {
        if (ChessBoard[(raw_start + raw_end) / 2][(col_start + col_end) / 2].getColor() == NONE)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // 如果以上条件都不满足，则不能移动
    return false;
}


// 判断棋子是否可以再次移动，即检查棋子当前位置的周围两格内是否有空格可供跳跃
bool Rule::CanJumpAgain(Chess ChessBoard[17][17],int raw, int col)
{
    // 检查棋子右侧一格有棋子且右侧两格为空的情况
    if (HasPiece(ChessBoard[raw][col + 1]) && IfInChessBoard(ChessBoard[raw][col + 2]) && !HasPiece(ChessBoard[raw][col + 2]))
    {
        return true;
    }
    // 检查棋子左侧一格有棋子且左侧两格为空的情况
    if (HasPiece(ChessBoard[raw][col - 1]) && IfInChessBoard(ChessBoard[raw][col - 2]) && !HasPiece(ChessBoard[raw][col - 2]))
    {
        return true;
    }
    // 检查棋子下方一格有棋子且上方两格为空的情况
    if (HasPiece(ChessBoard[raw + 1][col]) && IfInChessBoard(ChessBoard[raw + 2][col]) && !HasPiece(ChessBoard[raw + 2][col]))
    {
        return true;
    }
    // 检查棋子上方一格有棋子且下方两格为空的情况
    if (HasPiece(ChessBoard[raw - 1][col]) && IfInChessBoard(ChessBoard[raw - 2][col]) && !HasPiece(ChessBoard[raw - 2][col]))
    {
        return true;
    }
    // 检查棋子右下方一格有棋子且右上方两格为空的情况
    if (HasPiece(ChessBoard[raw - 1][col + 1]) && IfInChessBoard(ChessBoard[raw - 2][col + 2]) && !HasPiece(ChessBoard[raw - 2][col + 2]))
    {
        return true;
    }
    // 检查棋子左上方一格有棋子且左下方两格为空的情况
    if (HasPiece(ChessBoard[raw + 1][col - 1]) && IfInChessBoard(ChessBoard[raw + 2][col - 2]) && !HasPiece(ChessBoard[raw + 2][col - 2]))
    {
        return true;
    }

    // 如果以上所有情况都不满足，说明棋子无法再次移动
    return false;


}

// 判断棋盘是否在有效范围内
bool Rule::IfInChessBoard(Chess chess)
{
    if (chess.getRaw() >= 0 && chess.getRaw() <= 3)
    // 获取棋子的列坐标
    {
        // 判断列坐标是否在该行的有效范围内
        if (chess.getCol() >= 12 - chess.getRaw() && chess.getCol() <= 12)
            return true;// 如果在范围内，返回true

        else
            return false;// 否则返回false
    }
    // 检查行坐标是否在第二个有效区间内

    else if (chess.getRaw() >= 13 && chess.getRaw() <= 16)
    {
        // 判断列坐标是否在该行的有效范围内
        if (chess.getCol() >= 4 && chess.getCol() <= 20 - chess.getRaw())
            return true;// 如果在范围内，返回true
        else
            return false;// 否则返回false
    }

    // 检查行坐标是否在第3个有效区间内

    else if (chess.getRaw() >= 4 && chess.getRaw() <= 8)
    {
        // 判断列坐标是否在该行的有效范围内
        if (chess.getCol() >= 4 && chess.getCol() <= 20 - chess.getRaw())
            return true;// 如果在范围内，返回true
        else
            return false;// 否则返回false
    }

    // 检查行坐标是否在第4个有效区间内
    else if (chess.getRaw() >= 9 && chess.getRaw() <= 12)
    {
        // 判断列坐标是否在该行的有效范围内
        if (chess.getCol() >= 12 - chess.getRaw() && chess.getCol() <= 12)
            return true;// 如果在范围内，返回true
        else
            return false;// 否则返回false
    }

    return false;
}


// 检查给定位置是否有棋子
bool Rule::HasPiece(Chess chess)
{
    if (IfInChessBoard(chess)) {
        if (chess.getColor() == NONE) {
            return false;
        }
        return true;
    }
    return false;
}

// 检查棋盘上指定位置是否有棋子
bool Rule::HasPiece(Chess ChessBoard[17][17], int raw, int col)
{
    // 首先检查指定位置是否在棋盘的有效范围内
    if (IfInChessBoard(ChessBoard[raw][col]))

    {
        // 如果位置有效，再检查该位置的棋子颜色是否为 NONE
        if (ChessBoard[raw][col].getColor() == NONE) {
            return false;  //没有棋子
        }
        return true; //有棋子
    }

    return false;

}

void Rule::NextPlayer(User *currentplayer)
{
    currentplayer->setIsTurn(false);   //更改玩家的 isturn 为 false
    currentplayer->setOperated(false); //更改玩家的 Operated 为 false

    bool Allturn = true;
    for(User &player : players){        //更改下一个编号的玩家的 isturn 为 true
        if(player.getNum() > (currentplayer->getNum() )){
            player.setIsTurn(true);
            Allturn = false;
            break;
        }
    }
    if(Allturn)
    {
        players[0].setIsTurn(true);
    }
    qDebug() << "nextplayer";
}

void Rule::GetWinner(void)
{
    QString win_color = "NONE";
    bool FlagORANGE = settings.value("orange").toBool();
    bool FlagBLUE = settings.value("blue").toBool();
    bool FlagGREEN = settings.value("green").toBool();
    bool FlagRED = settings.value("red").toBool();
    bool FlagYELLOW = settings.value("yellow").toBool();
    bool FlagPURPLE = settings.value("purple").toBool();

    for (int i = 0; i < 4 && FlagGREEN; i++) {
        for (int j = 12 - i; j < 13 && FlagGREEN; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != GREEN)
            {
                FlagGREEN = false; // 设置标志为真，下一次迭代将退出循环
            }
        }
    }
    if (FlagGREEN)
    {
        win_color =  "green";  //返回绿色胜利
        settings.setValue("green",false);
    }

    for (int i = 13; i < 17 && FlagRED; i++) {
        for (int j = 4; j < 21 - i && FlagRED; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != RED)
            {
                FlagRED = false;  // 设置标志为真，下一次迭代将退出循环

            }
        }
    }
    if (FlagRED)
    {
        win_color =  "red";  //返回红色胜利
        settings.setValue("red",false);
    }


    for (int i = 4; i < 8 && FlagYELLOW; i++) {
        for (int j = 4; j < 12 - i && FlagYELLOW; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != YELLOW)
            {
                FlagYELLOW = false;  // 设置标志为真，下一次迭代将退出循环

            }
        }
    }
    if (FlagYELLOW)
    {
        win_color =  "yellow";  //返回黄色胜利
        settings.setValue("yellow",false);
    }


    for (int i = 9; i < 13 && FlagPURPLE; i++) {
        for (int j = 21 - i; j < 13 && FlagPURPLE; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != PURPLE)
            {
                FlagPURPLE = false;  // 设置标志为真，下一次迭代将退出循环

            }
        }
    }
    if (FlagPURPLE)
    {
        win_color =  "purple";  //返回紫色胜利
        settings.setValue("purple",false);
    }


    for (int i = 4; i < 8 && FlagBLUE; i++) {
        for (int j = 13; j < 21 - i && FlagBLUE; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != BLUE)
            {
                FlagBLUE = false;  // 设置标志为真，下一次迭代将退出循环

            }
        }
    }
    if (FlagBLUE)
    {
        win_color =  "blue";  //返回蓝色胜利
        settings.setValue("blue",false);
    }


    for (int i = 9; i < 13 && FlagORANGE; i++) {
        for (int j = 12 - i; j < 4 && FlagORANGE; j++) {
            //遍历棋盘上的一部分棋子
            if (chessBoard[i][j].getColor() != ORANGE)
            {
                FlagORANGE = false;  // 设置标志为真，下一次迭代将退出循环

            }
        }
    }
    if (FlagORANGE)
    {
        win_color =  "orange";  //返回橙色胜利
        settings.setValue("orange",false);
    }


    for(User &player : players){
        if(player.getColor() == win_color){
            winners.append(player);
            player.setRank(winners.size());
            winners[player.getRank()-1] = player;
            players.removeOne(player);
            break;
        }
    }


    if(players.isEmpty()&&!settings.value("have_showed").toBool()){
        settings.setValue("have_showed",true);
        Winner *winner = new Winner();
        winner->ShowWinner(winners, winner);
    }
/*
    for (int i = 16; i>=0; i--) {
        QString rowString;
        for (int j = 0; j < 17; j++) {
            //if(ChessBoard[i][j].getColor())
                rowString += QChar((chessBoard[i][j].getColor()+48));
        }
        qDebug() << rowString ;
    }*/
    for(User &winner: winners){
        qDebug() << winner.getUsername() << winner.getColor();
    }

}

User* Rule::getCurrentPlayer(void)
{
    User* currentplayer = nullptr;
    for(User &player : players){
        if(player.getIsTurn()){
            currentplayer = &player;
            break;
        }
    }
    if(!currentplayer)
        return nullptr;
    else
        return currentplayer;
}

void Rule::JumpFinished(){

}



