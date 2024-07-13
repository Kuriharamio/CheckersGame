#ifndef CHESS_H
#define CHESS_H

#include <QDataStream>
#include <QFile>

// 定义棋子颜色的枚举类型
enum Color {
    NONE,       // 空格，没有棋子
    ORANGE,     // 橙色棋子
    PURPLE,     // 紫色棋子
    YELLOW,     // 黄色棋子
    RED,        // 红色棋子
    BLUE,       // 蓝色棋子
    GREEN       // 绿色棋子
};

// 棋盘格子类
class Chess {

public:

    explicit Chess();
    ~Chess();
    bool setRaw(int r);
    bool setCol(int c);
    // 设置格子颜色
    void setColor(Color c);
    // 获取行号
    int getRaw();
    // 获取列号
    int getCol();
    // 获取颜色
    Color getColor();
    bool getUp();
    void setUp(bool up);

    friend QDataStream &operator<<(QDataStream &out, const Chess &chess);
    friend QDataStream &operator>>(QDataStream &in, Chess &chess);


private:
    int raw;       // 行号
    int col;       // 列号
    Color color;   // 颜色
    bool Up;
};




#endif // CHESS_H
