//
// Created by yue.wang on 18/1/24.
//

#ifndef NINECOLUMGAME_GAMEBOARD_H
#define NINECOLUMGAME_GAMEBOARD_H

#include <vector>
#include <map>
#include <string>
#include "Point.h"
using namespace std;
using namespace j2apps::com::ninegame;
namespace j2apps{namespace com{ namespace ninegame{
            class GameBoard {
                private:
                    map<Point,int > exsitPoint;
                    vector<Point> totalPoint;
            public:
                const vector<Point> &getTotalPoint() const;

            private:
                map<string,int> winPoint;
                    const int wideRange = 3;
                    const int highRange = 3;
                    const int totalPointLen = 9;
                    vector<Point> xPointVec;//player
                    vector<Point> yPointVec;//computer
                    vector<Point> winVec; //装载赢棋的组合。
                public:
                    bool validPoint(Point inputPoint); //判断棋子是否有效(越界或者已经下了)
                    int decideWhichWins();
                    int checkZuheWins(vector<Point> &inputVec);
                    GameBoard();
                    void init();
                    void loadPoint(Point inputPoint, int playerID);
                    const int getWideRange() const;
                    const int getHighRange() const;
                    void displayGameBoard();
                    const vector<Point> &getXPointVec() const;
                    const vector<Point> &getYPointVec() const;
            };
        }}}



#endif //NINECOLUMGAME_GAMEBOARD_H
