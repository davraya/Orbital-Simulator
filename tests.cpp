#include <iostream>
#include "TestAcceleration.h"
#include "TestVelocity.h"
#include "TestPosition.h"
#include "tests.h"

using std::cout;

void testsRunner()
{
    TestAcceleration tAcceleration;
    TestVelocity tVelocity;
    TestPosition tPosition;

    cout << "Starting Acceleration Tests...\n";
    tAcceleration.run();

    cout << "Starting Velocity Tests...\n";
    tVelocity.run();

    cout << "Starting Position Tests...\n";
    tPosition.run();

    cout << "All tests passed!\n";
}