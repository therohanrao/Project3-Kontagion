#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Socrates;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();


    //x2 & y2 set to center of circle default
    double distApart(int x1, int y1, int x2 = VIEW_WIDTH/2, int y2 = VIEW_HEIGHT/2) const;

    bool overlap(Actor* a1);
    
    //GODLY:
    template<typename ActorType>
    void addNewActor(ActorType* &a, StudentWorld* world, int x, int y, int dir = 0)
    {
        a = new ActorType(world, x, y, dir);
        m_actors.push_back(a);
        std::cerr << "new actor added..." << std::endl;
    }


private:

    //move these three to private later: 
    //SHOULD THIS BE IN PRIVATE THO??
    void addPits();
    void addDirt();
    void addFood();


    Socrates* m_socrates;

    std::list<Actor*> m_actors;
    int m_numActors;

    const int m_centerX = VIEW_WIDTH/2;
    const int m_centerY = VIEW_HEIGHT/2;
};

#endif // STUDENTWORLD_H_
