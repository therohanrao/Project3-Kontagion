#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

const double PI = 4 * atan(1);

void Actor::activate()
{

}

void Actor::setDead(bool state)
{
	m_dead = state;
}

bool Actor::isDead() const
{
	if (m_dead)
		return true;
	return false;
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

// A NOTE ABOUT DEPTH:

In
Kontagion, all bacteria and Socrates are at depth 0, and all other game actors are at depth
1, ensuring our active characters are in the foreground.
//

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


    int ch;
    if (getWorld()->getKey(ch))
    {
        int x = 0;
        int y = 0;
        switch (ch)
        {

        case KEY_PRESS_LEFT: //anti-clockwise movement

            setDirection(getDirection() + 5);
            setTheta();
            polarToCartesian(x, y, m_theta);
            x += VIEW_WIDTH / 2;
            y += VIEW_HEIGHT / 2;
            moveTo(x, y);
            m_counter++;

            break;

        case KEY_PRESS_RIGHT: //clockwise movement

            setDirection(getDirection() - 5);
            setTheta();
            polarToCartesian(x, y, m_theta);
            x += VIEW_WIDTH / 2;
            y += VIEW_HEIGHT / 2;
            moveTo(x, y);
            m_counter--;

            break;

        case KEY_PRESS_SPACE:
            break;

        case KEY_PRESS_ENTER:
            break;

        default:
            break;
        }

        std::cout << "DIR" << getDirection() << std::endl;
        std::cout << "THETA: " << m_theta << std::endl;
        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << y << std::endl;
        std::cout << "Counter: " << m_counter << std::endl << std::endl;

    }



}

void Socrates::takeDamage()
{

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

void Socrates::polarToCartesian(int& x, int& y, int theta, int r)
{
    double rad = theta * (PI / 180);
    x = r * (cos(rad));
    y = r * (sin(rad));
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

////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////END IMPLEMENTATION/////////////////////////
////////////////////////////////////////////////////////////