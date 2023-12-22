#include "GameScene.h"

USING_NS_CC;

Scene* Space_Invaders::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = Space_Invaders::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Space_Invaders::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Space_Invaders::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    

    /////////////////////////////
    // 3. add your codes below...

    int player_id = 11;
    Player pl(player_id, Object_T::playerT, visibleSize.width/2, origin.y + p.getBody()->getContentSize().height,"assets/Player/player_shield.png", 1, 1,0);
    p = pl;
    shields = vector<Equipment>{
                                 Equipment("assets/Player/player_shield.png",
                                           16,
                                           Object_T::equipT,
                                           origin.x + visibleSize.width/5,
                                           origin.y + visibleSize.height/5,
                                           1, 0, true, Object_T::none),
                                 Equipment("assets/Player/player_shield.png",
                                           32,
                                           Object_T::equipT,
                                           origin.x + visibleSize.width/5 + 90,
                                           origin.y + visibleSize.height/5,
                                           1, 0, true, Object_T::none),
                                 Equipment("assets/Player/player_shield.png",
                                           64,
                                           Object_T::equipT,
                                           origin.x + visibleSize.width/5+180,
                                           origin.y + visibleSize.height/5,
                                           1, 0, true, Object_T::none),
                                 Equipment("assets/Player/player_shield.png",
                                           128,
                                           Object_T::equipT,
                                           origin.x + visibleSize.width/5+270,
                                           origin.y + visibleSize.height/5,
                                           1, 0, true, Object_T::none)
                               };
    
    scoreBoard = Label::createWithTTF("Score: "+to_string(p.getScore()),
    "assets/space_invaders.ttf", 24);
    
    // position the label on the center of the screen
    scoreBoard->setPosition(Vec2(origin.x+45, origin.y + visibleSize.height -
                                 scoreBoard->getContentSize().height/2));
    scoreBoard->setScale(.5);
    this->addChild(scoreBoard, 1);
    endGame = Label::createWithTTF("","assets/space_invaders.ttf",24);
    endGame->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.width/2));
    endGame->setScale(.5f);
    this->addChild(endGame,1);
    p.scale(1.5);
    this->addChild(p.getBody(),1);
    /**
    vector<vector<Enemy>> enemies = em.getEnemies();
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("assets/Enemies/APlist.plist");
    for (int i = 0; i < 11; ++i)
    {
        Vec2 pos = enemies[0][i].getBody()->getPosition();
        enemies[0][i].setBody("assets/Enemies/invaderAframe1.png", pos.x, pos.y);
        enemies[1][i].setBody("assets/Enemies/invaderAframe1.png", pos.x, pos.y);
    }
    Vector<SpriteFrame*> A_frames;
    A_frames.pushBack(cache->getSpriteFrameByName("assets/Enemies/invaderAframe1.png"));
    A_frames.pushBack(cache->getSpriteFrameByName("assets/Enemies/invaderAframe2.png"));
    animateA = new Animation;
    animateA->initWithSpriteFrames(A_frames, 1.0f);*/
    for (int i = 0; i < shields.size(); ++i)
    {
        this->addChild(shields[i].getBody(),1);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            this->addChild(em.getSpriteAt(i, j),1);
        }
    }
    
    per = 1;
    dx = 1.0;
    dy = 25.0;
    moveRight = true;
    sideHit = 0;
    moveDown = false;
    botMin = shields[0].getBody()->getPosition().y + shields[0].getBody()->getContentSize().height;
    cycle = 0;
    attk_cycle = 250;
    vector<vector<Enemy>> temp = em.getEnemies();
    
    playerMissle = Equipment("assets/Player/player_missle.png",12, Object_T::equipT, 0.0, -100.0, 1, 1, false, Object_T::playerT);
    
    this->addChild(playerMissle.getBody(),1);
    
    //set up all the listeners needed to do touch, use accelerometer, detect collisions
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Space_Invaders::onAcceleration,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Space_Invaders::onTouchBegan,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Space_Invaders::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Space_Invaders::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->scheduleUpdate();
    return true;
}


