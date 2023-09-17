/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich, Sam Cummings, David Raya
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include <cassert>
#include "Velocity.h"
#include "Acceleration.h"

#define T 48


Position::Position(double x, double y) : x(0.0), y(0.0)
{
	setMetersX(x);
	setMetersY(y);
}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point
 *****************************************/
Position& Position::operator = (const Position& pt)
{
	x = pt.x;
	y = pt.y;
	return *this;
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
	out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
	return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pt)
{
	double x;
	double y;
	in >> x >> y;

	pt.setMetersX(x);
	pt.setMetersY(y);

	return in;
}

void Position::computeNewPostion(Velocity* vel, Acceleration* acc)
{
	computeX(vel->getDx(), acc->getDdx(), T / 2);
	computeY(vel->getDy(), acc->getDdy(), T / 2);
}

void Position::computeX(double dx, double ddx, double t)
{
	x = x + dx * t + 0.5 * ddx * t * t;
}

void Position::computeY(double dy, double ddy, double t)
{
	y = y + dy * t + 0.5 * ddy * t * t;
}
