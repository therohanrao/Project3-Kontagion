
#include <string>
#include <cmath>
#include <cassert>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>

#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"

using namespace std;

//const double PI = 4 * atan(1);

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath)
{
    m_socrates = nullptr;
}

StudentWorld::~StudentWorld()
{
    delete m_socrates;
    m_socrates = nullptr;
    cleanUp();
    cerr << "Destructor ran" << endl;
    //assert(m_actors.empty());
}

//IMAGE ID'S:
/*
        //	
        IID_PLAYER(for Socrates)
        IID_SALMONELLA
        IID_ECOLI
        IID_FOOD
        IID_SPRAY
        IID_FLAME
        IID_PIT
        IID_DIRT
        IID_FLAME_THROWER_GOODIE
        IID_RESTORE_HEALTH_GOODIE
        IID_EXTRA_LIFE_GOODIE
        24
        IID_FUNGUS
        //
*/


//Game control functions:
int StudentWorld::init()
{

    /*
    1. Initialize the data structures used to keep track of your game’s world.
2. Allocate and insert a Socrates object into the game world. Every time a level
starts or restarts, Socrates starts out fully initialized (with the baseline number of
sprays, flame thrower charges, hit points, etc.).
3. Allocate and insert various piles of dirt, pits, and food objects into the game world
as described below. 
    */

    /*
1. Create and add a new Socrates/player object at location (0, VIEW_HEIGHT/2) to
the Petri dish; this is in the left-middle of the dish.
    */
    m_socrates = new Socrates(this);

    cerr << "added player..." << endl;

    m_overlapActorIt = m_actors.end();

    //Salmonella* b = nullptr;
    //addNewActor(b, this, 128, 128);

    addPits();
    cerr << "added pits..." << endl;
    addFood();
    cerr << "added food..." << endl;
    addDirt();
    cerr << "added dirt..." << endl;

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

    /*
    1. It must ask all of the actors that are currently active in the game world to do
something (e.g., ask a salmonella to move itself, ask a pit to introduce a new
bacterium into the Petri dish, ask a goodie to check if it overlaps with Socrates,
and if so, grant him a special power, give Socrates a chance to move or fire, etc.).
a. If an actor does something that causes Socrates to die (e.g., an E. coli
damages Socrates until his hit points/health reaches zero), then the move()
method should immediately return GWSTATUS_PLAYER_DIED.
b. Otherwise, if Socrates has cleared the current Petri dish of all bacteria and
all of the pits have disappeared (each pit disappears once it’s released all
of its bacteria into the Petri dish) then it’s time to advance to the next
18
level. In this case, the move() method must return a value of
GWSTATUS_FINISHED_LEVEL.
2. It must then delete any actors that have died during this tick (e.g., a salmonella
that was killed by flames and so should be removed from the game world, or a
goodie that disappeared because it overlapped with Socrates and activated).
3. It must then add any new objects to the game (e.g., a new goodie or fungus).
4. It must update the status text on the top of the screen with the latest information
(e.g., the user’s current score, the number of foods Socrates has, the current level,
etc.).
    */

    //  pseudocode for all move
    /*
     void Ask_all_actors_to_do_something()
 {
 for each actor on the level:
 if (the actor is still alive)
 tell the actor to doSomething();
 }
    */

    int bacteriaCounter = 0;
    int pitCounter = 0;

    list<Actor*>::iterator actorsIt;

    //doSomething && isDead for all actors except socrates
    for (actorsIt = m_actors.begin(); actorsIt != m_actors.end(); ) // notice: no it++
    {
        if ((*actorsIt)->isDead()) //check if dead
        {
            if ((*actorsIt)->damageToPlayer() && !(*actorsIt)->consumable())
                increaseScore(100);

            int playsound = 0;
            double dist = distApart((*actorsIt)->getX(), (*actorsIt)->getY(), m_socrates->getX(), m_socrates->getY());
            if (!(*actorsIt)->damageToPlayer() && (*actorsIt)->consumable() && dist <= SPRITE_WIDTH)
                playsound = 1;
            else if ((*actorsIt)->damageToPlayer() && (*actorsIt)->consumable() && dist <= SPRITE_WIDTH)
                playsound = 2;
            if ((*actorsIt)->getDeathSound())
                playSound((*actorsIt)->getDeathSound());

            delete *actorsIt; //if so, delete
            *actorsIt = nullptr;
            actorsIt = m_actors.erase(actorsIt); //erase object in list and return next in list 

            if (playsound == 1)
                playSound(SOUND_GOT_GOODIE);
            if (playsound == 2)
                playSound(SOUND_PLAYER_HURT);

            continue;
        }

        if ((*actorsIt)->damageToPlayer() && !(*actorsIt)->consumable())
            bacteriaCounter++;

        if (!(*actorsIt)->destructible() && !(*actorsIt)->consumable())
            pitCounter++;

        (*actorsIt)->doSomething(); //call all doSomething for actors
        actorsIt++; // otherwise go to next pointer in list
    }

    if (bacteriaCounter == 0 && pitCounter == 0)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }

    m_socrates->doSomething(); //must be after all object's doSomething()!!!
    if (m_socrates->isDead())
    {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }

    addFungus();
    addGoodies();

    ostringstream gameText;
    gameText.fill('0');
    gameText << "Score: " << setw(6) << getScore() << "  Level: " << getLevel()
        << "  Lives: " << getLives() << "  Health: " << m_socrates->getHealth()
        << "  Sprays: " << m_socrates->getSprays()
        << "  Flames: " << m_socrates->getFlames();

    setGameStatText(gameText.str());

        return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator actorsIt;

    for (actorsIt = m_actors.begin(); actorsIt != m_actors.end(); ) // notice: no it++
    {
        delete *actorsIt;
        *actorsIt = nullptr;
        actorsIt = m_actors.erase(actorsIt);
    }

    delete m_socrates;
    m_socrates = nullptr;

    cerr << "cleanUp ran" << endl;
}

