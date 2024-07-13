#include "computer.h"

Computer::Computer() {}

int Computer::getBegin_x() const{
    return Begin_x;
}
void Computer::setBegin_x(int begin_x){
    Begin_x = begin_x;
}

int Computer::getBegin_y() const{
    return Begin_y;
}
void Computer::setBegin_y(int begin_y){
    Begin_y = begin_y;
}

int Computer::getDestin_x() const{
    return Destin_x;
}
void Computer::setDestin_x(int destin_x){
    Destin_x = destin_x;
}

int Computer::getDestin_y() const{
    return Destin_y;
}
void Computer:: setDestin_y(int destin_y){
    Destin_y = destin_y;
}

int Computer::getStatus() const{
    return Status;
}
void Computer:: setStatus(int status){
    Status = status;
}

Color Computer::turnStringToColor(QString color)
{
    if(color=="red")
        return RED;
    else if(color=="purple")
        return PURPLE;
    else if(color=="blue")
        return BLUE;
    else if(color=="green")
        return GREEN;
    else if(color=="yellow")
        return YELLOW;
    else if(color=="orange")
        return ORANGE;
    else
        return NONE;
}

int Computer::turnStringToDifficulty(QString difficulty)
{
    if(difficulty=="simple")
        return 1;
    else if(difficulty=="normal")
        return 2;
    else if(difficulty=="difficult")
        return 3;
    else if(difficulty=="master")
        return 4;
    else
        return 0;

}

std::array<int,5> Computer::FindDeeply(Chess ChessBoard[17][17], Color color_self, Color color_oppo,  int level, int depth){
    int maxdvalue = -999;
    //起点棋子的坐标位置
    int startr = 0;
    int startc = 0;

    std::array<int,5> result_self;
    std::array<int,5> result_oppo;
    std::array<int,5> final;
    std::vector<std::pair<int, int>> selectedFirstPosition = FindSelectPosition(ChessBoard, color_self);
    int visited[17][17] = {};

    Chess ChessBoard_next[17][17];


    // 使用范围for循环遍历向量(所有的统一颜色的棋子)
    for(int i = 0; i<10*level/4; i++){
        startr = selectedFirstPosition[i].first;
        startc = selectedFirstPosition[i].second;

        // 计算当前位置的评估值
        int demovalue = EvaluateBoard(startr, startc, color_self);//评估棋盘的初始位置的值

        //初始化
        for (int i = 0; i < 17; i++)
        {
            for (int j = 0; j < 17; j++)
            {
                visited[i][j] = 0;
            }
        }

        std::pair<int, int> tempPosition{ 0, 0 };//初始化
        std::vector<std::pair<int, int>> allJumpPosition;

        //遍历可以跳跃的情况 allJumpPosition存数据
        do
        {
            allJumpPosition.push_back(tempPosition);
            tempPosition = SerachMove(ChessBoard, visited, startr, startc);
        } while (allJumpPosition.size() < 2 || (allJumpPosition[allJumpPosition.size() - 1] != tempPosition) );

        for (int i = 1; i < 12; i+=2)
        {
            // 检查是否可以移动到目标位置
            if (rule.CanJump(ChessBoard, startr, startc, startr + dr[i], startc + dc[i]) == MOVE)
            {
                tempPosition.first = startr + dr[i];
                tempPosition.second = startc + dc[i];
                allJumpPosition.push_back(tempPosition);
            }
        }

        for (int i = 0; i < allJumpPosition.size(); i++)
        {
            int raw = allJumpPosition[i].first;
            int col = allJumpPosition[i].second;

            if ((raw+col) && !(startr ==raw && startc == col))//如果不是0，0且不原地
            {
                int nowdvalue = EvaluateBoard(raw, col, color_self) - demovalue;

                for(int i = 0; i<17; i++){
                    for(int j = 0;j<17;j++){
                        ChessBoard_next[i][j] = ChessBoard[i][j];
                    }
                }

                Color temp = ChessBoard_next[raw][col].getColor();//定义一个临时变量，用于存储棋子的颜色
                ChessBoard_next[raw][col].setColor(ChessBoard_next[startr][startc].getColor());//交换棋子的颜色
                ChessBoard_next[startr][startc].setColor(temp);

                for(int i = 0; i<depth; i++){
                    result_oppo = ComputersMove(ChessBoard_next,color_oppo,level);
                    nowdvalue -= result_oppo[4];

                    temp = ChessBoard_next[result_oppo[0]][result_oppo[1]].getColor();//定义一个临时变量，用于存储棋子的颜色
                    ChessBoard_next[result_oppo[0]][result_oppo[1]].setColor(ChessBoard_next[result_oppo[2]][result_oppo[3]].getColor());//交换棋子的颜色
                    ChessBoard_next[result_oppo[2]][result_oppo[3]].setColor(temp);


                    result_self = ComputersMove(ChessBoard_next,color_self,level);
                    nowdvalue += result_self[4];

                    temp = ChessBoard_next[result_self[0]][result_self[1]].getColor();//定义一个临时变量，用于存储棋子的颜色
                    ChessBoard_next[result_self[0]][result_self[1]].setColor(ChessBoard_next[result_self[2]][result_self[3]].getColor());//交换棋子的颜色
                    ChessBoard_next[result_self[2]][result_self[3]].setColor(temp);

                }



                result_oppo = ComputersMove(ChessBoard_next,color_oppo,level);
                nowdvalue -= result_oppo[4];

                if (nowdvalue > maxdvalue)
                {
                    final[0] = startr;
                    final[1] = startc;
                    final[2] = raw;
                    final[3] = col;
                    final[4] = nowdvalue;
                    maxdvalue = nowdvalue;
                }

            }

        }
    }

    qDebug() << final[4];

    return final;

}


