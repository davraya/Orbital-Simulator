#pragma once

#include "Acceleration.h"
#include <list>

#define EARTH_RADIUS 6378000
#define GRAVITY -9.8067
#define T 48

class Position;
class Velocity;
class ogstream;

class OrbitalObject
{
public:
	OrbitalObject() {}
	OrbitalObject(Position* pos, Velocity* vel, double r) : position{ pos }, velocity{ vel }, radius{ r } { this->acceleration = new Acceleration(0.0, 0.0); }
	void virtual update();
	bool checkCollision(OrbitalObject* other);
	bool isDead;
	void virtual draw(ogstream* gout) = 0;
	void virtual breakUp(std::list<OrbitalObject*>* orbitalObjects) = 0;
	Position* const getPosition() { return position; }
	Velocity* const getVelocity() { return velocity; }
	double getRadius() { return radius; }
protected:
	Position* position;
	Velocity* velocity;
	Acceleration* acceleration;
	double radius;
	double angle;
	double computeHeight();
	double computeGh(double h);	
};