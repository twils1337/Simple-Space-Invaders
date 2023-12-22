//
//  Character.h
//  SimpleSpaceInv
//
//  Created by Tyler Wilson on 3/3/16.
//
//
#include "cocos2d.h"
#include <iostream>
using namespace std;

typedef cocos2d::Point Point;
typedef cocos2d::Sprite Sprite;

#ifndef Character_h
#define Character_h
enum Object_T {playerT, equipT, enemyT, none};
class Object
{
    protected:
        int ID;
        Object_T ot;
        Sprite* body;
        int health;
        
    public:
        virtual void setHealth(int hp) = 0;
    
        Sprite* getBody()
        {
            return body;
        }
};
#endif /* Character_h */
