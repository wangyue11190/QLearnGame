#include <iostream>
#include <fstream>
#include "src/GameBoard.h"
#include <time.h>
#include "src/GameStatus.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <stdio.h>
using namespace j2apps::com::ninegame;
using namespace std;
using namespace boost;
void SelectRandomPoint(Point &inputPoint, int lenX, int lenY){
    srand( (unsigned)time( NULL ) );
    int x = rand() % lenX;
    int y = rand() % lenY;
    inputPoint.setX(x);
    inputPoint.setY(y);
}

map<string,float> loadMat(string file_path){
    std::ifstream fin;
    map<string, float>matMap;
    fin.open(file_path);
    string line;
    int num = 0;
    while(std::getline(fin,line)){
        vector<string> zuhe;
        boost::split(zuhe, line,boost::is_any_of("\t"));
        if(zuhe.size()==2){
            matMap.insert(map<string,float>::value_type(zuhe[0],atof(zuhe[1].c_str())));
        }
        zuhe.clear();
    }
    fin.close();
    return matMap;
}

map<string, string> loadStatus(string file_path){
    map<string, string> statusMap;
    ifstream fin;
    fin.open(file_path);
    string line;
    while(getline(fin,line)){
        vector<string> zuhe;
        boost::split(zuhe, line,boost::is_any_of("\t"));
        if(zuhe.size()==4){
            statusMap.insert(map<string,string>::value_type(zuhe[0],zuhe[1]));//key 是0_0 value 0
        }
    }
    return statusMap;
};
string createComputerFirstPath(const vector<Point> &xPointVec, const vector<Point> &yPointVec){
    string path = "";
    for(int index=0; index<xPointVec.size(); index++)
    {
        path += to_string(yPointVec[index].getX()) + "_" + to_string(yPointVec[index].getY()) + ";" + to_string(xPointVec[index].getX()) + "_" + to_string(xPointVec[index].getY());
        if(index !=xPointVec.size()-1){
            path += ";";
        }
    }
    return path;
}
bool checkOppoWin(string path, const map<string, float> &matMap, const map<string,string> &statusMap, vector<Point>&totalPoint){
    string pathStatusId="";
    map<string, string>::const_iterator iter = statusMap.find(path);
    if(iter != statusMap.end()){
        pathStatusId = iter->second;
    }else{
        return 0;
    }
    for(int index=0; index<totalPoint.size(); index++){
        string oppoPath = path + ";" + to_string(totalPoint[index].getX()) + "_" + to_string(totalPoint[index].getY());
        string newPathStatusId="";
        map<string, string>::const_iterator iter = statusMap.find(oppoPath);
        if(iter != statusMap.end()){
            newPathStatusId = iter->second;
        }else{
            continue;
        }
        map<string, float>::const_iterator iterScore = matMap.find(pathStatusId + "_" + newPathStatusId);
        if(iterScore != matMap.end() && iterScore->second==1.0f){
            return 1;
        }
    }
    return 0;
}
void findMaxScoreCandi(Point &pointY, string exsitPath, const map<string, float>&matMap, const map<string, string> &statusMap, \
        const GameBoard*gameBoard){
        //搜寻最大得分 如果最大得分为100直接返回,如果最大得分不为100且对手一步之内不能赢
        map<string, string>::const_iterator iter = statusMap.find(exsitPath);
        cout<<"exsting_path"<<exsitPath<<endl;
        string exsitPathStatusId;
        if(iter != statusMap.end()){
             exsitPathStatusId= iter->second;
        }
        else{
            cout<<"wrong path";
            return;
        }
        vector<Point> totalPoint =  gameBoard->getTotalPoint();
        float maxProba = -1; //最大概率
        for(int index=0; index<totalPoint.size(); index++){
            string newPath = exsitPath + ";" + to_string(totalPoint[index].getX()) + "_" + to_string(totalPoint[index].getY());
            string newPathStatusId="";
            map<string, string>::const_iterator iter = statusMap.find(newPath);
            if(iter != statusMap.end()){
                newPathStatusId = iter->second;
            }else{
                continue;
            }
            map<string, float>::const_iterator iterScore = matMap.find(exsitPathStatusId + "_" + newPathStatusId);
            if(iterScore != matMap.end() && iterScore->second>maxProba){
                if(checkOppoWin(newPath, matMap, statusMap, totalPoint)){
                    continue;
                }
                maxProba = iterScore->second;
                pointY.setX(totalPoint[index].getX());
                pointY.setY(totalPoint[index].getY());
            }

        }

        totalPoint.clear();

}

