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
#include <vector>
#include "cocos2d.h"
#include "Player.h"
#include "Hole.h"

class GameScene : public cocos2d::Layer
{
private:
    bool isInScreen(cocos2d::Vec2);
    std::shared_ptr<Player> player;
    void update(float delta);
    cocos2d::Label *gameOverLabel;
    std::vector<std::shared_ptr<Hole>> holes;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__ItoToshi__GameScene__) */
