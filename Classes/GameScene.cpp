//
//  GameScene.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/23.
//
//

#include "GameScene.h"

USING_NS_CC;

static const std::string createHoleTimerKey = "createHoleTimerKey";

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

    // タッチイベントをplayerに通知する設定
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *t, Event *e) -> bool {
        if (this->player == nullptr) return false;
        this->player->onTouchBegan();
        return true;
    };
    listener->onTouchEnded     = [=](Touch *t, Event *e) { this->player->onTouchEnded(); };
    listener->onTouchCancelled = [=](Touch *t, Event *e) { this->player->onTouchEnded(); };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // ゲームオーバーを表示するためのラベル
    this->gameOverLabel = Label::createWithTTF("GameOver!!!", "fonts/Marker Felt.ttf", 24);
    this->gameOverLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->gameOverLabel->setVisible(false);
    this->addChild(gameOverLabel);

    // 開始ボタン
    this->startButton = MenuItemFont::create("start", [=](Ref *sender) { this->start(); });
    auto menu = Menu::create(startButton, nullptr);
    menu->setPosition(this->gameOverLabel->getPosition() + Vec2(0, -50));
    this->addChild(menu);

    this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
    switch (this->state) {
        case GameState::init:
            break;
        case GameState::playing:
            this->updatePlaying(delta);
            break;
        case GameState::gameOver:
            break;
    }
}

void GameScene::updatePlaying(float delta)
{
    // 座標変換君を更新
    Coordinate::getInstance()->update(delta);

    // 要素の位置を更新
    this->player->update(delta);
    for (auto hole : this->holes) {
        hole->update(delta);
    }

    // 画面外判定
    if (!this->isInScreen(this->player->getPoint())) {
        this->gameOver();
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
            this->gameOver();
        }
    }
}

bool GameScene::isInScreen(cocos2d::Vec2 logicalPoint)
{
    Size s = Director::getInstance()->getVisibleSize();
    auto p = Coordinate::getInstance()->logical2physical(logicalPoint);

    if (p.x < 0 || p.x > s.width)  return false;
    if (p.y < 0 || p.y > s.height) return false;
    return true;
}

void GameScene::start()
{
    this->player = std::shared_ptr<Player>(new Player(this));
    this->holes.clear();

    this->gameOverLabel->setVisible(false);
    this->startButton->setVisible(false);

    // 3秒毎に穴を作る
    this->schedule([=](float delta) {
        this->holes.push_back(std::make_shared<Hole>(this));
    }, 3, createHoleTimerKey);

    Coordinate::getInstance()->reset();

    this->state = GameState::playing;
}

void GameScene::gameOver()
{
    this->gameOverLabel->setVisible(true);
    this->startButton->setVisible(true);

    this->unschedule(createHoleTimerKey);
    this->state = GameState::gameOver;
}
