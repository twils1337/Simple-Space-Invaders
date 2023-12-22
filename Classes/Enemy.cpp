//
//  Enemy.cpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#include "Enemy.h"

Enemy::Enemy(int iD, Object_T oT, Enemy_T et, float x, float y, string bod, string attk, int hp, int dmg, bool ded)
:Type(et), body_fn(bod), attack_fn(attk), attack_dmg(dmg), dead(ded)
{
    ID = iD;
    ot = oT;
    body=Sprite::create(body_fn);
    body->setPosition(x,y);
    auto physicsBody = cocos2d::PhysicsBody::createBox(getBody()->getContentSize(),
                                                       cocos2d::PhysicsMaterial(0,1,0));
    physicsBody->setCollisionBitmask(ID);
    physicsBody->setCategoryBitmask(1);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(true);
    body->setPhysicsBody(physicsBody);
    health = hp;
}

Enemy::Enemy()
:Type(Enemy_T::A), body_fn(""), attack_dmg(0), dead(false)
{
    health = 0;
}

bool Enemy::isDead() const
{
    return dead;
}

Enemy& Enemy::operator=(const Enemy &rhs)
{
    ID = rhs.ID;
    body_fn= rhs.body_fn;
    this->attack_dmg = rhs.attack_dmg;
    this->dead = rhs.dead;
    this->body = Sprite::create(body_fn);
    this->body->setPosition(rhs.body->getPosition().x, rhs.body->getPosition().y);
    this->health = rhs.health;
    return *this;
}

Equipment Enemy::_attack()
{
    cocos2d::Vec2 pos = body->getPosition();
    Equipment enemy_wep(attack_fn, 13, Object_T::equipT, pos.x,
                        pos.y - getBody()->getContentSize().height,
                        1, 1, true, Object_T::enemyT);
    enemy_wep.getBody()->getPhysicsBody()->setVelocity(cocos2d::Vec2(0,-80.0f));
    return enemy_wep;
}

string Enemy::getBodyFn() const
{
    return body_fn;
}

void Enemy::setBodyFn(string new_fn)
{
    body_fn = new_fn;
}

Enemy_T Enemy::getType() const
{
    return Type;
}

void Enemy::setHealth(int hp)
{
    health = hp;
}

void Enemy::setID(int iD)
{
    ID = iD;
}

int Enemy::getID() const
{
    return ID;
}

void Enemy::hasDied()
{
    dead = true;
}
