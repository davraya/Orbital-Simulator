#pragma once
#include "uiInteract.h"
#include "position.h"
#include "uiDraw.h"
#include <list>
#include "bullet.h"
#include "OribtalObject.h"
#include "Velocity.h"



class Ship : public OrbitalObject {



private:
	std::list<Bullet*> bullets;
	Interface ui;
	bool thrust;


public:
	Ship() { velocity = new Velocity(0.0, 0.0); acceleration = new Acceleration(0.0, 0.0); position = new Position(50000.0, 50000.0); };
	//Ship(Position p, double a) { position = p; angle = a; };
	Ship(Position* p, Velocity* v, double r) : OrbitalObject(p, v, r) {}
	void fire();
	void move();
	void virtual update();
	void draw(ogstream* gout);
	std::list<Bullet*>* getBullets() { return &bullets; }
	void breakUp(std::list<OrbitalObject*>* orbitalObjects) {  }
};