std::array<int, 5> Computer::ComputersMove(Chess ChessBoard[17][17], Color color, int level)
{
    int maxdvalue = -999;
    //评估最大值棋子的位置
    int maxr_end = 0;
    int maxc_end = 0;

    //起点棋子的坐标位置
    int startr = 0;
    int startc = 0;

    int maxr_start = 0;
    int maxc_start = 0;

    int count = 0;

    std::array<int, 5> result = { 0 , 0 , 0 , 0 ,  0};

    std::vector<std::pair<int, int>> selectedFirstPosition = FindSelectPosition(ChessBoard, color);


    int visited[17][17] = {};


    // 使用范围for循环遍历向量(所有的统一颜色的棋子)
    for(int i = 0; i<10*level/4; i++){
        startr = selectedFirstPosition[i].first;
        startc = selectedFirstPosition[i].second;

        // 计算当前位置的评估值
        int demovalue = EvaluateBoard(startr, startc, color);//评估棋盘的初始位置的值

        //初始化
        for (int i = 0; i < 17; i++)
        {
            for (int j = 0; j < 17; j++)
            {
                visited[i][j] = 0;
            }
        }


        std::pair<int, int> tempPosition{ 0, 0 };//初始化

        std::vector<std::pair<int, int>> allJumpPosition;


        //遍历可以跳跃的情况 allJumpPosition存数据
        do
        {
            allJumpPosition.push_back(tempPosition);
            tempPosition = SerachMove(ChessBoard, visited, startr, startc);
        } while (allJumpPosition.size() < 2 || (allJumpPosition[allJumpPosition.size() - 1] != tempPosition) );

        for (int i = 1; i < 12; i+=2)
        {
            // 检查是否可以移动到目标位置
            if (rule.CanJump(ChessBoard, startr, startc, startr + dr[i], startc + dc[i]) == MOVE)
            {
                tempPosition.first = startr + dr[i];
                tempPosition.second = startc + dc[i];
                allJumpPosition.push_back(tempPosition);
            }
        }


        //遍历所有可以跳跃的位置 找最大值棋子的位置
        for (int i = 0; i < allJumpPosition.size(); i++)
        {
            int raw = allJumpPosition[i].first;
            int col = allJumpPosition[i].second;

            if ((raw+col) && !(startr ==raw && startc == col))//如果不是0，0且不原地
            {
                int nowdvalue = EvaluateBoard(raw, col, color) - demovalue;
                if (nowdvalue > maxdvalue)//如果可以，则更新最大值和对应的坐标
                {
                    maxr_start = startr;
                    maxc_start = startc;

                    maxr_end = raw;
                    maxc_end = col;

                    maxdvalue = nowdvalue;

                }
            }

        }

    }


    if (ChessBoard[maxr_end][maxc_end].getColor() != NONE)
    {
        std::array<int, 5> error ={0 , 0 , 0 , 0,0 };
        return error;

    }
    // 设置最终选择的位置
    result[0] = maxr_start;
    result[1] = maxc_start;
    result[2] = maxr_end;
    result[3] = maxc_end;
    result[4] = maxdvalue;

    // 返回最终选择的位置
    return result;
}

