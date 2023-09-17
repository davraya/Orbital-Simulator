#pragma once

#include "OribtalObject.h"
#include "uiDraw.h"
#include <iostream>
#include <chrono>
#include "Velocity.h"

using namespace std;

class Fragment : public OrbitalObject
{
    std::chrono::steady_clock::time_point expirationTime = std::chrono::steady_clock::now() + std::chrono::seconds(3);
public:
    Fragment() {}
    Fragment(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawFragment(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects) {  };
    void update()
    {
        if (std::chrono::steady_clock::now() > expirationTime)
        {
            isDead = true;
            return;
        }
        double h = computeHeight();
        double gH = computeGh(h);

        angle = atan2(position->getMetersX(), position->getMetersY());

        acceleration->set(gH, angle);


        velocity->computeNewVelocity(acceleration);

        position->computeNewPostion(velocity, acceleration);
    }
    /*
    * Creates and returns a fragment
    * Params:
    *   - parentObj - the object that was just destroyed
    *   - angleDirRad - angle of direction in radians
    *   - xPixs - how many x pixels to move away from the parentObj
    *   - yPixs - how many y pixels to move away from the parentObj
    */
    static Fragment* createFragment(OrbitalObject* parentObj, double angleDirRad, double xPixs, double yPixs)
    {
        Position* fragPos = new Position(parentObj->getPosition()->getMetersX(), parentObj->getPosition()->getMetersY());
        fragPos->addPixelsX(xPixs);
        fragPos->addPixelsY(yPixs);
        Velocity* fragVel = new Velocity(
            parentObj->getVelocity()->getDx() + 5000.0 * sin(angleDirRad), 
            parentObj->getVelocity()->getDy() + 5000.0 * cos(angleDirRad)
        );
        Fragment* frag = new Fragment(fragPos, fragVel, 2);

        return frag;
        
    }
};


class CrewDragonCenter : public OrbitalObject
{
public:
   CrewDragonCenter() {}
   CrewDragonCenter(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawCrewDragonCenter(*position, angle); }
   void breakUp(std::list<OrbitalObject*>* orbitalObjects)
   {
      Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
      Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
      Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
      Fragment* frag4 = Fragment::createFragment(this, 3.14159, 0.0, -4.0);


      orbitalObjects->push_back(frag1);
      orbitalObjects->push_back(frag2);
      orbitalObjects->push_back(frag3);
      orbitalObjects->push_back(frag4);
   }
};

class CrewDragonLeft : public OrbitalObject
{
public:
   CrewDragonLeft() {}
   CrewDragonLeft(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawCrewDragonLeft(*position, angle); }
   void breakUp(std::list<OrbitalObject*>* orbitalObjects)
   {
      Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
      Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);



      orbitalObjects->push_back(frag1);
      orbitalObjects->push_back(frag2);
   }
};

class CrewDragonRight : public OrbitalObject
{
public:
   CrewDragonRight() {}
   CrewDragonRight(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawCrewDragonCenter(*position, angle); }
   void breakUp(std::list<OrbitalObject*>* orbitalObjects)
   {
      Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
      Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);



      orbitalObjects->push_back(frag1);
      orbitalObjects->push_back(frag2);
   }
};

class CrewDragon : public OrbitalObject
{
public:
    CrewDragon() {}
    CrewDragon(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawCrewDragon(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
       // Add the fragments
       Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 10.0);
       Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, -10.0);

       orbitalObjects->push_back(frag1);
       orbitalObjects->push_back(frag2);

       // Add the pieces
       Position* dragonCenterPos = new Position(position->getMetersX(), position->getMetersY());
       Velocity* dragonCenterVel = new Velocity(velocity->getDx() + 5000, velocity->getDy() + 5000);
       CrewDragonCenter* dragonCenter = new CrewDragonCenter(dragonCenterPos, dragonCenterVel, 7.0);

       Position* dragonLeftPos = new Position(position->getMetersX(), position->getMetersY());
       dragonLeftPos->addPixelsX(-20.0);
       Velocity* dragonLeftVel = new Velocity(velocity->getDx() + 5000 * sin(-1.57), velocity->getDy() + 5000 * cos(-1.57));
       CrewDragonLeft* dragonLeft = new CrewDragonLeft(dragonLeftPos, dragonLeftVel, 8.0);

       Position* dragonRightPos = new Position(position->getMetersX(), position->getMetersY());
       dragonRightPos->addPixelsX(20.0);
       Velocity* dragonRightVel = new Velocity(velocity->getDx() + 5000 * sin(1.57), velocity->getDy() + 5000 * cos(1.57));
       CrewDragonRight* dragonRight = new CrewDragonRight(dragonRightPos, dragonRightVel, 8.0);

