//
//  Coordinate.h
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#ifndef __ItoToshi__Coordinate__
#define __ItoToshi__Coordinate__

#include "cocos2d.h"

class Coordinate
{
private:
    cocos2d::Vec2 offset;
    Coordinate(){ this->reset(); }
    Coordinate(const Coordinate &other){}
    Coordinate &operator=(const Coordinate &other){}
public:
    static Coordinate *getInstance();
    void update(float delta);
    void reset();
    cocos2d::Vec2 logical2physical(cocos2d::Vec2 point);
    cocos2d::Vec2 physical2logical(cocos2d::Vec2 point);
};

#endif /* defined(__ItoToshi__Coordinate__) */
