#include "physics.h"
#include <cmath>
#include <iostream>
using namespace std;



Physics::Physics(double x, double y, double dx, double dy, double angle)
{
	this->x = x;;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->angle = angle;
}

void Physics::computeAll()
{
	computeHeight();
	cout << "height :" << height << endl;
	computeGH();
	cout << "gH :" << gH << endl;
	computeDdx();
	cout << "ddx :" << ddx << endl;
	computeDdy();
	cout << "ddy: " << ddy << endl;
	computeDx();
	cout << "Dx: " << dx << endl;
	computeDy();
	cout << "Dy: " << dy << endl << endl;;


	computeX();
	cout << "x: " << x << endl;
	computeY();
	cout << "y: " << y << endl;
	computeNewAngle();
	cout << "angle: " << angle << endl << endl;
}

double Physics::getX()
{
	return x;
}

double Physics::getY()
{
	return y;
}

void Physics::computeHeight()
{
	height = sqrt((x * x) + (y * y)) - earthRadious;
}

void Physics::computeGH()
{
	gH = g * (earthRadious / (earthRadious + height)) * (earthRadious / (earthRadious + height));
}

void Physics::computeDdx()
{
	ddx = gH * sin(angle);
}

void Physics::computeDdy()
{
	ddy = gH * cos(angle);
}

void Physics::computeDx()
{
	dx = dx + ddx * t;
}

void Physics::computeDy()
{
	dy = dy + ddy * t;
}

void Physics::computeX()
{
	x = x + dx * t + 0.5 * ddx * t * t;
}

void Physics::computeY()
{
	y = y + dy * t + 0.5 * ddy * t * t;
}

void Physics::computeNewAngle()
{
	//angle = asin(ddx / gH);
	angle = atan2(x, y);

}