void StudentWorld::addPits()
{

    int numPits = 0;
    int maxPits = getLevel();

    while (numPits < maxPits)
    {
        int xPos = 0;
        int yPos = 0;

        xPos = randInt(0, VIEW_WIDTH);
        yPos = randInt(0, VIEW_HEIGHT);

        Pit* p = new Pit(this, xPos, yPos);

        if (distApart(xPos, yPos) > 120.0 || overlap(p)) //gets random number within dist
        {
            delete p;
            p = nullptr;
            continue;
        }

        m_actors.push_back(p);
        numPits++;

        cerr << "adding pits..." << endl;
    }

    /*
    2. Add L pits to the Petri dish at random locations, in a manner such that no two pits
overlap with each other (their centers are at least 2*SPRITE_RADIUS pixels
apart from each other). Each pit must be no more 120 pixels from the center of the
Petri dish which is at (VIEW_WIDTH/2, VIEW_HEIGHT/2).
    */
}

void StudentWorld::addFood()
{

    int numFood = 0;
    int maxFood = min(5 * getLevel(), 25);

    while (numFood < maxFood)
    {
        int xPos = 0;
        int yPos = 0;

        xPos = randInt(0, VIEW_WIDTH);
        yPos = randInt(0, VIEW_HEIGHT);

        Food* f = new Food(this, xPos, yPos);

        if (distApart(xPos, yPos) > 120.0 || overlap(f)) //gets random number within dist
        {
            delete f;
            f = nullptr;
            continue;
        }
        m_actors.push_back(f);
        numFood++;

        cerr << "adding food..." << endl;
    }

    /*
    3. Add min(5 * L, 25) food objects to the Petri dish at random locations, in a manner
such that no two food objects overlap with each other or previously-placed
pits (their centers must be at least 2*SPRITE_RADIUS pixels apart from each
other). Each food object must be no more 120 pixels from the center of the Petri
dish which is at (VIEW_WIDTH/2, VIEW_HEIGHT/2).
    */
}

