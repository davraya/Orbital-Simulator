#include "OribtalObject.h"
#include "position.h"
#include "Acceleration.h"
#include "Velocity.h"
#include <cmath>
#include <iostream>

using namespace std;

/***
 * Updates the OrbitalObject's acceleration, velocity, and position
*/
void OrbitalObject::update()
{
	acceleration->computeNewAcceleration(position);
	velocity->computeNewVelocity(acceleration);
	position->computeNewPostion(velocity, acceleration);
}

bool OrbitalObject::checkCollision(OrbitalObject* other)
{
	double distanceX = other->position->getPixelsX() - position->getPixelsX();
	double distanceY = other->position->getPixelsY() - position->getPixelsY();
	double distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= other->radius + radius)
		return true;

	return false;
}

double OrbitalObject::computeHeight()
{
	return sqrt((position->getMetersX() * position->getMetersX()) + (position->getMetersY() * position->getMetersY())) - EARTH_RADIUS;
}

double OrbitalObject::computeGh(double h)
{
	return GRAVITY * (EARTH_RADIUS / (EARTH_RADIUS + h)) * (EARTH_RADIUS / (EARTH_RADIUS + h));
}