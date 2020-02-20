#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//	WHATS IN A GRAPHOBJECT??? THIS:
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

class StudentWorld;

class Actor : public GraphObject
{
public:

	Actor(StudentWorld* world, int imageID, double startX, double startY, 
		Direction dir = 0, int depth = 1, double size = 1.0) 
		: GraphObject(imageID, startX, startY, dir, depth, size) 
	{
		m_studentWorld = world;
		m_dead = false;
	}

	//all depths are 1 EXCEPT socrates and bacteria//

	//reference to studentWorld for actors

	StudentWorld* getWorld() { return  m_studentWorld; }

	virtual void doSomething() = 0;

	virtual void takeDamage(int damage = 0) = 0;

	virtual void setDead()
	{
		m_dead = true;
	}

	virtual bool isDead() const
	{
		return m_dead;
	}

	virtual int damageToPlayer()
	{
		return 0;
	}

	void polarToCartesian(int& x, int& y, int theta, int r = VIEW_RADIUS);

private:
	bool m_dead;
	StudentWorld* m_studentWorld;
};
////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////SOCRATES CLASS DECLARATION/////////////////
////////////////////////////////////////////////////////////

class Socrates : public Actor
{
public:

	Socrates(StudentWorld* world)
		: Actor(world, IID_PLAYER, 0, 128, 0, 0) //ImageID:Player x:0, y:128, dir: 0, depth:0
	{
		//setHealth(100);
		
		m_health = 100;
		m_sprayCharge = 20;
		m_rechargeDelay = false;
		m_flameCharge = 5;
		setTheta();
	}

	// A NOTE ABOUT DEPTH:
	//In Kontagion, all bacteria AND Socrates are at DEPTH 0, and ALL OTHER GAME ACTORS are at DEPTH
	//	1, ensuring our active characters are in the foreground.

	virtual void doSomething();

	virtual void takeDamage(int damage)
	{
		m_health -= damage;
	}

	//Might remove??
	/*int getHealth() const
	{
		return m_health;
	}
	*/

	//Might remove?? (set health function)
	/*void setHealth(int health)
	{
		m_health = health;
	}*/

	virtual bool isDead() const
	{
		if (m_health == 0)
			return true;
		return false;
	}

	void setTheta();

	int getTheta() const
	{
		return m_theta;
	}

	void printStats(int x, int y);

private:

	int m_health;

	int m_theta;

	Direction m_direction;
	int m_sprayCharge;
	bool m_rechargeDelay;
	int m_flameCharge;

	int m_counter = 0;

};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////DIRTPILE CLASS DECLARATION/////////////////
////////////////////////////////////////////////////////////

class DirtPile :
	public Actor
{
public:

	DirtPile(StudentWorld* world, double startX, double startY, Direction dir = 0)
		: Actor(world, IID_DIRT, startX, startY, dir, 1) //ImageID: Spray, ..., dir:0, depth:1
	{

	}

	virtual void takeDamage(int damage = 0)
	{
		setDead();
	}

	virtual void doSomething();

private:

};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////SPRAY CLASS DECLARATION////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/////////////////PROJECTILE BASE CLASS DECLARATION//////////
////////////////////////////////////////////////////////////

class Projectile : public Actor
{
public:
	Projectile(StudentWorld* world, int ImageID,  double startX, double startY, int dir, int range)
		: Actor(world, ImageID, startX, startY, dir) // depth:0
	{
		m_range = range; //max pixels a projectile will travel
		m_travelled = 0; //distance travelled
	}

	void move();

	virtual bool isDead() const
	{
		if (m_travelled < m_range)
			return false;
		return true;
	}


	virtual void doSomething()
	{
		move();
	}

	virtual void takeDamage(int damage = 0){}

private:
	int m_travelled;
	int m_range;
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////

class Spray : public Projectile
{
public:
	Spray(StudentWorld* world, double startX, double startY, int dir, int range = 112)
		: Projectile(world, IID_SPRAY, startX, startY, dir, range) //ImageID: Spray, ..., range: 112
	{}


	//virtual void doSomething();
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////FLAME CLASS DECLARATION////////////////////
////////////////////////////////////////////////////////////

class Flame : public Projectile
{
public:
	Flame(StudentWorld* world, double startX, double startY, int dir, int range = 32)
		: Projectile(world, IID_FLAME, startX, startY, dir, range) //ImageID: Flame, ..., range: 32
	{}

