//
//  GameScene.h
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/23.
//
//

#ifndef __ItoToshi__GameScene__
#define __ItoToshi__GameScene__

#include <memory>
#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
private:
    std::shared_ptr<Player> player;
    void update(float delta);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__ItoToshi__GameScene__) */