void StudentWorld::addDirt()
{
    int maxDirt = max(180 - (20 * getLevel()), 20);
    int numDirt = 0;
    while (numDirt != maxDirt)
    {
        int xPos = 0;
        int yPos = 0;

        xPos = randInt(0, VIEW_WIDTH);
        yPos = randInt(0, VIEW_HEIGHT);

        DirtPile* d = new DirtPile(this, xPos, yPos);

        if (distApart(xPos, yPos) > 120.0 || overlap(d)) //gets random number within dist
        {
            delete d;
            d = nullptr;
            continue;
        }
        m_actors.push_back(d);
        numDirt++;

        cerr << "adding dirt..." << endl;
    }
    cout << "DIRT: " << numDirt << endl;

    /*
    4. Add max(180 – 20 * L, 20) dirt objects to the Petri dish at random locations, in a
manner such that no dirt objects overlap with previously-placed food objects
or pits (their centers are at least 2*SPRITE_RADIUS pixels apart from each
other). It is OK for dirt objects to overlap with each other, however. Each dirt
object must be no more 120 pixels from the center of the Petri dish which is at
(VIEW_WIDTH/2, VIEW_HEIGHT/2)
*/

}


//Playtime functions:
double StudentWorld::distApart(double x1, double y1, double x2, double y2) const //returns the dist between passed coords or center
{
    double xDist = abs(x1 - x2);
    double yDist = abs(y1 - y2);

    double absDist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    return absDist;
}

double StudentWorld::getTheta(Actor* a, Actor* b) const
{
    if (b == nullptr)
        b = m_socrates;

    int deltaY = b->getY() - a->getY();
    int deltaX = b->getX() - a->getX();
    double dist = distApart(a->getX(), a->getY(), b->getX(), b->getY());

    double theta = abs(asin(deltaY/dist));

    //cerr << "THETA: " << theta << endl;
    //cerr << "deltaY: " << deltaY << endl;
    //cerr << "deltaX: " << deltaX << endl;
    //cerr << "dist: " << dist << endl;

    if (deltaY >= 0 && deltaX >= 0) //first quadrant
        return theta;
    else if (deltaY >= 0 && deltaX <= 0) //second quadrant
        return (PI) - theta;
    else if (deltaY <= 0 && deltaX <= 0) //third quadrant
        return (PI) + theta;
    else if (deltaY <= 0 && deltaX >= 0) //fourth quadrant
        return (2 * PI) - theta;

    return -1;
}

bool StudentWorld::overlap(Actor* a1, int overlapDist, int xpos, int ypos)
{

    list<Actor*>::iterator it;
    it = m_actors.begin();

    //if no arguments, use overlap on socrates
    if (a1 == nullptr)
        a1 = m_socrates;

    if (!xpos)
        xpos = a1->getX();
    if (!ypos)
        ypos = a1->getY();

    int k = 0;

    while (it != m_actors.end()) // notice: no it++
    {
        if (a1 != *it && distApart(xpos, ypos, (*it)->getX(), (*it)->getY()) <= overlapDist)
        {
            m_overlapActorIt = it;

            //cerr << xpos << "  " << ypos << endl;
            //cerr << "OKAY: " << k << endl;
            //cerr << "OKAY2: " << a1->getX() << endl;
            //cerr << "OKAY3: " << (*it)->getX() << endl;

            return true;
        }
        it++;
        k++;
    }
    m_overlapActorIt = it;
    return false;

}