	//virtual void doSomething();
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////PIT CLASS DECLARATION//////////////////////
////////////////////////////////////////////////////////////

class Pit : public Actor
{
public:
	Pit(StudentWorld* world, double startX, double startY, int dir)
		: Actor(world, IID_SPRAY, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething();
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////BACTERIA CLASS DECLARATION/////////////////
////////////////////////////////////////////////////////////

class Bacteria : public Actor
{
public:
	Bacteria(StudentWorld* world, int imageID, double startX, double startY, int dir, int health, int playerdamage)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{
		m_bacteriaHp = health;
		m_foodEaten = 0;
		m_damageDoes = playerdamage;
	}

	virtual int damageToPlayer()
	{
		return m_damageDoes;
	}

	virtual bool isDead() const
	{
		if (m_bacteriaHp <= 0)
			return true;
		return false;
	}

	virtual int foodEaten() const
	{
		return m_foodEaten;
	}

	virtual void eat()
	{
		m_bacteriaHp++;
	}

	virtual void resetEaten()
	{
		m_foodEaten = 0;
	}

	virtual void takeDamage(int damage)
	{
		m_bacteriaHp -= damage;
	}

	virtual void eatMitosis() = 0;

	virtual void doSomething() = 0;
private:
	int m_bacteriaHp;
	int m_foodEaten;
	int m_damageDoes;
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////SALMONELLA CLASS DECLARATION///////////////
////////////////////////////////////////////////////////////

class Salmonella : public Bacteria
{
public:
	Salmonella(StudentWorld* world, double startX, double startY, int dir = 90)
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 4, 1) //ImageID: Spray, ..., hp: 4, damage: 1
	{

	}

	virtual void doSomething();

	virtual void eatMitosis();

private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////AGGRO_SALMONELLA CLASS DECLARATION/////////
////////////////////////////////////////////////////////////

class AggroSalmonella : public Bacteria
{
public:
	AggroSalmonella(StudentWorld* world, double startX, double startY, int dir)
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 10, 2) //ImageID: Spray, ..., health :10, playerdamage: 2
	{

	}

	virtual void doSomething();

	virtual void eatMitosis();
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////ECOLI CLASS DECLARATION////////////////////
////////////////////////////////////////////////////////////

class EColi : public Bacteria
{
public:
	EColi(StudentWorld* world, double startX, double startY, int dir)
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 5, 4) //ImageID: EColi, ..., health: 5, playerdamage: 4
	{

	}

	virtual void doSomething();

	virtual void eatMitosis();
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////CONSUMABLE CLASS DECLARATION///////////////
////////////////////////////////////////////////////////////

class Consumable : public Actor
{
public:
	Consumable(StudentWorld* world, int imageID, double startX, double startY, int dir = 0)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{ 
		setMaxAge();
		m_ticksAlive = 0;
	}

	virtual void incTicksAlive()
	{
		m_ticksAlive++;
	}

	virtual bool isDead() const
	{
		if (m_ticksAlive >= m_maxAge)
			return true;
		return false;
	}

	void setMaxAge();

	virtual void doSomething() = 0;

	virtual void takeDamage(int damage = 0) { setDead(); };

private:
	int m_ticksAlive;
	int m_maxAge;
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////FOOD CLASS DECLARATION/////////////////////
////////////////////////////////////////////////////////////

class Food : public Consumable
{
public:
	Food(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_FOOD, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}

	virtual void doSomething() = 0;
private:

};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////FLAMEG CLASS DECLARATION///////////////////
////////////////////////////////////////////////////////////

class FlameG : public Consumable
{
public:
	FlameG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_FLAME_THROWER_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{}

	virtual void doSomething() {};
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////HEALTHG CLASS DECLARATION//////////////////
////////////////////////////////////////////////////////////

class HealthG : public Consumable
{
public:
	HealthG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_RESTORE_HEALTH_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() {};
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////LIFEG CLASS DECLARATION////////////////////
////////////////////////////////////////////////////////////

class LifeG : public Consumable
{
public:
	LifeG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_EXTRA_LIFE_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() {};
private:
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/////////////////FUNGUS CLASS DECLARATION///////////////////
////////////////////////////////////////////////////////////

class Fungus : public Consumable
{
public:
	Fungus(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_FUNGUS, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() {};
private:
};

#endif // ACTOR_H_
