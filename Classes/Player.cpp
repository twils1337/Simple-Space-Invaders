//
//  Player.cpp
//  SimpleSpaceInv
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#include "Player.h"

Player::Player(int iD, Object_T oT, float x, float y, string ship, int hp, int dmg, long pts, bool livin)
:score(pts), attack_dmg(dmg), alive(livin)
{
    ID = iD;
    ot = oT;
    body = Sprite::create(ship);
    body->setPosition(x,y);
    auto physicsBody = cocos2d::PhysicsBody::createBox(getBody()->getContentSize(),
                                                       cocos2d::PhysicsMaterial(0.1,0,0.1));
    physicsBody->setCollisionBitmask(ID);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(true);
    body->setPhysicsBody(physicsBody);
    health = hp;
}

long Player::getScore() const
{
    return score;
}

void Player::scale(float factor)
{
    body->setScale(factor);
}
 

void Player::_attack(Equipment& missle)
{
    if (!missle.isActive())
    {
        missle.changeActive(true);
        auto action = cocos2d::MoveTo::create(0, Point(
                                            getBody()->getPosition().x,
                                            getBody()->getContentSize().height + getBody()->getPosition().y));
        missle.getBody()->runAction(action);
    }
}

void Player::setHealth(int hp)
{
    health = hp;
}

void Player::increaseScore()
{
    score += score_incr;
}

Player& Player::operator=(Player &rhs)
{
    ID = rhs.ID;
    ot = rhs.ot;
    body = Sprite::create("assets/Player/spaceship.png");
    body->setPosition(rhs.getBody()->getPosition().x, rhs.getBody()->getPosition().y);
    auto physicsBody = cocos2d::PhysicsBody::createBox(getBody()->getContentSize(),
                                                       cocos2d::PhysicsMaterial(0,0,0));
    physicsBody->setCollisionBitmask(ID);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(true);
    body->setPhysicsBody(physicsBody);
    health = rhs.health;
    return *this;
}

bool Player::isDead() const
{
    return alive == false;
}

void Player::died()
{
    alive = false;
}


