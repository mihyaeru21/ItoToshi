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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

    // ゲームオーバーを表示するためのラベル
    this->gameOverLabel = Label::createWithTTF("GameOver!!!", "fonts/Marker Felt.ttf", 24);
    gameOverLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    gameOverLabel->setVisible(false);  // 隠しておく
    this->addChild(gameOverLabel);

    // 3秒毎に穴を作る
    this->schedule([=](float delta) {
        this->holes.push_back(std::make_shared<Hole>(this));
    }, 3, "hoge");

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    // 要素の位置を更新
    this->player->update(delta);
    for (auto hole : this->holes) {
        hole->update(delta);
    }

    // 画面外判定
    if (!this->isInScreen(this->player->getPoint())) {
        this->gameOverLabel->setVisible(true);
        this->unscheduleUpdate();
    }
    auto iter = this->holes.begin();
    while (iter != this->holes.end()) {
        auto hole = *iter;
        if (!this->isInScreen(hole->getPoint())) {
            this->holes.erase(iter);
        }
        else {
            iter++;
        }
    }

    // 当たり判定
    for (auto hole : this->holes) {
        if (hole->collisePoint(this->player->getPoint())) {
            this->gameOverLabel->setVisible(true);
            this->unscheduleUpdate();
        }
    }
}

bool GameScene::isInScreen(cocos2d::Vec2 p)
{
    Size s = Director::getInstance()->getVisibleSize();

    if (p.x < 0 || p.x > s.width)  return false;
    if (p.y < 0 || p.y > s.height) return false;
    return true;
}
