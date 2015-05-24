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

    this->size  = Size(20, visibleSize.height);
    this->point = Vec2(visibleSize.width, 0);

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
    this->node->drawSolidRect(this->point, destPoint, Color4F(1, 1, 1, 1));
}

bool Hole::collisePoint(cocos2d::Vec2 point)
{
    return false;
}

cocos2d::Vec2 Hole::getPoint()
{
    return this->point;
}