int StudentWorld::playerOverlap()
{
    if (overlap() && (*m_overlapActorIt)->consumable() && (*m_overlapActorIt)->destructible())
    {
        cerr << "PLAYER ON SOMETHING" << endl;

        (*m_overlapActorIt)->overlap();

        if (!(*m_overlapActorIt)->damageToPlayer())
        {
            //playSound(SOUND_GOT_GOODIE);
            return 1;
        }
        else
        {
            //playSound(SOUND_PLAYER_HURT);
            return 2;
        }
    }
    return 0;
}


bool StudentWorld::projectileOverlap(Projectile* p)
{
    if (overlap(p) && (*m_overlapActorIt)->destructible())
    {
        //Food* b = nullptr;
        //addNewActor(b, this, p->getX(), p->getY());

        (*m_overlapActorIt)->takeDamage(p->damageGiven());
        p->setDead();
        return true;
    }
    return false;
}

//NEEDS TESTING
bool StudentWorld::bacteriaOverlap(Bacteria* b)
{
    if (bacteriaOnPlayer(b))
        return true;
    else if (bacteriaOnFood(b))
        return true;
    else if (bacteriaOnDirt(b))
        return true;
    else return false;
}

//START BACTERIA AUXILIARY FUNCTIONS

bool StudentWorld::bacteriaOnPlayer(Bacteria* b)
{
    //if on a player
    if (distApart(b->getX(), b->getY(), m_socrates->getX(), m_socrates->getY()) <= SPRITE_WIDTH)
    {
        playSound(SOUND_PLAYER_HURT);
        m_socrates->takeDamage(b->damageToPlayer());
        return true;
    }
    else
        return false;
}

bool StudentWorld::bacteriaOnFood(Bacteria* b)
{
    //if on food
    if (overlap(b, SPRITE_WIDTH / 2) && (*m_overlapActorIt)->consumable() && !(*m_overlapActorIt)->destructible())
    {
        (*m_overlapActorIt)->setDead(); //tell food it's dead
        b->eatMitosis(); //increase food/ make more bacteria
        return true;
    }
    else
        return false;
}

bool StudentWorld::bacteriaOnDirt(Bacteria* b, double moveDist, double dir)
{
    double nextx = 0;
    double nexty = 0;

    if (dir < 0)
        dir = b->getDirection();

    b->getPositionInThisDirection(dir, moveDist, nextx, nexty);

    //if on a dirt
    if (overlap(b, SPRITE_WIDTH / 2, nextx, nexty)
        && !(*m_overlapActorIt)->consumable()
        && !(*m_overlapActorIt)->damageToPlayer()
        && (*m_overlapActorIt)->destructible())
    {
        b->dirtBlocked(true);
        return true;
    }
    else
        b->dirtBlocked(false);

    return false;
}

// END BACTERIA AUXILIARY FUNCTIONS

bool StudentWorld::consumableOverlap(Consumable* c)
{
    c->applyEffect(m_socrates);
    return true;
}

void StudentWorld::addFungus()
{
    int chanceFungus = max(510 - getLevel() * 10, 200);
    bool spawnFungus = randInt(0, chanceFungus);

   if (!spawnFungus)
    {
        int x = 0;
        int y = 0;
        int theta = randInt(0, 359);

        m_socrates->polarToCartesian(x, y, theta);
        x += VIEW_WIDTH / 2;
        y += VIEW_HEIGHT / 2;
        m_actors.push_back(new Fungus(this, x, y));
    }

}

void StudentWorld::addGoodies()
{
    int chanceGoodie = max(510 - getLevel() * 10, 250);
    bool spawnGoodie = randInt(0, chanceGoodie);

   if (!spawnGoodie)
    {

        int x = 0;
        int y = 0;
        int theta = randInt(0, 359);

        m_socrates->polarToCartesian(x, y, theta);
        x += VIEW_WIDTH / 2;
        y += VIEW_HEIGHT / 2;

        int goodieType = randInt(0, 9);

        if (goodieType == 0)
            m_actors.push_back(new LifeG(this, x, y));
        else if (goodieType <= 3)
            m_actors.push_back(new FlameG(this, x, y));
        else
            m_actors.push_back(new HealthG(this, x, y));
    }
}