void computerQLearn(Point &pointY, const GameBoard *gameBoard, const map<string, float>matMap, \
                const map<string, string>statustMap){
    if(gameBoard->getXPointVec().size() == 0 && gameBoard->getYPointVec().size()==0){
        SelectRandomPoint(pointY, gameBoard->getWideRange(), gameBoard->getHighRange());//第一步随机
    }
    else{
        string existPath = createComputerFirstPath(gameBoard->getXPointVec(), gameBoard->getYPointVec());
        findMaxScoreCandi(pointY, existPath, matMap, statustMap, gameBoard);

    }

}
void gameInit(){
    int playerOneX;
    int playerOneY;
    int playerTwoX;
    int playerTwoY;

    map<string,float> matMap=loadMat("/Users/yue.wang/ClionProjects/NineColumGame/conf/mat_1.txt");
    map<string,string> statusMap = loadStatus("/Users/yue.wang/ClionProjects/NineColumGame/conf/status.txt");
    srand( (unsigned)time( NULL ) );
    //int side = rand()%2;
    int continueOrNot = 1;
    while(continueOrNot) {
        GameBoard *gameBoard = new GameBoard();
        int side = 0;
        if (side == 0) {
            cout << "computer first input" << endl;

        } else {
            cout << "player first input" << endl;

        }

        while (true) {
            if (side >= 1) {
                gameBoard->displayGameBoard();
            }
            while (side >= 1) {
                cout << "please input a point";
                cout << "x";
                cin >> playerOneX;
                cout << "y";
                cin >> playerOneY;
                Point point = Point(playerOneX, playerOneY);
                if (gameBoard->validPoint(point)) {
                    gameBoard->loadPoint(point, 1);
                    break;
                }
                else {
                    cout << "invalid input, please input a valid point and point not exist" << endl;
                }
            }
            int status = gameBoard->decideWhichWins();
            if (status == xWin) {
                cout << "player win" << endl;
                break;
            } else if (status == Tequal) {
                cout << "equal" << endl;
                break;
            }
            gameBoard->displayGameBoard();
            while (side >= 0) {
                Point pointY;
                //SelectRandomPoint(pointY, gameBoard->getWideRange(), gameBoard->getHighRange());

                computerQLearn(pointY, gameBoard, matMap, statusMap);
                if (gameBoard->validPoint(pointY)) {
                    gameBoard->loadPoint(pointY, 2);
                    cout << "computerinput:" << pointY.getX() << ":" << pointY.getY() << endl;
                    break;
                } else {
                    cout << "invalid input, please input a valid point and point not exist" << endl;
                    cout << "point" << pointY.getX() << "::" << pointY.getY() << endl;
                    SelectRandomPoint(pointY, gameBoard->getWideRange(), gameBoard->getHighRange());
                }
            }
            status = gameBoard->decideWhichWins();
            if (status == yWin) {
                cout << "computer win" << endl;
                if(gameBoard != nullptr){delete gameBoard;}
                break;
            } else if (status == Tequal) {
                cout << "equal" << endl;
                if(gameBoard != nullptr ){delete  gameBoard;}
                break;
            }
            side++;
        }
        cout<<"continue or Not"<<endl;
        cin>>continueOrNot;

    }
}
int main() {
    gameInit();
    //map<string,float> tmpMap = loadMat("/Users/yue.wang/ClionProjects/NineColumGame/conf/mat_1.txt");
    //map<string,string> tmpMap = loadStatus("/Users/yue.wang/ClionProjects/NineColumGame/conf/status.txt");
    //cout<<tmpMap.size()<<endl;
    return 0;
}