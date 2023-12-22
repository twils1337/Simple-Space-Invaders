//
//  EnemyManager.cpp
//  SimpleSpaceInvaders
//
//  Created by Tyler Wilson on 3/3/16.
//
//

#include "EnemyManager.hpp"


EnemyManager::EnemyManager()
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    float buffer =visibleSize.width/5;
    int weapon = -42;
    srand(time(NULL));
    
    
    int id;
    Enemy Jelly1 = Enemy(idPrefixRow1,
                         Object_T::enemyT,
                         Enemy_T::A,
                         origin.x + buffer,
                         origin.y + visibleSize.height - 80,
                         "assets/Enemies/invaderAframe1.png",
                         "assets/Enemies/enemy_ray.png",
                         1, 1, false);
    vector<Enemy> jellys1{Jelly1};
    front_line.push_back(make_pair(0, 0));
    for (int i = 1; i < MAXPERROW; ++i)
    {
        weapon = rand()%2+1;
        string atk = (weapon == 1) ? "assets/Enemies/enemy_ray.png" : "assets/Enemies/enemy_missle.png";
        id = idPrefixRow1 | i;
        jellys1.push_back(
        Enemy(id,
              Object_T::enemyT,
              Enemy_T::A,
              jellys1[i-1].getBody()->getPosition().x + jellys1[i-1].getBody()->getContentSize().width+5,
              jellys1[i-1].getBody()->getPosition().y,
              "assets/Enemies/invaderAframe1.png",
              atk,
              1, 1, false)
        );
        front_line.push_back(make_pair(0, i));
    }
    manager.push_back(jellys1);
    
    Enemy Jelly2 = Enemy(idPrefixRow2,
                         Object_T::enemyT,
                         Enemy_T::A,
                         origin.x + buffer,
                    jellys1[0].getBody()->getPosition().y+jellys1[0].getBody()->getContentSize().height+5,
                    "assets/Enemies/invaderAframe1.png",
                    "assets/Enemies/enemy_ray.png",
                    1, 1, false);
    vector<Enemy> jellys2{Jelly2};
    for (int i = 1; i < MAXPERROW; ++i)
    {
        weapon = rand()%2+1;
        string atk = (weapon == 1) ? "assets/Enemies/enemy_ray.png" : "assets/Enemies/enemy_missle.png";
        id = idPrefixRow2 | i;
        jellys2.push_back(
                          Enemy(id,
                                Object_T::enemyT,
                                Enemy_T::A,
                                jellys2[i-1].getBody()->getPosition().x + jellys2[i-1].getBody()->getContentSize().width+5,
                                jellys1[i-1].getBody()->getPosition().y + jellys1[i-1].getBody()->getContentSize().height+5,
                                "assets/Enemies/invaderAframe1.png",
                                atk,
                                1, 1, false)
                          );
    }
    manager.push_back(jellys2);
    

    Enemy Bug1 = Enemy(idPrefixRow3,
                       Object_T::enemyT,
                       Enemy_T::B,
                       origin.x + buffer,
                         jellys2[0].getBody()->getPosition().y+jellys2[0].getBody()->getContentSize().height+5,
                         "assets/Enemies/invaderBframe1.png",
                         "assets/Enemies/enemy_missle.png",
                         1, 1, false);
    vector<Enemy> bugs1{Bug1};
    for (int i = 1; i < MAXPERROW; ++i)
    {
        weapon = rand()%2+1;
        string atk = (weapon == 1) ? "assets/Enemies/enemy_ray.png" : "assets/Enemies/enemy_missle.png";
        id = idPrefixRow3 | i;
        bugs1.push_back(
                          Enemy(id,
                                Object_T::enemyT,
                                Enemy_T::B,
                                bugs1[i-1].getBody()->getPosition().x + jellys2[i-1].getBody()->getContentSize().width+5,
                                jellys2[i-1].getBody()->getPosition().y + jellys2[i-1].getBody()->getContentSize().height+5,
                                "assets/Enemies/invaderBframe1.png",
                                atk,
                                1, 1, false)
                          );
        bugs1[i-1].getBody()->setScale(1.05);
    }
    bugs1[MAXPERROW-1].getBody()->setScale(1.05);
    manager.push_back(bugs1);
    
    Enemy Bug2 = Enemy(idPrefixRow4,
                       Object_T::enemyT,
                       Enemy_T::B,
                       origin.x + buffer,
                       bugs1[0].getBody()->getPosition().y+bugs1[0].getBody()->getContentSize().height+5,
                       "assets/Enemies/invaderBframe1.png",
                       "assets/Enemies/enemy_missle.png",
                       1, 1, false);
    vector<Enemy> bugs2{Bug2};
    for (int i = 1; i < MAXPERROW; ++i)
    {
        weapon = rand()%2+1;
        string atk = (weapon == 1) ? "assets/Enemies/enemy_ray.png" : "assets/Enemies/enemy_missle.png";
        id = idPrefixRow4 | i;
        bugs2.push_back(
                        Enemy(id,
                              Object_T::enemyT,
                              Enemy_T::B,
                              bugs2[i-1].getBody()->getPosition().x + jellys1[i-1].getBody()->getContentSize().width+5,
                              bugs1[i-1].getBody()->getPosition().y + jellys1[i-1].getBody()->getContentSize().height+5,
                              "assets/Enemies/invaderBframe1.png",
                              atk,
                              1, 1, false)
                        );
        bugs2[i-1].getBody()->setScale(1.1);
    }
    bugs2[MAXPERROW-1].getBody()->setScale(1.1);
    manager.push_back(bugs2);
    
    Enemy Squid = Enemy(idPrefixRow5,
                        Object_T::enemyT,
                        Enemy_T::B,
                        origin.x + buffer,
                       bugs2[0].getBody()->getPosition().y+bugs1[0].getBody()->getContentSize().height+5,
                       "assets/Enemies/invaderCframe1.png",
                       "assets/Enemies/enemy_missle.png",
                       1, 1, false);
    vector<Enemy> squids{Squid};
    for (int i = 1; i < MAXPERROW; ++i)
    {
        weapon = rand()%2+1;
        string atk = (weapon == 1) ? "assets/Enemies/enemy_ray.png" : "assets/Enemies/enemy_missle.png";
        id = idPrefixRow5 | i;
        squids.push_back(
                        Enemy(id,
                              Object_T::enemyT,
                              Enemy_T::B,
                              squids[i-1].getBody()->getPosition().x + jellys1[i-1].getBody()->getContentSize().width+5,
                              bugs2[i-1].getBody()->getPosition().y + jellys1[i-1].getBody()->getContentSize().height+5,
                              "assets/Enemies/invaderCframe1.png",
                              atk,
                              1, 1, false)
                        );
        squids[i-1].getBody()->setScale(1.1);
    }
    squids[MAXPERROW-1].getBody()->setScale(1.1);
    manager.push_back(squids);
}

