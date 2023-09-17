#pragma once

#include "position.h"
#include "OribtalObject.h"

#include <chrono>



class Bullet : public OrbitalObject {

    std::chrono::steady_clock::time_point expirationTime = std::chrono::steady_clock::now() + std::chrono::seconds(3);

public:

    Bullet(Position* p, Velocity* v, double r) : OrbitalObject(p, v, r) {}

    void draw(ogstream* gout) { gout->drawProjectile(*position); }
    void breakUp(std::list<OrbitalObject*>* orbitalObjects) {  }



    bool hasExpired() {
        if (std::chrono::steady_clock::now() > expirationTime)
            return true;
        return false;
    }



};