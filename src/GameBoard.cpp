//
// Created by yue.wang on 18/1/24.
//

#include "GameBoard.h"
#include "GameStatus.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
using namespace j2apps::com::ninegame;
namespace j2apps{namespace  com{namespace  ninegame{
            GameBoard::GameBoard() {
                init();
            }
            void GameBoard::init() {
                totalPoint.push_back(Point(0,0));
                totalPoint.push_back(Point(0,1));
                totalPoint.push_back(Point(0,2));
                totalPoint.push_back(Point(1,0));
                totalPoint.push_back(Point(1,1));
                totalPoint.push_back(Point(1,2));
                totalPoint.push_back(Point(2,0));
                totalPoint.push_back(Point(2,1));
                totalPoint.push_back(Point(2,2)); //初始化棋盘所有的点

                winPoint["0_0_0_1_0_2"] = 1;
                winPoint["1_0_1_1_1_2"] = 1;
                winPoint["2_0_2_1_2_2"] = 1;
                winPoint["0_0_1_0_2_0"] = 1;
                winPoint["0_1_1_1_2_1"] = 1;
                winPoint["0_2_1_2_2_2"] = 1;
                winPoint["0_0_1_1_2_2"] = 1;
                winPoint["0_2_1_1_2_0"] = 1;

            }

            int GameBoard::decideWhichWins() {
                    //0 是和棋 -1是没有人赢 1是x赢 2是y赢
                if(xPointVec.size()<=2 && yPointVec.size()<=2){
                    return noWin;
                }
                if(xPointVec.size()>=3){
                    if(checkZuheWins(xPointVec)==1){return xWin;};
                }
                if(yPointVec.size()>=3){
                    if(checkZuheWins(yPointVec) == 1){return yWin;}
                }
                if(xPointVec.size() + yPointVec.size() == totalPointLen){
                    return Tequal;
                }
                return noWin;

            }
            int GameBoard::checkZuheWins(vector<Point> &inputVec) {
                for(int indexjj=0; indexjj < inputVec.size(); indexjj ++){
                    cout<<inputVec[indexjj].getX()<<":"<<inputVec[indexjj].getY();
                }
                cout<<"former ends"<<endl;
                sort(inputVec.begin(),inputVec.end(),Point::comp);
                for(int indexjj=0; indexjj < inputVec.size(); indexjj ++){
                    cout<<inputVec[indexjj].getX()<<":"<<inputVec[indexjj].getY();
                }
                cout<<"later ends"<<endl;
                int inputVecSize = inputVec.size();
                if(inputVecSize<3)return 0;
                for(int indexFirst = 0; indexFirst< inputVecSize; indexFirst++){
                    for(int indexSecond = indexFirst + 1; indexSecond< inputVecSize; indexSecond++){
                        for(int indexThird = indexSecond + 1; indexThird< inputVecSize; indexThird++){
                            string zuhe = to_string(inputVec[indexFirst].getX()) + "_" + to_string(inputVec[indexFirst].getY()) + \
                            "_" + to_string(inputVec[indexSecond].getX()) + "_" +  to_string(inputVec[indexSecond].getY()) + \
                             "_" + to_string(inputVec[indexThird].getX()) + "_" + to_string(inputVec[indexThird].getY());
                            if (winPoint.find(zuhe) != winPoint.end()){
                                winVec.push_back(inputVec[indexFirst]);
                                winVec.push_back(inputVec[indexSecond]);
                                winVec.push_back(inputVec[indexThird]);
                                return 1;
                            }
                        }
                    }
                }
                return 0;
            }
            bool GameBoard::validPoint(Point inputPoint) {
                if(inputPoint.getX()>=this->wideRange || inputPoint.getY()>=this->highRange){
                    return false;
                }
                if(exsitPoint.find(inputPoint) != exsitPoint.end()){
                    return false;
                }
                return true;
            }

            void GameBoard::loadPoint(Point inputPoint, int playerID) {
                exsitPoint[inputPoint] = playerID;
                if(playerID == 1){
                    xPointVec.push_back(inputPoint);
                }
                else{
                    yPointVec.push_back(inputPoint);
                }
            }

            const int GameBoard::getWideRange() const {
                return wideRange;
            }

            const int GameBoard::getHighRange() const {
                return highRange;
            }

            void GameBoard::displayGameBoard() {
                int  signal = 0;
                cout<<"game board as follows:"<<endl;
                for(int index = 0; index < totalPoint.size(); index++){
                    Point tmpPoint = totalPoint[index];
                    if(exsitPoint.find(tmpPoint) != exsitPoint.end()){
                        signal = exsitPoint[tmpPoint];
                    }else{
                        signal = 0;
                    }
                    cout<<to_string(signal)<<" ";
                    if((index+1)%3==0){
                        cout<<endl;
                    }

                }
                cout<<"game board input finish"<<endl;
            }

            const vector<Point> &GameBoard::getXPointVec() const {
                return xPointVec;
            }

            const vector<Point> &GameBoard::getYPointVec() const {
                return yPointVec;
            }

            const vector<Point> &GameBoard::getTotalPoint() const {
                return totalPoint;
            }

        }}}