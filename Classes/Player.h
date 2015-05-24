//
//  Player.h
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#ifndef __ItoToshi__Player__
#define __ItoToshi__Player__

#include "cocos2d.h"

class Player
{
private:
    cocos2d::Vec2 point;
    cocos2d::DrawNode *node;

    int direction      = -1;
    float velocity     = 0.1;
    float acceleration = 0.2;
public:
    Player(cocos2d::Node *parent);
    void update(float delta);
    void onTouchBegan();
    void onTouchEnded();
    cocos2d::Vec2 getPoint();
};

#endif /* defined(__ItoToshi__Player__) */
