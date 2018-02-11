//
// Created by yue.wang on 18/1/24.
//

#include "Point.h"

namespace j2apps{ namespace  com { namespace ninegame{

            int Point::getY() const {
                return y;
            }

            int Point::getX() const {
                return x;
            }

            void Point::setX(int x) {
                Point::x = x;
            }

            void Point::setY(int y) {
                Point::y = y;
            }
            Point::Point(int x, int y) {
                this->x = x;
                this->y = y;
            }
            bool Point::operator<(const Point &input) const {
                if(this->x < input.x){
                    return true;
                }
                else if (this->x == input.x){
                    if(this->y < input.y){
                        return true;
                    }
                    else{
                        return false;
                    }
                }else{
                    return false;
                }
            }
            bool Point::comp(const Point &one, const Point &two) {
                if(one.x < two.x){
                    return true;
                }
                else if (one.x == two.x){
                    if(one.y < two.y){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                };
            }
        }

    }
}
