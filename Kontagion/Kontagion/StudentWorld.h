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

    //move these three to private later:
    void addPits(); 
    void addDirt();
    void addFood();

    double distFromCenter(int x, int y) const;

private:

    Socrates* m_socrates;

    std::list<Actor*> m_actors;
    int m_numActors;

    int m_centerX = VIEW_WIDTH/2;
    int m_centerY = VIEW_HEIGHT/2;
};

#endif // STUDENTWORLD_H_