std::pair<int,int> Computer::SerachMove(Chess ChessBoard[17][17], int visited[17][17] , int raw , int col)
{
    int raw_n = 0;
    int col_n = 0;


    std::pair<int,int> result = std::make_pair(raw, col);

    if (!rule.CanJumpAgain(ChessBoard, raw, col))
    {
        for (int i = 0; i < 17; i++)
        {
            for (int j = 0; j < 17; j++)
            {
                if (visited[i][j] == 1)
                {
                    visited[i][j] = 0;
                }
            }
        }
        visited[raw][col] = 2;

        return result;
    }

    for (int i = 0; i < 12; i+=2)
    {

        if (rule.CanJumpOnly(ChessBoard, raw, col, raw + dr[i], col + dc[i])  &&  !visited[raw + dr[i]][col + dc[i]])
        {

            raw_n= raw + dr[i];
            col_n= col + dc[i];
            visited[raw][col] = 1;
            return SerachMove(ChessBoard,  visited, raw_n, col_n);

        }
    }
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (visited[i][j] == 1)
            {
                visited[i][j] = 0;
            }
        }
    }
    visited[raw][col] = 2;
    return result;
}

int Computer::EvaluateBoard(int raw, int col, Color color) {
    switch (color)
    {

    case GREEN:
        return RED_GREEN_VALUE[raw][16 - col];
    case RED:
        return RED_GREEN_VALUE[16 - raw][col];

    case BLUE:
        return BLUE_ORANGE_VALUE[16 - raw][col];

    case ORANGE:
        return BLUE_ORANGE_VALUE[raw][16 - col];

    case PURPLE:
        return PURPLE_YELLOW_VALUE[16 - raw][col];

    case YELLOW:
        return PURPLE_YELLOW_VALUE[raw][16 - col];
    default:
        return 0;
    }
}

std::vector<std::pair<int, int>> Computer::FindSelectPosition(Chess ChessBoard[17][17], Color color) {
    // 初始化一个向量，用于存储所有找到的指定颜色棋子的坐标
    std::vector<std::pair<int, int>> AllPositions;
    //颜色为空，返回空向量
    if (color == NONE)
        return AllPositions;

    int count = 0;
    // 开始双重循环，遍历棋盘上的每一个位置
    for (int i = 0; i < 17 && count < 10; ++i) {
        for (int j = 0; j < 17 && count < 10; ++j)
        {
            // 如果棋子位置有效，进一步检查棋子的颜色
            if (ChessBoard[i][j].getColor() == color)
            {
                // 如果棋子颜色与指定颜色相符，则记录该位置
                // emplace_back直接在向量尾部插入一个新的元素，效率高于push_back
                AllPositions.emplace_back(i, j);
                count++;
            }
        }
    }

    // 创建一个随机数生成器
    std::random_device rd;
    std::mt19937 g(rd());

    // 使用std::shuffle打乱向量
    std::shuffle(AllPositions.begin(), AllPositions.end(), g);

    // 函数结束时，返回收集到的所有指定颜色棋子的位置列表
    return AllPositions;
}
