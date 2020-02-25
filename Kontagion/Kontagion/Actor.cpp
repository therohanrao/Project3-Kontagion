#include "Actor.h"
#include "StudentWorld.h"

using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*void Actor::activate()
{

}*/

/*void Actor::setDead(bool state)
{
	m_dead = state;
}*/

/*bool Actor::isDead() const
{
	if (m_dead)
		return true;
	return false;
}*/

void Actor::polarToCartesian(int& x, int& y, int theta, int r)
{
    double rad = theta * (PI / 180);
    x = r * (cos(rad));
    y = r * (sin(rad));
}



////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////SOCRATES CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////

void Socrates::doSomething()
{
    /*
    class Socrates: public …
 {
 public:
 virtual void doSomething()
 {
 Try to get user input (if any is available)
 If the user pressed the LEFT key then
 Move counterclockwise around the perimeter by 5 degrees
 If the user pressed the RIGHT key then
Move clockwise around the perimeter by 5 degrees
 ...
 If the user pressed space and Socrates has Sprays left, then
Introduce a new Spray object into the Petri dish in front
 of Socrates
 ...
 }
 ...
 };
    */

    /*
    void Socrates::doSomething()
{
 ...
 int ch;
 if (getAPointerToMyStudentWorld()->getKey(ch))
 {
 // user hit a key during this tick!
 switch (ch)
 {
 case KEY_PRESS_LEFT:
 ... move Socrates counterclockwise ...;
 break;
 case KEY_PRESS_RIGHT:
 ... move Socrates clockwise...;
 break;
 case KEY_PRESS_SPACE:
 ... add spray in front of Socrates...;
 break;
 // etc…
 }
 }
 ...
}
    */

    //WHATS IN A GRAPHOBJECT ? ? ? THIS :
    /*
GraphObject(int imageID, double startX, double startY,
int startDirection = 0, int depth = 0);

double getX() const; // in pixels (0-255)
double getY() const; // in pixels (0-255)
void moveTo(double x, double y); // in pixels (0-255)
23

// moveAngle() moves the actor the specified number of units in the
// specified direction.

void moveAngle(Direction angle, int units = 1);

// getPositionInThisDirection() returns a new (x, y) location in the
// specified direction and distance, based on the passed-in angle and the
// GraphObject’s current (x, y) location.

void getPositionInThisDirection(Direction angle, int units,
 double &dx, double &dy);

int getDirection() const; // in degrees (0-359)

void setDirection(Direction d); // in degrees (0-359)
*/

    overlap();

    int ch = 0;
    if (getWorld()->getKey(ch))
    {
        int x = 0;
        double dx = 0;
        int y = 0;
        double dy = 0;

        Spray* spray = nullptr;
        Flame* flame = nullptr;
        switch (ch)
        {

        case KEY_PRESS_LEFT: //anti-clockwise movement

            setDirection(getDirection() + 5);
            setTheta();
            polarToCartesian(x, y, m_theta);
            x += VIEW_WIDTH / 2;
            y += VIEW_HEIGHT / 2;
            moveTo(x, y);
            m_counter--;

            //printStats(x, y);

            break;

        case KEY_PRESS_RIGHT: //clockwise movement

            setDirection(getDirection() - 5);
            setTheta();
            polarToCartesian(x, y, m_theta);
            x += VIEW_WIDTH / 2;
            y += VIEW_HEIGHT / 2;
            moveTo(x, y);
            m_counter++;

            //printStats(x, y);

            break;

        case KEY_PRESS_SPACE:
            if (m_sprayCharge >= 1)
            {
                getPositionInThisDirection(getDirection(), SPRITE_WIDTH, dx, dy);
                //printStats(x, y);
                //std::cerr << dx << " " << dy << std::endl;;
                getWorld()->addNewActor(spray, getWorld(), dx, dy, getDirection());
                getWorld()->playSound(SOUND_PLAYER_SPRAY);
                m_sprayCharge--;
            }
            break;

        case KEY_PRESS_ENTER:
            if (m_flameCharge >= 1)
            {
                for (int i = 0; i < 338; i += 22)
                {
                    getPositionInThisDirection(getDirection() + i, SPRITE_WIDTH, dx, dy);
                    getWorld()->addNewActor(flame, getWorld(), dx, dy, getDirection() + i);
                }
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                //m_flameCharge--; UNCOMMENT THIS LATER!!!!!
            }
            break;

        default:
            break;
        }
    }
    else if (m_sprayCharge < 20)
        m_sprayCharge++;

    //std::cerr << "SprayCharge: " << m_sprayCharge << std::endl << std::endl;
}

