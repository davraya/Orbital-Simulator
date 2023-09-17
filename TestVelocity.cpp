#include <cassert>
#include <iostream>
#include "TestVelocity.h"
#include "Velocity.h"
#include "TestHelper.h"

void TestVelocity::run()
{
    testComputeDx_positive();
    testComputeDx_negative();
    testComputeDy_positive();
    testComputeDy_negative();
}

void TestVelocity::testComputeDx_positive()
{
    // set up
    double dx = 1.0;
    double ddx = 2.0;
    double t = 5.0;
    Velocity vel(dx, 0.0);

    // exercise
    vel.computeDx(ddx, t);

    // verify
    assert(closeEnough(vel.dx, 11.0, .001));
}

void TestVelocity::testComputeDx_negative()
{
    // set up
    double dx = -2685;
    double ddx = 0.1122;
    double t = 48;
    Velocity vel(dx, 0.0);

    // exercise
    vel.computeDx(ddx, t);

    // verify
    assert(closeEnough(vel.dx, -2679.614, .001));
}

void TestVelocity::testComputeDy_positive()
{
    // set up
    double dy = 1550;
    double ddy = 0.1943;
    double t = 48;
    Velocity vel(0.0, dy);

    // exercise
    vel.computeDy(ddy, t);

    // verify
    assert(closeEnough(vel.dy, 1559.326, .001));
}

void TestVelocity::testComputeDy_negative()
{
    // set up
    double dy = 1.0;
    double ddy = -2.0;
    double t = 5.0;
    Velocity vel(0.0, dy);

    // exercise
    vel.computeDy(ddy, t);

    // verify
    assert(closeEnough(vel.dy, -9.0, .001));
}