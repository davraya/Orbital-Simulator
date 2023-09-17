#pragma once
#include "OribtalObject.h"
#include "uiDraw.h"

class Earth : public OrbitalObject
{
public:
   Earth() {}
   Earth(Position* pos, Velocity* vel, double r) : OrbitalObject(pos, vel, r) {}
   void draw(ogstream* gout) { gout->drawEarth(*position, angle); };
   void breakUp(std::list<OrbitalObject*>* orbitalObjects){};
   void rotate() { angle += 0.01; }

};