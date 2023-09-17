#include "Velocity.h"
#include "Acceleration.h"

#define T 48

void Velocity::computeNewVelocity(Acceleration* acc)
{
   computeDx(acc->getDdx(), T / 2);
   computeDy(acc->getDdy(), T / 2);
}

void Velocity::computeDx(double ddx, double t)
{
    dx = dx + ddx * t;
}

void Velocity::computeDy(double ddy, double t)
{
    dy = dy + ddy * t;
}