void Socrates::takeDamage(int damage)
{
    std::cerr << m_health << std::endl;
    std::cerr << damage << std::endl;
    m_health -= damage;
}

bool Socrates::overlap()
{
    return getWorld()->playerOverlap();
}

void Socrates::incLife()
{
    getWorld()->incLives();
}

void Socrates::setTheta()
{
    int dir = getDirection();

    if (dir < 180)
        m_theta = 180 + dir;
    else if (dir < 359)
        m_theta = dir - 180;
    else
        std::cerr << "INVALID DIR SET" << std::endl;
}

void Socrates::printStats(int x, int y)
{
    std::cerr << "DIR" << getDirection() << std::endl;
    std::cerr << "THETA: " << m_theta << std::endl;
    std::cerr << "X: " << x << std::endl;
    std::cerr << "Y: " << y << std::endl;
    std::cerr << "Counter: " << m_counter << std::endl;
}
////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////

void DirtPile::doSomething()
{

}

bool DirtPile::overlap()
{
    if (getWorld()->dirtOverlap(this))
        setDead();
    return true;
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////PROJECTILE CLASS IMPLEMENTATION////////////
////////////////////////////////////////////////////////////

void Projectile::move()
{
    if (m_travelled < m_range)
    {
        moveAngle(getDirection(), SPRITE_WIDTH);
        m_travelled += SPRITE_WIDTH;
    }

    //std::cerr << "distLeft: " << m_distanceLeft << std::endl;
}

bool Projectile::overlap()
{
    return getWorld()->projectileOverlap(this);
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////SPRAY CLASS IMPLEMENTATION/////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////FLAME CLASS IMPLEMENTATION/////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////


void Pit::doSomething()
{
    if (spawnBacteria())
        getWorld()->playSound(SOUND_BACTERIUM_BORN);
}

bool Pit::spawnBacteria()
{
    /*
    Otherwise, there is a 1 in 50 chance that during a tick, a given pit will emit a
bacterium. Assuming the current tick was chosen to emit bacteria into the Petri
dish:
a. Considering only the types of bacteria that is has not yet run out of, the pit
must randomly select one of those types (each type being equally likely to be
chosen).
b. It must create a new bacterium object of the chosen type (regular salmonella,
aggressive salmonella or E. coli) with an (x ,y) coordinate that is the same as
the pit’s (x ,y) coordinate.
c. It must add that new bacterium to the StudentWorld object.
d. It must decrement the count of bacteria of the chosen type that it has left in its
inventory.
e. It (or some other object) must play a sound effect to indicate that the
bacterium was just born: SOUND_BACTERIUM_BORN.
    */

    if (m_numSal + m_numASal + m_numEColi <= 0)
    {
        setDead();
        return false;
    }

    int spawnBacteria = randInt(0, 49);

    const int SAL = 1;
    const int ASAL = 2;
    const int EC = 3;

    Salmonella* sal = nullptr;
    AggroSalmonella* asal = nullptr;
    EColi* ec = nullptr;

    if (!spawnBacteria)
    {
        int bacteria = 0;
        for (;;)
        {
            bacteria = randInt(1, 3);
            switch (bacteria)
            {
            case SAL:
                if (m_numSal)
                {
                    getWorld()->addNewActor(sal, getWorld(), getX(), getY(), 90);
                    m_numSal--;
                    return true;
                }
                break;
            case ASAL:
                if (m_numASal)
                {
                    getWorld()->addNewActor(asal, getWorld(), getX(), getY(), 90);
                    m_numASal--;
                    return true;
                }
                break;
            case EC:
                if (m_numEColi)
                {
                    getWorld()->addNewActor(ec, getWorld(), getX(), getY(), 90);
                    m_numEColi;
                    return true;
                }
                break;
            }
        }
    }

    return false;
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////

bool Bacteria::overlap()
{
    return getWorld()->bacteriaOverlap(this);
}

bool Bacteria::isDead() const
{
    if (m_bacteriaHp <= 0)
    {
        return true;
    }
    return false;
}

void Bacteria::takeDamage(int damage)
{
    getWorld()->playSound(m_hurtSound);
    m_bacteriaHp -= damage;
}

///
///

void Salmonella::doSomething()
{
    if (isDead())
        return;

    //cerr << "MOVE PLAN DIST: " << getMovePlanDist() <<  endl;

    overlap();

    double newdir = -1;
    double newx = 0;
    double newy = 0;

    if (getMovePlanDist() > 0)
    {
        //cerr << "move plan > 0" << endl;
        decMovePlan();

        getPositionInThisDirection(getDirection(), 3, newx, newy);

        //if not blocked:
        if (!getBlocked() && getWorld()->distApart(newx, newy) < VIEW_RADIUS)
        {
            //cerr << "not blocked" << endl;
            moveTo(newx, newy);
        }
        else
        {
            //cerr << "blocked" << endl;
            setDirection(randInt(0, 359)); //sets new dir randomly
            resetMovePlan(); //resets movement plan to 10
        }
        return;
    }
    else if (getWorld()->findFood(this, newdir))
    {
        //cerr << "Finding food, newdir: " << newdir << endl;
        setDirection(newdir);

        overlap(); //check again if blocked by dirt

        if (!getBlocked())
        {
            //cerr << "not blocked" << endl;
            resetMovePlan();
            return;
        }
        else
        {
            //cerr << "found food but blocked" << endl;
            setDirection(randInt(0, 359));
            resetMovePlan();
            return;
        }
    }
    else
    {
        //cerr << "move plan < 0, no food" << endl;
        setDirection(randInt(0, 359));
        resetMovePlan();
        return;
    }

    /*
    The regular salmonella will check to see if it has a movement plan distance of
greater than zero. If so this means it wants to continue moving the same direction
it was previously moving in. It will do the following:
a. Decrement its movement plan distance by one.
b. It will see if it can move forward by 3 pixels in the direction it is currently
facing. The following things will block the regular salmonella from
moving forward:
i. Moving forward 3 pixels would cause the regular salmonella to
overlap with a dirt pile, where in this case, the definition of
overlap means that the Euclidean distance from the regular
salmonella’s proposed new (x, y) location to the dirt pile is <=
SPRITE_WIDTH/2 pixels.
ii. Moving forward 3 pixels would cause the regular salmonella to
move outside of the Petri dish, that is, its distance from the center
of the screen (VIEW_WIDTH/2, VIEW_HEIGHT/2) is greater
than or equal to VIEW_RADIUS.
c. If the regular salmonella can move forward 3 pixels to the new position, it
(or some base class it’s derived from) must do so using either the
GraphObject moveTo() or moveAngle() method.
d. Otherwise, if the regular salmonella is blocked from moving forward 3
pixels, it will:
i. Pick a random direction to move in, from 0 to 359 degrees, and set
its direction to that new direction.
ii. Reset its movement plan distance to 10, so it will try to move 10
ticks in this new direction.
e. The regular salmonella will immediately return.


6. Otherwise, the regular salmonella will get the directional angle to the closest food
within 128 pixels of itself on the Petri dish.
a. If no food can be found within 128 pixels, then the regular salmonella
will:
i. Pick a random direction to move in, from 0 to 359 degrees, and set
its direction to that direction.
ii. Reset its movement plan distance to 10, so it will try to move 10
ticks in this new direction.
iii. Immediately return.
b. If food can be found within 128 pixels, the regular salmonella will try to
move toward that food. If moving forward 3 pixels would cause the
regular salmonella to overlap9 with a dirt pile, then it will:
i. Pick a random direction to move in, from 0 to 359 degrees, and set
its direction to that new direction.
ii. Reset its movement plan distance to 10, so it will try to move 10
ticks in this new direction.
iii. Immediately return.
    */

}

void Salmonella::eatMitosis()
{
    Salmonella* s = nullptr;
    if (mitosis(s))
        return;
    else
        eat();
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////

void AggroSalmonella::doSomething()
{
    if (isDead())
        return;

    overlap();

    double sx = 0;
    double sy = 0;

    double newx = 0;
    double newy = 0;
    double newdir = 0;

    bool foundPlayer = false;

    getWorld()->findSocrates(sx, sy);
    if (getWorld()->distApart(getX(), getY(), sx, sy) <= 72.0) //if dist from socrates <= 72
    {
        double newdir = getWorld()->getTheta(this);
        getWorld()->radiansToDegrees(newdir);
        setDirection(newdir); //set dir in dir of socrates
        getPositionInThisDirection(newdir, 3, newx, newy); // move in dir of socrates
        getWorld()->bacteriaOnDirt(this); //check if blocked by dirt

        //cerr << "found socrates: " << endl;
        //cerr << "newdir: " << newdir << endl;
        //cerr << "newx: " << newx << endl;
        //cerr << "newy: " << newy << endl;


        if (!getBlocked())
        {
            cerr << "hunting socrates" << endl;
            moveTo(newx, newy);
        }
        foundPlayer = true; //skip later step if socrates found
    }

    if (getWorld()->bacteriaOnPlayer(this)) //damage to socrates will be taken care of by studentworld
    {
        if (foundPlayer)
            return;
    }
    else if (mitosis(this))
    {
        if (foundPlayer)
            return;
    }
    else
        getWorld()->bacteriaOnFood(this);

    if (!foundPlayer)
    {
        if (getMovePlanDist() > 0) //if movement plan > 0 ...
        {
            //cerr << "move plan > 0" << endl;
            decMovePlan(); //decrease move plan

            getPositionInThisDirection(getDirection(), 3, newx, newy);

            getWorld()->bacteriaOnDirt(this);
            //if not blocked:
            if (!getBlocked() && getWorld()->distApart(newx, newy) < VIEW_RADIUS)
            {
                //cerr << "not blocked" << endl;
                moveTo(newx, newy);
            }
            else
            {
                //cerr << "blocked" << endl;
                setDirection(randInt(0, 359)); //sets new dir randomly
                resetMovePlan(); //resets movement plan to 10
            }
            return;
        }
        else if (getWorld()->findFood(this, newdir))
        {
            //cerr << "Finding food, newdir: " << newdir << endl;
            setDirection(newdir);

            getWorld()->bacteriaOnDirt(this); //check again if blocked by dirt

            if (getBlocked())
            {
                //cerr << "found food but blocked" << endl;
                setDirection(randInt(0, 359));
                resetMovePlan();
                return;
            }

            moveAngle(getDirection(), 3);

        }
        else
        {
            //cerr << "move plan < 0, no food" << endl;
            setDirection(randInt(0, 359));
            resetMovePlan();
            return;
        }
    }
}

void AggroSalmonella::eatMitosis()
{
    AggroSalmonella* aS = nullptr;
    if (mitosis(aS))
        return;
    else
        eat();
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////


void EColi::doSomething()
{
    if (isDead())
        return;

    overlap();
}

void EColi::eatMitosis()
{
    EColi* ec = nullptr;
    if (mitosis(ec))
        return;
    else
        eat();
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////CONSUMABLES CLASS IMPLEMENTATION///////////
////////////////////////////////////////////////////////////

void Consumable::doSomething()
{
    m_ticksAlive++;
}

void Consumable::setMaxAge()
{
    m_maxAge = std::max(randInt(0, 300 - (10 * getWorld()->getLevel()) - 1), 50);
}

bool Consumable::overlap()
{
    m_ticksAlive = m_maxAge;
    return getWorld()->consumableOverlap(this);
    //always returns true;
}

void Food::applyEffect(Socrates* s)
{
    //see bacteria overlap
}

void FlameG::applyEffect(Socrates* s)
{
    s->incFlame();
}

void HealthG::applyEffect(Socrates* s)
{
    s->restoreHealth();
}

void LifeG::applyEffect(Socrates* s)
{
    s->incLife();
}

void Fungus::applyEffect(Socrates* s)
{
    s->takeDamage(damageToPlayer());
}


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////