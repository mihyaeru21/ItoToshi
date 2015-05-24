//
//  Player.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Node *parent)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 初期値
    this->point = Vec2(visibleSize.width / 4, visibleSize.height / 2);

    // プレイヤーの位置を表示するnode
    this->node = DrawNode::create();
    parent->addChild(this->node);
}

void Player::update(float delta)
{
    this->velocity      += this->acceleration * this->direction;
    this->point.y += this->velocity;

    this->node->clear();
    this->node->drawPoint(this->point, 30, Color4F(1, 1, 1, 1));
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
