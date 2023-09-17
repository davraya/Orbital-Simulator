#include <cassert>
#include <iostream>
#include "TestPosition.h"
#include "Acceleration.h"
#include "Velocity.h"
#include "Position.h"
#include "TestHelper.h"

void TestPosition::run()
{
    testComputeX_positive();
    testComputeX_negative();
    testComputeX_positive_decimal();
    testComputeY_positive();
    testComputeY_negative();
    testComputeY_positive_decimal();
}

void TestPosition::testComputeX_positive()
{
    // Setup
    Velocity velocity(5.0, 0.0);
    Velocity* pVel = &velocity;
    Acceleration acceleration(2.0, 0.0);
    Acceleration* pAccel = &acceleration;
    double t = 1.0;
    Position position;
    position.x = 10.0;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeX(pVel->getDx(), pAccel->getDdx(), t);

    // Verify
    assert(position.x == 16.0);
}

void TestPosition::testComputeX_negative()
{
    // Setup
    Velocity velocity(-10.0, 0.0);
    Velocity* pVel = &velocity;
    Acceleration acceleration(2.0, 0.0);
    Acceleration* pAccel = &acceleration;
    double t = 1.0;
    Position position;
    position.x = 5.0;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeX(pVel->getDx(), pAccel->getDdx(), t);

    // Verify
    assert(position.x == -4.0);
}

void TestPosition::testComputeX_positive_decimal()
{
    // Setup
    Velocity velocity(-2690.39, 1540.67);
    Velocity* pVel = &velocity;
    Acceleration acceleration(-0.112274, -0.194285);
    Acceleration* pAccel = &acceleration;
    double t = 48.0;
    Position position;
    position.x = 21082000.0;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeX(pVel->getDx(), pAccel->getDdx(), t);

    // Verify
    assert(closeEnough(position.x, 20952731.940, 0.001));
}

void TestPosition::testComputeY_positive()
{
    // Setup
    Velocity velocity(0, 5);
    Velocity* pVel = &velocity;
    Acceleration acceleration(0, 2);
    Acceleration* pAccel = &acceleration;
    double t = 1;
    Position position;
    position.y = 10;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeY(pVel->getDy(), pAccel->getDdy(), t);

    // Verify
    assert(position.y == 16.0);
}

void TestPosition::testComputeY_negative()
{
    // Setup
    Velocity velocity(0, -10.0);
    Velocity* pVel = &velocity;
    Acceleration acceleration(0, 2.0);
    Acceleration* pAccel = &acceleration;
    double t = 1;
    Position position;
    position.y = 5.0;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeY(pVel->getDy(), pAccel->getDdy(), t);

    // Verify
    assert(position.y == -4.0);
}

void TestPosition::testComputeY_positive_decimal()
{
    // Setup
    Velocity velocity(-2690.39, 1540.67);
    Velocity* pVel = &velocity;
    Acceleration acceleration(-0.112274, -0.194285);
    Acceleration* pAccel = &acceleration;
    double t = 48.0;
    Position position;
    position.y = 36515095.0;
    position.update(&acceleration, &velocity, t);

    // Exercise
    position.computeY(pVel->getDy(), pAccel->getDdy(), t);

    // Verify
    assert(closeEnough(position.y, 36588823.343, 0.001));
}