       orbitalObjects->push_back(dragonCenter);
       orbitalObjects->push_back(dragonLeft);
       orbitalObjects->push_back(dragonRight);

    };
};

class GPSCenter : public OrbitalObject
{
    public:
        GPSCenter() {}
        GPSCenter(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
        void draw(ogstream* gout) { gout->drawGPSCenter(*position, angle); }
        void breakUp(std::list<OrbitalObject*>* orbitalObjects)
        {
            Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
            Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
            Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);

            orbitalObjects->push_back(frag1);
            orbitalObjects->push_back(frag2);
            orbitalObjects->push_back(frag3);
        }
};

class GPSLeft : public OrbitalObject
{
    public:
        GPSLeft() {}
        GPSLeft(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
        void draw(ogstream* gout) { gout->drawGPSLeft(*position, angle); }
        void breakUp(std::list<OrbitalObject*>* orbitalObjects)
        {
            Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
            Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
            Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);

            orbitalObjects->push_back(frag1);
            orbitalObjects->push_back(frag2);
            orbitalObjects->push_back(frag3);
        }
};

class GPSRight : public OrbitalObject
{
    public:
        GPSRight() {}
        GPSRight(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
        void draw(ogstream* gout) { gout->drawGPSRight(*position, angle); }
        void breakUp(std::list<OrbitalObject*>* orbitalObjects)
        {
            Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
            Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
            Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);

            orbitalObjects->push_back(frag1);
            orbitalObjects->push_back(frag2);
            orbitalObjects->push_back(frag3);
        }
};

class GPS : public OrbitalObject
{
public:
    GPS() {}
    GPS(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawGPS(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        // Add the fragments
        Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 10.0);
        Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, -10.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);

        // Add the pieces
        Position* gpsCenterPos = new Position(position->getMetersX(), position->getMetersY());
        Velocity* gpsCenterVel = new Velocity(velocity->getDx() + 5000, velocity->getDy() + 5000);
        GPSCenter* gpsCenter = new GPSCenter(gpsCenterPos, gpsCenterVel, 7.0);

        Position* gpsLeftPos = new Position(position->getMetersX(), position->getMetersY());
        gpsLeftPos->addPixelsX(-20.0);
        Velocity* gpsLeftVel = new Velocity(velocity->getDx() + 5000 * sin(-1.57), velocity->getDy() + 5000 * cos(-1.57));
        GPSLeft* gpsLeft = new GPSLeft(gpsLeftPos, gpsLeftVel, 8.0);

        Position* gpsRightPos = new Position(position->getMetersX(), position->getMetersY());
        gpsRightPos->addPixelsX(20.0);
        Velocity* gpsRightVel = new Velocity(velocity->getDx() + 5000 * sin(1.57), velocity->getDy() + 5000 * cos(1.57));
        GPSRight* gpsRight = new GPSRight(gpsRightPos, gpsRightVel, 8.0);

        orbitalObjects->push_back(gpsCenter);
        orbitalObjects->push_back(gpsLeft);
        orbitalObjects->push_back(gpsRight);

    };
};

