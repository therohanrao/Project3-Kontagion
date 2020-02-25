
#include <string>
#include <cmath>
#include <cassert>

#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath)
{
    m_socrates = nullptr;
    m_numActors = 0;
}

StudentWorld::~StudentWorld()
{
    delete m_socrates;
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

int StudentWorld::init()
{

    /*
    1. Initialize the data structures used to keep track of your game�s world.
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
    m_overlapActorIt = m_actors.end();

    addPits();
    addFood();
    addDirt();

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
all of the pits have disappeared (each pit disappears once it�s released all
of its bacteria into the Petri dish) then it�s time to advance to the next
18
level. In this case, the move() method must return a value of
GWSTATUS_FINISHED_LEVEL.
2. It must then delete any actors that have died during this tick (e.g., a salmonella
that was killed by flames and so should be removed from the game world, or a
goodie that disappeared because it overlapped with Socrates and activated).
3. It must then add any new objects to the game (e.g., a new goodie or fungus).
4. It must update the status text on the top of the screen with the latest information
(e.g., the user�s current score, the number of foods Socrates has, the current level,
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



    list<Actor*>::iterator actorsIt;

    for (actorsIt = m_actors.begin(); actorsIt != m_actors.end(); ) // notice: no it++
    {
        if ((*actorsIt)->isDead()) //check if dead
        {
            delete* actorsIt; //if so, delete
            actorsIt = m_actors.erase(actorsIt); //erase object in list and return next in list 
            std::cerr << "killed something" << endl;
            continue;
        }
        (*actorsIt)->doSomething(); //call all doSomething for actors
        actorsIt++; // otherwise go to next pointer in list
    }

    m_socrates->doSomething(); //must be after all object's doSomething()!!!

    addFungus();
    addGoodies();

    list<Actor*>::iterator actorsIt;

    for (actorsIt = m_actors.begin(); actorsIt != m_actors.end(); ) // notice: no it++
    {
        (*actorsIt)->doSomething(); //call all doSomething for actors
        if ((*actorsIt)->isDead()) //check if dead
        {
            delete* actorsIt; //if so, delete
            actorsIt = m_actors.erase(actorsIt); //erase object in list and return next in list 
            std::cerr << "killed something" << endl;
        }
        else actorsIt++; // otherwise go to next pointer in list
    }

    int input;

    getKey(input);

    if (input == KEY_PRESS_DOWN)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    else
        return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator actorsIt;

    for (actorsIt = m_actors.begin(); actorsIt != m_actors.end(); ) // notice: no it++
    {
        delete *actorsIt;
        actorsIt = m_actors.erase(actorsIt);
    }

    cerr << "cleanUp ran" << endl;
}

void StudentWorld::addPits()
{



    /*
    2. Add L pits to the Petri dish at random locations, in a manner such that no two pits
overlap with each other (their centers are at least 2*SPRITE_RADIUS pixels
apart from each other). Each pit must be no more 120 pixels from the center of the
Petri dish which is at (VIEW_WIDTH/2, VIEW_HEIGHT/2).
    */
}

void StudentWorld::addFood()
{



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

        if (distApart(xPos, yPos) > 120.0) //gets random number within dist
            continue;

        m_actors.push_back(new DirtPile(this, xPos, yPos));
        numDirt++;
        m_numActors++;
    }
    cout << "DIRT: " << numDirt << endl;

    /*
    4. Add max(180 � 20 * L, 20) dirt objects to the Petri dish at random locations, in a
manner such that no dirt objects overlap with previously-placed food objects
or pits (their centers are at least 2*SPRITE_RADIUS pixels apart from each
other). It is OK for dirt objects to overlap with each other, however. Each dirt
object must be no more 120 pixels from the center of the Petri dish which is at
(VIEW_WIDTH/2, VIEW_HEIGHT/2)
*/

}

double StudentWorld::distApart(int x1, int y1, int x2, int y2) const //returns the dist between passed coords or center
{
    int xDist = abs(x1 - x2);
    int yDist = abs(y1 - y2);

    double absDist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    return absDist;
}


<<<<<<< HEAD
bool StudentWorld::overlap(Actor* a1, int overlapDist)
=======
bool StudentWorld::overlap(Actor* a1)
>>>>>>> master
{
    list<Actor*>::iterator it;
    it = m_actors.begin();

<<<<<<< HEAD
    //if no arguments, use overlap on socrates
    if (a1 == nullptr)
        a1 = m_socrates;

    int k = 0;

    while (it != m_actors.end()) // notice: no it++
    {
        if (a1 != *it && distApart(a1->getX(), a1->getY(), (*it)->getX(), (*it)->getY()) <= overlapDist)
        {
            m_overlapActorIt = it;
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

bool StudentWorld::dirtOverlap(Actor* p)
{
    if (true);

    return true;
}

bool StudentWorld::projectileOverlap(Projectile* p)
{
    if (overlap(p) && (*m_overlapActorIt)->destructible())
    {
        (*m_overlapActorIt)->takeDamage(p->damageGiven());
        return true;
    }
    return false;
}

bool StudentWorld::bacteriaOverlap(Bacteria* b)
{
    if (true);

    return true;
}

void StudentWorld::addFungus()
{
    int chanceFungus = max(510 - getLevel() * 10, 200);
    bool spawnFungus = randInt(0, chanceFungus);

   if (!spawnFungus) //HAVEN"T DONE TIMER FOR DEATH OF FUNGUS
    {
        int x = 0;
        int y = 0;
        int theta = randInt(0, 369);
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

   if (!spawnGoodie) //HAVEN"T DONE TIMER FOR DEATH OF GOODIE
    {

        int x = 0;
        int y = 0;
        int theta = randInt(0, 369);
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
=======
    while (it != m_actors.end()) // notice: no it++
    {
        if (distApart(a1->getX(), a1->getY(), (*it)->getX(), (*it)->getY()) <= SPRITE_WIDTH)
            return true;
        it++;
    }
    return false;


}


>>>>>>> master
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

getScore() can be used to determine Socrates�s current score.

increaseScore() is used by a StudentWorld object (or your other classes) to increase or
decrease the user�s score upon successfully destroying a bacterium, picking up a goodie
of some sort or getting injured by a fungus. When your code calls this method, you must
specify how many points the user gets (e.g., 100 points for destroying a salmonella, -50
points if a human steps onto a fungus). This means that the game score is controlled by
our GameWorld object � you must not maintain your own score data member in your
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
which you will use as the base class for your StudentWorld class. Here�s how this method
might be used:
 // if a salmonella dies, make a dying sound
 if (theSalmonellaHasDied())
 studentWorldObject->playSound(SOUND_SALMONELLA_DIE);
    */