//
//  Hole.cpp
//  ItoToshi
//
//  Created by Mihyaeru on H27/05/24.
//
//

#include "Hole.h"

USING_NS_CC;

Hole::Hole(cocos2d::Node *parent)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->size  = Size(10, this->makeHeight());
    this->point = Vec2(visibleSize.width - 10, this->makeY(this->size.height));

    this->node = DrawNode::create();
    parent->addChild(this->node);
}

Hole::~Hole()
{
    this->node->removeFromParent();
}

void Hole::update(float delta)
{
    this->point.x += this->velocity;
    Vec2 destPoint = this->point + Vec2(this->size.width, this->size.height);

    this->node->clear();
    this->node->drawRect(this->point, destPoint, Color4F(1, 1, 1, 1));
}

bool Hole::collisePoint(cocos2d::Vec2 point)
{
    float minX = this->point.x;
    float maxX = minX + this->size.width;
    float minY = this->point.y;
    float maxY = minY + this->size.height;

    if (point.x > minX && point.x < maxX && (point.y < minY || point.y > maxY)) return true;
    return false;
}

cocos2d::Vec2 Hole::getPoint()
{
    return this->point + Vec2(10, 0); // 嘘つく
}

float Hole::makeHeight()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.height / 16;
}

float Hole::makeY(float height)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int max = visibleSize.height - height*2;
    return (arc4random() % max) + height;
}