void Space_Invaders::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (p.getBody()->getPosition().x + acc->x*5.0 > origin.x+p.getBody()->getContentSize().width/2 &&
        p.getBody()->getPosition().x + acc->x*5.0 < visibleSize.width+p.getBody()->getContentSize().width)
    {
        auto action = MoveTo::create(0.1, Point(p.getBody()->getPosition().x+acc->x*5.0,p.getBody()->getPosition().y));
        p.getBody()->runAction(action);
    }
    else
    {
        if (p.getBody()->getPosition().x + acc->x*5.0 < origin.x+p.getBody()->getContentSize().width/2)
        {
            auto action = MoveTo::create(0.1, Point(origin.x+p.getBody()->getContentSize().width/2.0+3,p.getBody()->getPosition().y));
            p.getBody()->runAction(action);
        }
        else
        {
            auto action = MoveTo::create(0.1, Point(visibleSize.width + p.getBody()->getContentSize().width,p.getBody()->getPosition().y));
            p.getBody()->runAction(action);
        }
    }
}

bool Space_Invaders::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    p._attack(playerMissle);
    return true;
}


bool Space_Invaders::onContactBegin(PhysicsContact& contact)
{
    if (contact.getShapeA()->getCollisionBitmask() == 13 &&
        contact.getShapeB()->getCollisionBitmask() == 13)
    {
        return false;
    }
    int idA = contact.getShapeA()->getBody()->getCollisionBitmask();
    int idB = contact.getShapeB()->getBody()->getCollisionBitmask();
    enum Types{player, shield, weapon, enemy};
    Types A, B;
    if (idA == 11)
    {
        A = Types::player;
    }
    else if (idA == 12 || idA == 13)
    {
        A = Types::weapon;
    }
    else if (128 >= idA && idA >= 16)
    {
        A = Types::shield;
    }
    else if (idA >= 256)
    {
        A = Types::enemy;
    }
    
    if (idB == 11)
    {
        B = Types::player;
    }
    else if (idB == 12 || idB == 13)
    {
        B = Types::weapon;
    }
    else if (128 >= idB && idB >= 16)
    {
        B = Types::shield;
    }
    else if (idB >= 256)
    {
        B = Types::enemy;
    }
    
    if (A == Types::player && B == Types::weapon)
    {
        if (idB == 12)
        {
            return false;
        }
        p.died();
        Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
        Device::setAccelerometerEnabled(false);
    }
    else if (B == Types::player && A == Types::weapon)
    {
        if (idA == 12)
        {
            return false;
        }
        p.died();
        Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
        Device::setAccelerometerEnabled(false);
    }
    
    else if (A == Types::enemy && B == Types::weapon)
    {
        if (idB == 13)
        {
            return false;
        }
        int row;
        int mask = 0x1F00;
        int check = idA & mask;
        switch (check)
        {
            case 4096:
                row = 0;
                break;
            case 2048:
                row = 1;
                break;
            case 1024:
                row = 2;
                break;
            case 512:
                row = 3;
                break;
            case 256:
                row = 4;
                break;
            default:
                break;
        }
        int colMask =0xF;
        int col = idA & colMask;
        em.hasDied(row, col);
        if (em.inFront(row, col))
            em.decreaseFrontLineAt(col);
        vector<vector<Enemy>> enemies = em.getEnemies();
        enemies[row][col].getBody()->removeFromParentAndCleanup(true);
        playerMissle.changeActive(false);
        auto action = cocos2d::MoveTo::create(0, Point(0,-100));
        playerMissle.getBody()->runAction(action);
        p.increaseScore();
        return true;
    }
    else if (B == Types::enemy && A == Types::weapon)
    {
        if (idB == 13)
        {
            return false;
        }
        int row;
        int mask = 0x1F00;
        int check = idB & mask;
        switch (check)
        {
            case 4096:
                row = 0;
                break;
            case 2048:
                row = 1;
                break;
            case 1024:
                row = 2;
                break;
            case 512:
                row = 3;
                break;
            case 256:
                row = 4;
                break;
            default:
                break;
        }
        int colMask =0xF;
        int col = idB & colMask;
        em.hasDied(row, col);
        if (em.inFront(row, col))
            em.decreaseFrontLineAt(col);
        vector<vector<Enemy>> enemies = em.getEnemies();
        enemies[row][col].getBody()->removeFromParentAndCleanup(true);
        playerMissle.changeActive(false);
        auto action = cocos2d::MoveTo::create(0, Point(0,-100));
        playerMissle.getBody()->runAction(action);
        p.increaseScore();
        return true;
        
    }
    else if (A == Types::shield && B == Types::weapon)
    {
        if (idB == 12)
        {
            playerMissle.changeActive(false);
            auto action = cocos2d::MoveTo::create(0, Point(0,-100));
            playerMissle.getBody()->runAction(action);
        }
        else
        {
            switch (idA)
            {
                case 16:
                    if (shields[0].isActive())
                    {
                        shields[0].getBody()->removeFromParentAndCleanup(true);
                        shields[0].changeActive(false);
                    }
                    break;
                case 32:
                    if (shields[1].isActive())
                    {
                        shields[1].getBody()->removeFromParentAndCleanup(true);
                        shields[1].changeActive(false);
                    }
                    break;
                case 64:
                    if (shields[2].isActive())
                    {
                        shields[2].getBody()->removeFromParentAndCleanup(true);
                        shields[2].changeActive(false);
                    }
                    break;
                case 128:
                    if (shields[3].isActive())
                    {
                        shields[3].getBody()->removeFromParentAndCleanup(true);
                        shields[3].changeActive(false);
                    }
                    break;
                default:
                    break;
            }
            contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
        }
    }
    else if (B == Types::shield && A == Types::weapon)
    {
        if (idA == 12)
        {
            playerMissle.changeActive(false);
            auto action = cocos2d::MoveTo::create(0, Point(0,-100));
            playerMissle.getBody()->runAction(action);
        }
        else
        {
            switch (idB)
            {
                case 16:
                    if (shields[0].isActive())
                    {
                        shields[0].getBody()->removeFromParentAndCleanup(true);
                        shields[0].changeActive(false);
                    }
                    break;
                case 32:
                    if (shields[1].isActive())
                    {
                        shields[1].getBody()->removeFromParentAndCleanup(true);
                        shields[1].changeActive(false);
                    }
                    break;
                case 64:
                    if (shields[2].isActive())
                    {
                        shields[2].getBody()->removeFromParentAndCleanup(true);
                        shields[2].changeActive(false);
                    }
                    break;
                case 128:
                    if (shields[3].isActive())
                    {
                        shields[3].getBody()->removeFromParentAndCleanup(true);
                        shields[3].changeActive(false);
                    }
                    break;
                default:
                    break;
            }
             contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
        }
    }
    
    else if ( (idA == 12  && idB == 13) || (idA == 13 && idB == 12))
    {
        playerMissle.changeActive(false);
        auto action = cocos2d::MoveTo::create(0, Point(0,-100));
        playerMissle.getBody()->runAction(action);
        if (idB == 13)
            contact.getShapeB()->getBody()->getNode()->removeFromParentAndCleanup(true);
        else
            contact.getShapeA()->getBody()->getNode()->removeFromParentAndCleanup(true);
        
    }
    return true;
}

