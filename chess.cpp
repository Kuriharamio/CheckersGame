#include "chess.h"

Chess::Chess()
{

    raw = 0;          // 行号默认为0
    col = 0;          // 列号默认为0
    color = NONE;     // 颜色默认为NONE

}

Chess::~Chess()
{
}

QDataStream &operator<<(QDataStream &out, const Chess &chess) {
    out << chess.raw << chess.col << static_cast<int>(chess.color) << chess.Up;
    return out;
}

QDataStream &operator>>(QDataStream &in, Chess &chess) {
    int color;
    in >> chess.raw >> chess.col >> color >> chess.Up;
    chess.color = static_cast<Color>(color);
    return in;
}

bool Chess::setRaw(int r) {
    if (r >= 0 && r <= 16) {
        raw = r; // 设置行号
        return true;
    }
    return false;
}

bool Chess::setCol(int c) {
    if (c >= 0 && c <= 16) {
        col = c; // 设置列号
        return true;
    }
    return false;
}

// 设置格子颜色
void Chess::setColor(Color c) {
    color = c; // 设置格子颜色
}

// 获取行号
int Chess::getRaw() {
    return raw; // 返回行号
}

// 获取列号
int Chess::getCol() {
    return col; // 返回列号
}

// 获取颜色
Color Chess::getColor() {
    return color; // 返回颜色
}

bool Chess::getUp(){
    return Up;
}

void Chess::setUp(bool up){
    Up = up;
}

