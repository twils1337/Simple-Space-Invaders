//
//  Equipment.cpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#include "Equipment.h"

Equipment::Equipment(string bod, int iD, Object_T oT,float x, float y, int hp, int dmg, bool _active, Object_T Sender)
:damage(dmg), active(_active), sender(Sender)
{
    ID = iD;
    ot = oT;
    body = Sprite::create(bod);
    body->setPosition(x,y);
    auto physicsBody = cocos2d::PhysicsBody::createBox(getBody()->getContentSize(),
                                                       cocos2d::PhysicsMaterial(0,0,0));
    physicsBody->setCollisionBitmask(ID);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setGravityEnable(false);
    if (ID == 16 || ID == 32 || ID == 64 | ID == 128)
    {
        physicsBody->setDynamic(false);
    }
    else
    {
        physicsBody->setDynamic(true);
    }
    body->setPhysicsBody(physicsBody);
    health = hp;
    damage = dmg;
}

Equipment::Equipment()
:damage(1), active(false)
{
    //body = Sprite::create("");
    //body->setPosition(0,-200);
    health = 1;
}
void Equipment::_attack()
{
}

bool Equipment::isActive()
{
    return active;
}

void Equipment::changeActive(bool status)
{
    active = status;
}

void Equipment::setHealth(int hp)
{
    health = hp;
}

Object_T Equipment::getSenderT() const
{
    return sender;
}
