#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Equipment.h"
#include "Enemy.h"
#include "EnemyManager.hpp"
#include <map>


class Space_Invaders : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Space_Invaders);
    
    //handles using the accelerometer so that that the player can move
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
    
    //handles a a screen tap to fire an attack
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    //handles collision detection using Cocos2d's built in physics engine
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    //main game loop function
    void update(float) override;
    
    Player p;
    vector<Equipment> shields;
    EnemyManager em;                  //manages the multiple enemies on screen
    int per;                          //time period for MoveBy
    float dy, dx;                     //change in x and y to help automate enemy movement
    bool moveRight, moveDown;
    int sideHit;
    float botMin;
    const int int_attackers = 4;
    int attk_cycle;
    //int num_attackers;
    int cycle;                         //overall cycles the game has progress through
    const int cycle_check = 40;        //used to help check when to move down
    
    //was to be used for animation
    //const float animation_per = 1.0f;
    //cocos2d::Animation* animateA;
    //cocos2d::Animate* animateB;
    //cocos2d::Animate* animateC;
    
    Equipment playerMissle;
    
    cocos2d::Label* scoreBoard;
    
    cocos2d::Label* endGame;            //shows the end game pop-up
    
private:
    //sets up the game to use Cocos built in physics engine
    //->handled in init
    cocos2d::PhysicsWorld* gameWorld;
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {gameWorld = world;}
    
};

#endif // __Space_Invaders_SCENE_H__
