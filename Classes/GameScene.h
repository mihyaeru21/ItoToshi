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
#include "Coordinate.h"

enum class GameState {
    init,
    playing,
    gameOver,
};

class GameScene : public cocos2d::Layer
{
private:
    GameState state = GameState::init;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Hole>> holes;
    cocos2d::Label *gameOverLabel;
    cocos2d::MenuItemFont *startButton;

    void start();
    void gameOver();
    void update(float delta);
    void updatePlaying(float delta);
    bool isInScreen(cocos2d::Vec2);

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__ItoToshi__GameScene__) */
