//
// Created by yue.wang on 18/1/24.
//

#ifndef NINECOLUMGAME_POINT_H
#define NINECOLUMGAME_POINT_H

//九宫格游戏
namespace j2apps {namespace com{ namespace ninegame{
            class Point {
                private:
                    int x;
                    int y;
                public:
                    void setX(int x);
                    int getX() const;
                    void setY(int y);
                    int getY() const;
                    Point(int x, int y);
                    Point(){};
                    bool operator < (const Point&input) const;
                    bool static comp(const Point &one, const Point &two);
            };
        }}}



#endif //NINECOLUMGAME_POINT_H
