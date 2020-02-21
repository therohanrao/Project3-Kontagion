#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

const double PI = 4 * atan(1);

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

            printStats(x, y);

            break;

        case KEY_PRESS_RIGHT: //clockwise movement

            setDirection(getDirection() - 5);
            setTheta();
            polarToCartesian(x, y, m_theta);
            x += VIEW_WIDTH / 2;
            y += VIEW_HEIGHT / 2;
            moveTo(x, y);
            m_counter++;

            printStats(x, y);

            break;

        case KEY_PRESS_SPACE:
            if (m_sprayCharge >= 1)
            {
                getPositionInThisDirection(getDirection(), SPRITE_WIDTH, dx, dy);
                printStats(x, y);
                std::cerr << dx << " " << dy << std::endl;;
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
    if (getWorld()->projectileOverlap(this))
    {
        setDead();
        return true;
    }
    return false;
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

}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////


void Salmonella::doSomething()
{

}

void Salmonella::eatMitosis()
{
    if (foodEaten() >= 3)
    {
        Salmonella* s = nullptr;
        getWorld()->addNewActor(s, getWorld(), getX(), getY(), getDirection());
        resetEaten();
    }
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

}

void AggroSalmonella::eatMitosis()
{
    if (foodEaten() >= 3)
    {
        AggroSalmonella* aS = nullptr;
        getWorld()->addNewActor(aS, getWorld(), getX(), getY(), getDirection());
        resetEaten();
    }
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

}

void EColi::eatMitosis()
{
    if (foodEaten() >= 3)
    {
        EColi* eC = nullptr;
        getWorld()->addNewActor(eC, getWorld(), getX(), getY(), getDirection());
        resetEaten();
    }
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
/////////////////DIRTPILE CLASS IMPLEMENTATION//////////////
////////////////////////////////////////////////////////////
void Consumable::setMaxAge()
{
    m_maxAge = std::max(randInt(0, 300 - (10 * getWorld()->getLevel()) - 1), 50);
}

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////