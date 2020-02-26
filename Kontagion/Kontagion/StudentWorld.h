#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include <string>
#include <list>

#include "GameWorld.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const double PI = 4 * atan(1);

class Actor;
class Socrates;
class DirtPile;
class Bacteria;
class Projectile;
class Consumable;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();


    //x2 & y2 set to center of circle default
    double distApart(double x1, double y1, double x2 = VIEW_WIDTH / 2, double y2 = VIEW_HEIGHT / 2) const;
    //gets theta respect to b or default (socrates)
    double getTheta(Actor* a, Actor* b = nullptr) const;

    bool overlap(Actor* a1 = nullptr, int overlapDist = SPRITE_WIDTH, int xpos = 0, int ypos = 0);

    //GODLY:
    template<typename ActorType>
    void addNewActor(ActorType* a, StudentWorld* world, int x, int y, int dir = 0)
    {
        a = new ActorType(world, x, y, dir);
        m_actors.push_back(a);
        //std::cerr << "new actor added..." << std::endl;
    }

    template<typename numberType>
    void degreesToRadians(numberType& n)
    {
        n = n * (PI / 180);
    }

    template<typename numberType>
    void radiansToDegrees(numberType& n)
    {
        n = n * (180 / PI);
    }

    int playerOverlap();

    bool projectileOverlap(Projectile* p);
    bool bacteriaOverlap(Bacteria* b);
    bool consumableOverlap(Consumable* c);

    bool findFood(Bacteria* b, double& newdir);

    void findSocrates(double& sx, double& sy);

    //auxiliary functions:

    //bacteria
    bool bacteriaOnPlayer(Bacteria* b);
    bool bacteriaOnDirt(Bacteria* b, double moveDist = 3, double dir = -1);
    bool bacteriaOnFood(Bacteria* b);

private:

    //move these three to private later: 
    //SHOULD THIS BE IN PRIVATE THO??

    //init functions
    void addPits();
    void addDirt();
    void addFood();

    //runtime functions
    void addFungus();
    void addGoodies();

    Socrates* m_socrates;

    std::list<Actor*> m_actors;

    std::list<Actor*>::iterator m_overlapActorIt;

    int m_numActors;

    const int m_centerX = VIEW_WIDTH / 2;
    const int m_centerY = VIEW_HEIGHT / 2;

};

#endif // STUDENTWORLD_H_
