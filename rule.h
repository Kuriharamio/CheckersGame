#ifndef RULE_H
#define RULE_H

#include <QWidget>
#include <QPushButton>

#include "chess.h"
#include "user.h"
#include "winner.h"

extern Chess chessBoard[17][17];

extern QList<User> users;
extern QList<User> players;
extern QList<User> winners;

enum MoveType {
    // NONE: 表示没有移动或跳跃，通常用于初始状态或无效操作
    STOP,

    // MOVE: 表示普通的移动操作，不涉及跳跃
    MOVE,

    // JUMP: 表示跳跃操作，可能越过其他棋子
    JUMP,

    // BOTH: 表示既可以移动也可以跳跃的操作
    BOTH
};

class Rule
{
public:
    Rule();

    void JumpFinished();
    bool CanJumpOnly(Chess ChessBoard[17][17],int raw_start, int col_start, int raw_end, int col_end);
    User* getCurrentPlayer();
    void GetWinner(void);
    MoveType CanJump(Chess ChessBoard[17][17],int raw_start, int col_start, int raw_end, int col_end);
    bool IfInChessBoard(Chess chess);
    bool HasPiece(Chess chess);
    bool HasPiece(Chess ChessBoard[17][17],int raw, int col);
    int Judge(Chess ChessBoard[17][17],QPushButton *button1,QPushButton *button2);
    int JudgeAgain(Chess ChessBoard[17][17],QPushButton *button);
    int NextJudge(Chess ChessBoard[17][17],QPushButton *button1,QPushButton *button2);
    bool CanJumpAgain(Chess ChessBoard[17][17],int raw, int col);
    bool CanNextJump(Chess ChessBoard[17][17],int raw_start, int col_start, int raw_end, int col_end);
    void NextPlayer(User *currentplayer);

    bool IfInColorZone(int raw, int col,Color color);
    bool IfInBlankZone(int raw, int col);
    bool IfInOppoColorZone(int raw, int col,Color color);
    bool IfInRedZone(int raw, int col);
    bool IfInBlueZone(int raw, int col);
    bool IfInGreenZone(int raw, int col);
    bool IfInPurpleZone(int raw, int col);
    bool IfInYellowZone(int raw, int col);
    bool IfInOrangeZone(int raw, int col);
};

#endif // RULE_H