class HubbleTelescope : public OrbitalObject
{
public:
    HubbleTelescope() {}
    HubbleTelescope(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawHubbleTelescope(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    { 
        Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
        Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
        Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);
        orbitalObjects->push_back(frag3);
    };
};

class HubbleComputer : public OrbitalObject
{
public:
    HubbleComputer() {}
    HubbleComputer(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawHubbleComputer(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
        Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);
    };
};

class HubbleLeft : public OrbitalObject
{
public:
    HubbleLeft() {}
    HubbleLeft(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawHubbleLeft(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
        Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, 4.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);
    };
};

class HubbleRight : public OrbitalObject
{
public:
    HubbleRight() {}
    HubbleRight(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawHubbleRight(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
        Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, 4.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);
    };
};

class Hubble : public OrbitalObject
{
public:
    Hubble() {}
    Hubble(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawHubble(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        Position* hubbleLeftPos = new Position(position->getMetersX(), position->getMetersY());
        hubbleLeftPos->addPixelsX(-20.0);
        Velocity* hubbleLeftVel = new Velocity(velocity->getDx() + 5000.0 * sin(-1.57), velocity->getDy() + 5000.0 * cos(-1.57));
        HubbleLeft* hubbleLeft = new HubbleLeft(hubbleLeftPos, hubbleLeftVel, 8.0);

        Position* hubbleRightPos = new Position(position->getMetersX(), position->getMetersY());
        hubbleRightPos->addPixelsX(20.0);
        Velocity* hubbleRightVel = new Velocity(velocity->getDx() + 5000.0 * sin(1.57), velocity->getDy() + 5000.0 * cos(1.57));
        HubbleRight* hubbleRight = new HubbleRight(hubbleRightPos, hubbleRightVel, 8.0);

        Position* hubbleTelescopePos = new Position(position->getMetersX(), position->getMetersY());
        hubbleTelescopePos->addPixelsY(20.0);
        Velocity* hubbleTelescopeVel = new Velocity(velocity->getDx() + 5000.0 * sin(0.0), velocity->getDy() + 5000.0 * cos(0.0));
        HubbleTelescope* hubbleTelescope = new HubbleTelescope(hubbleTelescopePos, hubbleTelescopeVel, 10.0);

        Position* hubbleCompPos = new Position(position->getMetersX(), position->getMetersY());
        hubbleCompPos->addPixelsY(-20.0);
        Velocity* hubbleCompVel = new Velocity(velocity->getDx() + 5000.0 * sin(3.14159), velocity->getDy() + 5000.0 * cos(3.14159));
        HubbleComputer* hubbleComp = new HubbleComputer(hubbleCompPos, hubbleCompVel, 7.0);

        orbitalObjects->push_back(hubbleLeft);
        orbitalObjects->push_back(hubbleRight);
        orbitalObjects->push_back(hubbleTelescope);
        orbitalObjects->push_back(hubbleComp);
    };
};

class Sputnik : public OrbitalObject
{
public:
    Sputnik() {}
    Sputnik(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawSputnik(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
        Fragment* frag1 = Fragment::createFragment(this, 1.57, 4.0, 0.0);
        Fragment* frag2 = Fragment::createFragment(this, -1.57, -4.0, 0.0);
        Fragment* frag3 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
        Fragment* frag4 = Fragment::createFragment(this, 3.14159, 0.0, -4.0);

        orbitalObjects->push_back(frag1);
        orbitalObjects->push_back(frag2);
        orbitalObjects->push_back(frag3);
        orbitalObjects->push_back(frag4);
    };
};

class StarlinkBody : public OrbitalObject
{
public:
   StarlinkBody() {}
   StarlinkBody(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawStarlinkBody(*position, angle); }
   void breakUp(std::list<OrbitalObject*>* orbitalObjects)
   {
      Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
      Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, 4.0);
      Fragment* frag3 = Fragment::createFragment(this, -1.57, -4.0, 0.0);


      orbitalObjects->push_back(frag1);
      orbitalObjects->push_back(frag2);
      orbitalObjects->push_back(frag3);

   };
};

class StarlinkArray : public OrbitalObject
{
public:
   StarlinkArray() {}
   StarlinkArray(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawStarlinkArray(*position, angle); }
   void breakUp(std::list<OrbitalObject*>* orbitalObjects)
   {
      Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 4.0);
      Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, 4.0);
      Fragment* frag3 = Fragment::createFragment(this, -1.57, -4.0, 0.0);


      orbitalObjects->push_back(frag1);
      orbitalObjects->push_back(frag2);
      orbitalObjects->push_back(frag3);

   };
};

class Starlink : public OrbitalObject
{
public:
    Starlink() {}
    Starlink(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
    void draw(ogstream* gout) { gout->drawStarlink(*position, angle); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects)
    {
       // Add the fragments
       Fragment* frag1 = Fragment::createFragment(this, 0.0, 0.0, 10.0);
       Fragment* frag2 = Fragment::createFragment(this, 3.14159, 0.0, -10.0);

       orbitalObjects->push_back(frag1);
       orbitalObjects->push_back(frag2);

       // Add the pieces
       Position* starlinkBodyPos = new Position(position->getMetersX(), position->getMetersY());
       Velocity* starlinkBodyVel = new Velocity(velocity->getDx() + 5000, velocity->getDy() + 5000);
       StarlinkBody* dragonCenter = new StarlinkBody(starlinkBodyPos, starlinkBodyVel, 7.0);

       Position* starlinkArrayPos = new Position(position->getMetersX(), position->getMetersY());
       starlinkArrayPos->addPixelsX(-20.0);
       Velocity* starlinkArrayVel = new Velocity(velocity->getDx() + 5000 * sin(-1.57), velocity->getDy() + 5000 * cos(-1.57));
       StarlinkArray* dragonLeft = new StarlinkArray(starlinkArrayPos, starlinkArrayVel, 8.0);

     

       orbitalObjects->push_back(dragonCenter);
       orbitalObjects->push_back(dragonLeft);

    };
};