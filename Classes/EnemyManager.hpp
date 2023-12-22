//
//  EnemyManager.hpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#ifndef EnemyManager_hpp
#define EnemyManager_hpp
#include "Enemy.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>

class EnemyManager
{
    private:
    vector< vector<Enemy> > manager;
    vector< pair<int,int> > front_line; //aliens at the front of their respective column
    const int MAXPERROW = 11;
    //id prefixes are used to help id enemies when collision detection has occured
    const int idPrefixRow1 = 4096;
    const int idPrefixRow2 = 2048;
    const int idPrefixRow3 = 1024;
    const int idPrefixRow4 = 512;
    const int idPrefixRow5 = 256;
    
    public:
    EnemyManager();
    
    Sprite* getSpriteAt(int i, int j);
    
    vector< vector<Enemy> > getEnemies();
    
    //helper function to see if an enemy is at a certain spot
    //->mostly used to make sure aliens don't go past shield area
    bool enemiesAt(float y);
    
    void decreaseFrontLineAt(int i);
    
    void hasDied(int i, int j);
    
    bool inFront(int i, int j); //checks to see if alien at i,j is at the front of their column
    
    vector<pair<int,int>> getFrontLine();
    
    bool allDead();
};
#endif /* EnemyManager_hpp */
