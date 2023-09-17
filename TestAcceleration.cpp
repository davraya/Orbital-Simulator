#include <cassert>
#include <cmath>
#include <iostream>
#include "TestHelper.h"
#include "TestAcceleration.h"
#include "Acceleration.h"


void TestAcceleration::run()
{
    testComputeDdx_positive();
    testComputeDdx_negative();
    testComputeDdx_positive_decimal();
    testComputeDdy_positive();
    testComputeDdx_negative();
    testComputeDdy_positive_decimal();
}

void TestAcceleration::testComputeDdx_positive()
{
    // set up
    double gravity = 1.0;
    double angle = 1.5708; // 90 degs in radians
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdx();

    // verify
    assert(closeEnough(acc.ddx, 1.0, .001));
}

void TestAcceleration::testComputeDdx_negative()
{
    // set up
    double gravity = 1.0;
    double angle = 4.712; // 270 degs in radians
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdx();

    // verify
    assert(closeEnough(acc.ddx, -1.0, .001));
}

void TestAcceleration::testComputeDdx_positive_decimal()
{
    // set up
    double gravity = 0.224;
    double angle = 0.524;
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdx();

    // verify
    assert(closeEnough(acc.ddx, 0.1122, .001));
}

void TestAcceleration::testComputeDdy_positive()
{
    // set up
    double gravity = 1.0;
    double angle = 0.0;
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdy();

    // verify
    assert(closeEnough(acc.ddy, 1.0, .001));
}

void TestAcceleration::testComputeDdy_negative()
{
    // set up
    double gravity = 1.0;
    double angle = 3.14159; // 180 degs in radians
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdy();

    // verify
    assert(closeEnough(acc.ddy, -1.0, .001));
}

void TestAcceleration::testComputeDdy_positive_decimal()
{
    // set up
    double gravity = 0.224;
    double angle = 0.524;
    Acceleration acc;
    acc.set(gravity, angle);

    // exercise 
    acc.computeDdy();

    // verify
    assert(closeEnough(acc.ddy, 0.1943, .001));
}