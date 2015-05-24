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

    this->drawNode = DrawNode::create();
    this->addChild(this->drawNode);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    this->drawNode->clear();
    this->drawNode->drawSegment(Point(10, 10), Point(100, 100), 10.0, Color4F(1, 1, 1, 1));
}
