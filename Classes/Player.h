//
//  Player.h
//  SimpleSpaceInv
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#ifndef Player_h
#define Player_h
#include "Object.h"
#include "Equipment.h"

class Player : public Object
{
    private:
    int attack_dmg;
    long score;
    const int score_incr = 10;
    bool alive;
    
    public:
    Player(int iD = 0,
           Object_T oT = Object_T::playerT,
           float x = 0,
           float y = 0,
           string ship = "assets/Player/spaceship.png",
           int hp = 1,
           int dmg = 1,
           long pts = 0,
           bool livin = true);
    
    void setHealth(int hp);
    
    void _attack(Equipment& missle);
    
    long getScore() const;
    
    void increaseScore();
    
    void scale(float factor);
    
    Player& operator=(Player &rhs);
    
    bool isDead() const;
    
    void died();
    
};
#endif /* Player_hpp */
