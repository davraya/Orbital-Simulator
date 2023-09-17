#include <cmath>
#include "Acceleration.h"
#include "position.h"

void Acceleration::computeDdx()
{
    ddx = gravity * sin(angle);
}

void Acceleration::computeDdy()
{
    ddy = gravity * cos(angle);
}

void Acceleration::computeNewAcceleration(Position* p)
{
    double h = computeHeight(p);
    gravity = computeGh(h);
    angle = atan2(p->getMetersX(), p->getMetersY());

    computeDdx();
    computeDdy();
}

double Acceleration::computeHeight(Position* p)
{
    return sqrt((p->getMetersX() * p->getMetersX()) + (p->getMetersY() * p->getMetersY())) - EARTH_RADIUS;
}

double Acceleration::computeGh(double h)
{
    return GRAVITY * (EARTH_RADIUS / (EARTH_RADIUS + h)) * (EARTH_RADIUS / (EARTH_RADIUS + h));
}