//finds closest food and returns dist 
bool StudentWorld::findFood(Bacteria* b, double& newdir)
{
    
    list<Actor*> tempFood;
    list<Actor*>::iterator it;

    //add all food to list
    for (it = m_actors.begin(); it != m_actors.end();) // notice: no it++
    {
        if ((*it)->consumable() && !(*it)->destructible()) //check if food
            tempFood.push_back(*it);
        it++; // iterate through list
        //cerr << "running forever" << endl;
    }

    if (tempFood.empty())
    {
        return false;
    }

    Actor* closest = *tempFood.begin();

    for (it = tempFood.begin(); it != tempFood.end();)
    {
        if (distApart(b->getX(), b->getY(), (*it)->getX(), (*it)->getY() 
            < distApart(b->getX(), b->getY(), closest->getX(), closest->getY()) ))
        {
            closest = *it;
        }
        it++;
    }

    if (distApart(b->getX(), b->getY(), closest->getX(), closest->getY()) >= 128)
        return false;
    else
    {
        newdir = getTheta(b, closest);
        //cerr << "studentworld newdir in radians: " << newdir << endl;
        radiansToDegrees(newdir);

        //cerr << "studentworld newdir : " << newdir << endl;
        return true;
    }
}

void StudentWorld::findSocrates(double& sx, double& sy)
{
    sx = m_socrates->getX();
    sy = m_socrates->getY();
}

//  GAMEWORLD FUNCTIONS? HERE:
/*

unsigned int getLevel() const;
unsigned int getLives() const;
void decLives();
void incLives();
unsigned int getScore() const;
void increaseScore(unsigned int howMuch);
void setGameStatText(string text);
bool getKey(int& value);
void playSound(int soundID);


getLevel() can be used to determine the current level number.

getLives() can be used to determine how many lives Socrates has left.

decLives() reduces the number of Kontagion lives by one.

incLives() increases the number of Kontagion lives by one.

getScore() can be used to determine Socrates’s current score.

increaseScore() is used by a StudentWorld object (or your other classes) to increase or
decrease the user’s score upon successfully destroying a bacterium, picking up a goodie
of some sort or getting injured by a fungus. When your code calls this method, you must
specify how many points the user gets (e.g., 100 points for destroying a salmonella, -50
points if a human steps onto a fungus). This means that the game score is controlled by
our GameWorld object – you must not maintain your own score data member in your
own classes.
16

The setGameStatText() method is used to specify what text is displayed at the top of the
game screen, e.g.:
 Score: 004500 Level: 4 Lives: 3 health: 82 Sprays: 16 Flames: 4

 getKey() can be used to determine if the user has hit a key on the keyboard to move
Socrates or to fire a projectile. This method returns true if the user hit a key during the
current tick, and false otherwise (if the user did not hit any key during this tick). The only
argument to this method is a variable that will be set to the key that was pressed by the
user (if any key was pressed). If the function returns true, the argument will be set to one
of the following values (defined in GameConstants.h):
KEY_PRESS_LEFT
KEY_PRESS_RIGHT
KEY_PRESS_UP
KEY_PRESS_DOWN
KEY_PRESS_SPACE
KEY_PRESS_TAB
KEY_PRESS_ENTER

The playSound() method can be used to play a sound effect when an important event
happens during the game (e.g., a bacterium dies or Socrates picks up a goodie). You can
find constants (e.g., SOUND_PLAYER_SPRAY) that describe what noise to make in the
GameConstants.h file. The playSound() method is defined in our GameWorld class,
which you will use as the base class for your StudentWorld class. Here’s how this method
might be used:
 // if a salmonella dies, make a dying sound
 if (theSalmonellaHasDied())
 studentWorldObject->playSound(SOUND_SALMONELLA_DIE);
    */