//
//  Player.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#include "Player.h"
#include "Coordinate.h"

USING_NS_CC;

Player::Player(cocos2d::Node *parent)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初期値
    this->point    = Vec2(visibleSize.width / 4, visibleSize.height / 2);
//    this->point    = Vec2(0, visibleSize.height / 2);
    this->velocity = Vec2(5, 0);

    // プレイヤーの位置を表示するnode
    this->node = DrawNode::create();
    parent->addChild(this->node);
}

Player::~Player()
{
    this->node->removeFromParent();
}

void Player::update(float delta)
{
    auto c = Coordinate::getInstance();

    this->velocity.y += this->acceleration * this->direction;
    this->point      += this->velocity;

    this->prevPoints.push_back(this->point);
    if (this->prevPoints.size() > 100) this->prevPoints.pop_front();
    int i = 0;
    for (auto p : this->prevPoints) {
        this->raw_points[i++] = c->logical2physical(p);
    }

    this->node->clear();
    this->node->drawPoly(this->raw_points, (unsigned)this->prevPoints.size(), false, Color4F(1, 1, 1, 1));
}

void Player::onTouchBegan()
{
    this->direction = 1;
}

void Player::onTouchEnded()
{
    this->direction = -1;
}

cocos2d::Vec2 Player::getPoint()
{
    return this->point;
}
