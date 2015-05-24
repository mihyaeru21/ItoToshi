//
//  Coordinate.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#include "Coordinate.h"

Coordinate *Coordinate::getInstance() {
    static Coordinate instance;
    return &instance;
}

void Coordinate::update(float delta)
{
    this->offset += cocos2d::Vec2(5, 0);
}

void Coordinate::reset()
{
    this->offset = cocos2d::Vec2(0, 0);
}

cocos2d::Vec2 Coordinate::logical2physical(cocos2d::Vec2 point)
{
    return point - this->offset;
}

cocos2d::Vec2 Coordinate::physical2logical(cocos2d::Vec2 point)
{
    return point + this->offset;
}
