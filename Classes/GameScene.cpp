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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初期値
    this->playerPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // プレイヤーの位置を表示するnode
    this->drawNode = DrawNode::create();
    this->addChild(this->drawNode);

    // タッチイベントであれする
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *t, Event *e) -> bool {
        this->direction = 1;
        return true;
    };
    listener->onTouchEnded     = [=](Touch *t, Event *e) { this->direction = -1; };
    listener->onTouchCancelled = [=](Touch *t, Event *e) { this->direction = -1; };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    this->velocity      += this->acceleration * this->direction;
    this->playerPoint.y += this->velocity;

    this->drawNode->clear();
    this->drawNode->drawPoint(this->playerPoint, 30, Color4F(1, 1, 1, 1));
}