Sprite* EnemyManager::getSpriteAt(int i, int j)
{
    return manager[i][j].getBody();
}

vector< vector<Enemy> > EnemyManager::getEnemies()
{
    return manager;
}

bool EnemyManager::enemiesAt(float y)
{
    for (int i = 0; i < manager.size(); ++i)
    {
        for (int j = 0; j < MAXPERROW; ++j)
        {
            if (!manager[i][j].isDead() && manager[i][j].getBody()->getPosition().y == y)
            {
                return true;
            }
        }
    }
    return false;
}


void EnemyManager::decreaseFrontLineAt(int col)
{
    int row = front_line[col].first;
    while (manager[row][col].isDead())
    {
        if (row == 4)
        {
            row = -1;
            break;
        }
        ++row;
    }
    front_line[col].first = row;
}

void EnemyManager::hasDied(int i, int j)
{
    manager[i][j].hasDied();
}

bool EnemyManager::inFront(int i, int j)
{
    return ((front_line[j].first == i) && (front_line[j].second == j));
}

vector<pair<int,int>> EnemyManager::getFrontLine()
{
    return front_line;
}

bool EnemyManager::allDead()
{
    for (int i = 0; i < front_line.size(); ++i)
    {
        if (front_line[i].first != -1)
        {
            return false;
        }
    }
    return true;
}