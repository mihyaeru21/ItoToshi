//
//  GameScene.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/23.
//
//

#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    this->player = std::shared_ptr<Player>(new Player(this));

    // タッチイベントをplayerに通知する
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *t, Event *e) -> bool {
        this->player->onTouchBegan();
        return true;
    };
    listener->onTouchEnded     = [=](Touch *t, Event *e) { this->player->onTouchEnded(); };
    listener->onTouchCancelled = [=](Touch *t, Event *e) { this->player->onTouchEnded(); };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    this->player->update(delta);
}
