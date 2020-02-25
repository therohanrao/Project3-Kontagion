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

	//pure virtual??
	virtual bool overlap() 
	{ 
		std::cerr << " shouldnt be running this: actor::overlap()" << std::endl;
			return true; 
	} // make pure virtual

	virtual int damageToPlayer()
	{
		return 0;
	}
	virtual void takeDamage(int damage = 0) = 0;
	virtual void setDead()
	{
		m_dead = true;
	}
	virtual bool isDead() const
	{
		return m_dead;
	}

	//set false for food
	virtual bool destructible()
	{
		return true;
	}
	virtual bool consumable()
	{
		return false;
	}


<<<<<<< HEAD
=======
	virtual void setDead(bool state);
	virtual bool isDead() const = 0;

	//virtual bool canHurt();



>>>>>>> master
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

		std::cerr << m_health << std::endl;
		std::cerr << damage << std::endl;
		m_health -= damage;
	}

	virtual bool destructible() { return false; }

	virtual bool overlap();

	//Might remove?? (get health function)
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
		if (m_health <= 0)
		{
			return true;
		}
		return false;
	}

	void incFlame()
	{
		m_flameCharge += 5;
	}

	void restoreHealth() 
	{ 
		m_health = 100;
	}

	void incLife();

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

<<<<<<< HEAD
	virtual void takeDamage(int damage = 0)
	{
		std::cerr << "dirt killed" << std::endl;
		setDead();
	}

	virtual bool overlap();

=======
	virtual bool isDead() const
	{
		return false;
	}

