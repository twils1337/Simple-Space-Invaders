//
//  Enemy.hpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//


#ifndef Enemy_h
#define Enemy_h
#include "Object.h"
#include "Equipment.h"

//jelly: assets/Enemies/invadeAframe1.png
//bug: assets/Enemies/invadeBframe1.png
//squid: assets/Enemies/invadeCframe1.png
enum Enemy_T {A, B, C};
class Enemy : public Object
{
    private:
    Enemy_T Type;
    string body_fn; //path/filename of sprite
    string attack_fn;
    int attack_dmg;
    bool dead;
    
    public:
    Enemy(int iD, Object_T oT, Enemy_T et, float x, float y,
          string bod = "assets/Enemies/invadeAframe1.png",
          string attk = "assets/Enemies/enemy_missle.png",
          int hp = 1, int dmg = 1,
          bool ded = false);
    
    Enemy();
    
    bool isDead() const;
    
    void setHealth(int hp);
    
    string getBodyFn() const;
    
    void setBodyFn(string new_fn);
    
    Equipment _attack();
    
    Enemy_T getType() const;
    
    string bodyFileName() { return body_fn; };
    
    void setID(int iD);
    
    int getID() const;
    
    Enemy& operator=(const Enemy &rhs);
    
    void hasDied();
    
    
};
#endif /* Enemy_hpp */
