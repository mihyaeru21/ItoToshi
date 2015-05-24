//
//  Hole.h
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#ifndef __ItoToshi__Hole__
#define __ItoToshi__Hole__

#include "cocos2d.h"

class Hole
{
private:
    cocos2d::Vec2 point;
    cocos2d::Size size;
    cocos2d::DrawNode *node;
    float makeHeight();
    float makeY(float height);

public:
    Hole(cocos2d::Node *parent);
    ~Hole();
    void update(float delta);
    bool collisePoint(cocos2d::Vec2 point);
    cocos2d::Vec2 getPoint();
};

#endif /* defined(__ItoToshi__Hole__) */