void Space_Invaders::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Space_Invaders::update(float f)
{
    if (!p.isDead()  && !em.allDead())
    {
        int leftMostCol = 11;
        int rightMostCol = -1;
        int botMostRow = 5;
        Enemy leftMost;
        Enemy rightMost;
        Enemy botMost;
        vector< vector<Enemy> > enemies = em.getEnemies();
        int maxRows = 5;
        int maxCols = 11;
        ++cycle;
        for (int i = 0; i < maxRows; ++i)
        {
            for (int j = 0; j < maxCols; ++j)
            {
                if (enemies[i][j].isDead() == false && j > rightMostCol)
                {
                    rightMostCol = j;
                    rightMost = enemies[i][j];
                }
                if (enemies[i][j].isDead() == false && j < leftMostCol)
                {
                    leftMostCol = j;
                    leftMost = enemies[i][j];
                }
                if (enemies[i][j].isDead() == false && i < botMostRow)
                {
                    botMostRow = i;
                    botMost = enemies[i][j];
                }
            }
            
        }

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        for (int i = 0; i < maxRows; ++i)
        {
            for (int j = 0; j < maxCols; ++j)
            {
                /**
                if (cycle%cycle_check==0)
                {
                    switch (enemies[i][j].getType())
                    {
                        case Enemy_T::A:
                        {
                            enemies[i][j].getBody()->runAction(Animate::create(animateA));
                            break;
                        }
                        case Enemy_T::B:
                        {
                            enemies[i][j].getBody()->runAction(animB);
                            break;
                        }
                        case Enemy_T::C:
                        {
                            enemies[i][j].getBody()->runAction(animC);
                            break;
                        }
                        default:
                            break;
                     }
                }*/
                if (enemies[i][j].isDead())
                {
                    continue;
                }
                if (moveDown)
                {
                    if (botMost.getBody()->getPosition().y - dy > botMin)
                    {
                        auto action = MoveBy::create(per, Point(0,-1*dy));
                        enemies[i][j].getBody()->runAction(action);
                    }
                    else
                    {
                        if (i == 0)
                        {
                            auto action = MoveTo::create(per,
                                                         Point(enemies[i][j].getBody()->getPosition().x, botMin));
                            enemies[i][j].getBody()->runAction(action);
                        }
                        else
                        {
                            if (!em.enemiesAt(botMin))
                            {
                                if (j == 0)
                                {
                                    auto action = MoveTo::create(per,
                                                Point(enemies[i][j].getBody()->getPosition().x,
                                                      enemies[i-1][j].getBody()->getPosition().y +
                                                      enemies[i-1][j].getBody()->getContentSize().height-4));
                                    enemies[i][j].getBody()->runAction(action);
                                }
                                else
                                {
                                    auto action = MoveTo::create(per,
                                                Point(enemies[i][j].getBody()->getPosition().x,
                                                      enemies[i][j-1].getBody()->getPosition().y -
                                                      enemies[i-1][j].getBody()->getContentSize().height-2));
                                    enemies[i][j].getBody()->runAction(action);
                                }
                            }
                        }
                    }
                }
                else if ( moveRight)
                {
                    if (rightMost.getBody()->getPosition().x + dx <
                        visibleSize.width+rightMost.getBody()->getContentSize().width/2)
                    {
                        auto action = MoveTo::create(
                                                per, Point(enemies[i][j].getBody()->getPosition().x+dx,
                                                enemies[i][j].getBody()->getPosition().y)
                                                    );
                        enemies[i][j].getBody()->runAction(action);
                    }
                    else
                    {
                        if (++sideHit % 4 == 0 && sideHit != 0)
                        {
                            moveDown = true;
                            sideHit = (rand()%2+1)%2 == 0 ? 0:-1;
                            --j;
                        }
                        moveRight = false;
                    }
                }
                else
                {
                    if (leftMost.getBody()->getPosition().x - dx >
                        origin.x+leftMost.getBody()->getContentSize().width*2)
                    {
                        auto action = MoveTo::create(
                                                     per, Point(enemies[i][j].getBody()->getPosition().x-dx,
                                                     enemies[i][j].getBody()->getPosition().y)
                                                     );
                        enemies[i][j].getBody()->runAction(action);
                    }
                    else
                    {
                        if (++sideHit % 4 == 0 && sideHit != 0)
                        {
                            moveDown = true;
                            sideHit = (rand()%2+1)%2 == 0 ? 0:-1;
                            --j;
                        }
                        moveRight = true;
                    }
                }
            }
        }
        if (cycle % attk_cycle==0 ||  cycle % (attk_cycle+30)==0 || cycle % (attk_cycle+60)==0 || cycle % (attk_cycle+90)==0)
        {
            vector< pair<int,int> > front = em.getFrontLine();
            int attacker = rand()%11;
            if (front[attacker].first != -1)
            {
                Equipment weapon = enemies[front[attacker].first][front[attacker].second]._attack();
                auto dir = Director::getInstance();
                dir->getRunningScene()->addChild(weapon.getBody(),1);
            }
        }
        if (moveDown)
            moveDown = false;

        if (playerMissle.isActive())
        {
            auto action = cocos2d::MoveBy::create(5, Vec2(0,20));
            playerMissle.getBody()->runAction(action);
        }
        if (playerMissle.getBody()->getPosition().y > 300)
        {
            playerMissle.changeActive(false);
            auto action = cocos2d::MoveTo::create(0, Point(0,-100));
            playerMissle.getBody()->runAction(action);
        }
        scoreBoard->setString("Score: " + to_string(p.getScore()));
    }
    else
    {
        scoreBoard->setString("Score: " + to_string(p.getScore()));
        endGame->setString("Game Over.\nFinal Score: " + to_string(p.getScore()));
        Color3B color = p.isDead() ? Color3B::RED : Color3B::GREEN;
        endGame->setColor(color);
    }
}