>>>>>>> master
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
<<<<<<< HEAD
{
public:
	Projectile(StudentWorld* world, int ImageID,  double startX, double startY, int dir, int range, int damage)
		: Actor(world, ImageID, startX, startY, dir) // depth:0
	{
		m_range = range; //max pixels a projectile will travel
		m_travelled = 0; //distance travelled
		m_strength = damage;
	}

	void move();
	
	int damageGiven() { return m_strength; }

	virtual bool destructible() { return false; }

	virtual void setDead()
	{
		Actor::setDead();
		m_travelled = m_range;
	}

	virtual bool isDead() const
	{
		if (m_travelled < m_range)
			return false;
		return true;
	}

	virtual void doSomething()
	{
		overlap();
		move();
	}

	virtual void takeDamage(int damage = 0){}

private:

	virtual bool overlap();

	int m_travelled;
	int m_range;
	int m_strength;
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////

class Spray : public Projectile
{
public:
	Spray(StudentWorld* world, double startX, double startY, int dir, int range = 112, int damage = 2)
		: Projectile(world, IID_SPRAY, startX, startY, dir, range, damage) //ImageID: Spray, ..., range: 112
=======
{
public:
	Projectile(StudentWorld* world, int ImageID,  double startX, double startY, int dir, int range)
		: Actor(world, ImageID, startX, startY, dir) // depth:0
	{
		m_distanceLeft = range; //max pixels a projectile will travel
	}

	void move();

	virtual bool isDead() const
	{
		if (m_distanceLeft > 0)
			return false;
		return true;
	}

	virtual void doSomething()
	{
		move();
	}
private:
	int m_distanceLeft;
};

////////////////////////////////////////////////////////////
/////////////////END DECLARATION////////////////////////////
////////////////////////////////////////////////////////////

class Spray : public Projectile
{
public:
	Spray(StudentWorld* world, double startX, double startY, int dir, int range = 112)
		: Projectile(world, IID_SPRAY, startX, startY, dir, range) //ImageID: Spray, ..., range: 112
>>>>>>> master
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
<<<<<<< HEAD
	Flame(StudentWorld* world, double startX, double startY, int dir, int range = 32, int damage = 5)
		: Projectile(world, IID_FLAME, startX, startY, dir, range, damage) //ImageID: Flame, ..., range: 32
	{}

=======
	Flame(StudentWorld* world, double startX, double startY, int dir, int range = 32)
		: Projectile(world, IID_FLAME, startX, startY, dir, range) //ImageID: Flame, ..., range: 32
	{}

	//virtual void doSomething();
>>>>>>> master
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
<<<<<<< HEAD
	Pit(StudentWorld* world, double startX, double startY, int dir = 0)
		: Actor(world, IID_SPRAY, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{
		m_numSal = 5;
		m_numASal = 3;
		m_numEColi = 2;
	}

	virtual bool isDead()
	{
		if (m_numSal + m_numASal + m_numEColi == 0)
			return true;
		return false;
	}

	virtual void takeDamage(int damage = 0) {};

	bool spawnBacteria();

	virtual void doSomething();
private:
	int m_numSal;
	int m_numASal;
	int m_numEColi;
=======
	Pit(StudentWorld* world, double startX, double startY, int dir)
		: Actor(world, IID_SPRAY, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething();
private:
>>>>>>> master
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
<<<<<<< HEAD
	Bacteria(StudentWorld* world, int imageID, double startX, double startY, int dir, int health, int playerdamage)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{
		m_movePlanDist = 0;
		m_bacteriaHp = health;
		m_damageDoes = playerdamage;
		m_foodEaten = 0;
		m_blocked = false;
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

	virtual void takeDamage(int damage)
	{
		m_bacteriaHp -= damage;
	}

	virtual bool overlap();

	virtual void eatMitosis() = 0;

	virtual void doSomething() = 0;


	//Movement Plan functions:
	virtual int getMovePlanDist()
	{
		return m_movePlanDist;
	}
	virtual void decMovePlan()
	{
		m_movePlanDist--;
	}
	virtual void resetMovePlan()
	{
		std::cerr << "MOVE PLAN RESET " << std::endl;
		m_movePlanDist = 10;
	}

	virtual void dirtBlocked(bool blocked)
	{
		m_blocked = blocked;
	}
	virtual bool getBlocked() const
	{
		return m_blocked;
	}

	//Food functions:
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
private:

	bool m_blocked;

	int m_movePlanDist;
	int m_bacteriaHp;
	int m_foodEaten;
	int m_damageDoes;
=======
	Bacteria(StudentWorld* world, int imageID, double startX, double startY, int dir)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() = 0;
private:
>>>>>>> master
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
<<<<<<< HEAD
	Salmonella(StudentWorld* world, double startX, double startY, int dir = 90)
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 4, 1) //ImageID: Spray, ..., hp: 4, damage: 1
=======
	Salmonella(StudentWorld* world, double startX, double startY, int dir)
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir) //ImageID: Spray, ..., depth:0
>>>>>>> master
	{

	}

<<<<<<< HEAD
	virtual void doSomething();

	virtual void eatMitosis();

=======


	virtual void doSomething();
>>>>>>> master
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
<<<<<<< HEAD
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 10, 2) //ImageID: Spray, ..., health :10, playerdamage: 2
	{

	}

	virtual void doSomething();

	virtual void eatMitosis();
=======
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething();
>>>>>>> master
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
<<<<<<< HEAD
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir, 5, 4) //ImageID: EColi, ..., health: 5, playerdamage: 4
	{

	}

	virtual void doSomething();

	virtual void eatMitosis();
=======
		: Bacteria(world, IID_SALMONELLA, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething();
>>>>>>> master
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
<<<<<<< HEAD
	Consumable(StudentWorld* world, int imageID, double startX, double startY, int dir = 0)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:
	{ 
		setMaxAge();
		m_ticksAlive = 0;
	}

	virtual bool consumable()
	{
		return true;
	}

	virtual void incTicksAlive()
	{
		m_ticksAlive++;
	}

	virtual bool isDead() const
	{
		if (Actor::isDead())
			return true;
		if (m_ticksAlive >= m_maxAge)
		{
			std::cerr << "fungus killed" << std::endl;
			return true;
		}
		return false;
	}

	virtual bool overlap();

	virtual void applyEffect(Socrates* s) = 0;

	virtual void doSomething();

	virtual void takeDamage(int damage = 0) { setDead(); };

private:
	void setMaxAge();

	int m_ticksAlive;
	int m_maxAge;
=======
	Consumable(StudentWorld* world, int imageID, double startX, double startY, int dir)
		: Actor(world, imageID, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() = 0;
private:
>>>>>>> master
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
<<<<<<< HEAD
	Food(StudentWorld* world, double startX, double startY, double dir = 0)
=======
	Food(StudentWorld* world, double startX, double startY, int dir)
>>>>>>> master
		: Consumable(world, IID_FOOD, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}

<<<<<<< HEAD
	virtual void applyEffect(Socrates* s);

	virtual bool isDead() const
	{
		return Actor::isDead();
	}

	virtual void takeDamage(int damage = 0) {};

	virtual bool destructible()
	{
		return false;
	}

private:
=======
>>>>>>> master


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
<<<<<<< HEAD
	FlameG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_FLAME_THROWER_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{}

	virtual void applyEffect(Socrates* s);
=======
	FlameG(StudentWorld* world, double startX, double startY, int dir)
		: Consumable(world, IID_FLAME_THROWER_GOODIE, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() = 0;
>>>>>>> master
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
<<<<<<< HEAD
	HealthG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_RESTORE_HEALTH_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}

	void applyEffect(Socrates* s);

=======
	HealthG(StudentWorld* world, double startX, double startY, int dir)
		: Consumable(world, IID_RESTORE_HEALTH_GOODIE, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() = 0;
>>>>>>> master
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
<<<<<<< HEAD
	LifeG(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_EXTRA_LIFE_GOODIE, startX, startY) //ImageID: Spray, ..., depth:0
	{

	}

	void applyEffect(Socrates* s);

=======
	LifeG(StudentWorld* world, double startX, double startY, int dir)
		: Consumable(world, IID_EXTRA_LIFE_GOODIE, startX, startY, dir) //ImageID: Spray, ..., depth:0
	{

	}



	virtual void doSomething() = 0;
>>>>>>> master
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
<<<<<<< HEAD
	Fungus(StudentWorld* world, double startX, double startY)
		: Consumable(world, IID_FUNGUS, startX, startY) //ImageID: Spray, ..., depth:0
=======
	Fungus(StudentWorld* world, double startX, double startY, int dir)
		: Consumable(world, IID_FUNGUS, startX, startY, dir) //ImageID: Spray, ..., depth:0
>>>>>>> master
	{

	}

<<<<<<< HEAD
	virtual int damageToPlayer()
	{
		return 25;
	}

	void applyEffect(Socrates* s);

=======


	virtual void doSomething() = 0;
>>>>>>> master
private:
};

#endif // ACTOR_H_
