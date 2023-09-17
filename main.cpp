/*************************************************************
 * 1. Names:
 *      Sam Cummings & David Raya
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "Velocity.h"
#include "tests.h"
#include "satellites.h"
#include "bullet.h"
#include "ship.h"
#include <vector>
#include <list>
#include "Earth.h"

#define STAR_COUNT 30

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Simulation
{
public:
    Simulation(Position ptUpperRight) :
        ptUpperRight(ptUpperRight)
    {
        for (int i = 0; i < STAR_COUNT; i++)
            starPositions.push_back(new Position(ptUpperRight.getMetersX() * random(-0.5, 0.5), ptUpperRight.getMetersY() * random(-0.5, 0.5)));

        angleShip = 0.0;
        angleEarth = 0.0;
        phaseStar = 0;
    }

    Ship ship = Ship(new Position(-450.0 * 128000.0, 450.0 * 128000.0), new Velocity(0.0, -2000.0), 0.0);
    Position ptShip;
    list<Position*> starPositions;
    Position ptUpperRight;

    Sputnik sputnik       =  Sputnik   (new Position(-36'515'095.13, 21'082'000.0), new Velocity(2050.0, 2684.68),  4.0);
    Hubble hubble         =  Hubble    (new Position(0.0, -42'164'000.0),       new Velocity(3100.0, 0.0),      10.0);
    Starlink starlink     =  Starlink  (new Position(0.0, -13'020'000.0),       new Velocity(5800.0, 0.0),      6.0);
    CrewDragon crewDragon =  CrewDragon(new Position(0.0, 8'000'000.0),         new Velocity(-7900.0, 0.0),     7.0);

    GPS gps_1 = GPS(new Position(0.0, 26'560'000.0),             new Velocity(-3880.0, 0.0),      12.0);
    GPS gps_2 = GPS(new Position(23'001'634.72, 13'280'000.0),   new Velocity(-1940.0, 3360.18),  12.0);
    GPS gps_3 = GPS(new Position(23'001'634.72, -13'280'000.0),  new Velocity(1940.0, 3360.18),   12.0);
    GPS gps_4 = GPS(new Position(0.0, -26'560'000.0),            new Velocity(3880.0, 0.0),       12.0);
    GPS gps_5 = GPS(new Position(-23'001'634.72, -13'280'000.0), new Velocity(1940.0, -3360.18),  12.0);
    GPS gps_6 = GPS(new Position(-23'001'634.72, 13'280'000.0),  new Velocity(-1940.0, -3360.18), 12.0);

    list<OrbitalObject*> orbitalObjects =
    {
        &sputnik,
        &hubble,
        &starlink,
        &crewDragon,
        &gps_1,
        &gps_2,
        &gps_3,
        &gps_4,
        &gps_5,
        &gps_6,
        &ship
    };

    unsigned char phaseStar;
    Earth earth = Earth(new Position(0, 0), new Velocity(0, 0), 50);
    double angleShip;
    double angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Simulation* pSimulation = (Simulation*)p;

    // Check for collisions
    for (auto currObj : pSimulation->orbitalObjects)
    {
        // Check for satellite collisions
        for (auto otherObj : pSimulation->orbitalObjects)
        {
            if (currObj != otherObj)
            {
                if (currObj->checkCollision(otherObj))
                {
                    currObj->isDead = true;
                    otherObj->isDead = true;
                }
            }
        }
        // Check for bullet impact
        for (auto bullet : *pSimulation->ship.getBullets())
        {
            if (bullet->checkCollision(currObj))
            {
                currObj->isDead = true;
                bullet->isDead = true;
            }
        }

        //Check for earth collision
        if(pSimulation->earth.checkCollision(currObj))
           currObj->isDead = true;
    }

    // Remove all the 'dead' objs
    for (auto it = pSimulation->orbitalObjects.begin(); it != pSimulation->orbitalObjects.end();)
    {
        if ((*it)->isDead)
        {
            //delete* it;
            (*it)->breakUp(&pSimulation->orbitalObjects);
            it = pSimulation->orbitalObjects.erase(it);
        }
        else
            it++;
    }

   
    // Update positions
    for (auto orbitalObj : pSimulation->orbitalObjects)
        orbitalObj->update();


    // rotate the earth
    pSimulation->earth.rotate();
    pSimulation->angleShip += 0.02;
    pSimulation->phaseStar++;

    //
    // draw everything
    //
    Position pt;
    ogstream gout(pt);

    // draw satellites and ship
    for (auto orbitalObj : pSimulation->orbitalObjects)
        orbitalObj->draw(&gout);
  
       // draw a single star
    for (auto starPos : pSimulation->starPositions)
        gout.drawStar(*starPos, pSimulation->phaseStar);

    // draw the earth
    pt.setMeters(0.0, 0.0);
    pSimulation->earth.draw(&gout);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Run tests
    testsRunner();

    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
    ptUpperRight.setPixelsX(1000.0);
    ptUpperRight.setPixelsY(1000.0);
    Interface ui(0, NULL,
        "Orbital Simulation",   /* name on the window */
        ptUpperRight);

    // Initialize the demo
    Simulation simulation(ptUpperRight);

    // set everything into action
    ui.run(callBack, &simulation);

    return 0;
}