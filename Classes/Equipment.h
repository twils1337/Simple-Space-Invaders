//
//  Equipment.hpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#ifndef Equipment_h
#define Equipment_h
#include "Object.h"


    
class Equipment : public Object
{
    private:
    int damage;
    bool active;
    Object_T sender;
    
    public:
    Equipment(string bod,
              int iD,
              Object_T oT,
              float x = 0,
              float y = 0,
              int hp = 1,
              int dmg = 0,
              bool _active = true,
              Object_T Sender = Object_T::none);
    Equipment();
    
    void setHealth(int hp);
    
    bool isActive();
    
    void changeActive(bool status);
    
    void _attack();
    
    Object_T getSenderT() const;
    
};

#endif /* Equipment_hpp */
