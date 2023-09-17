#pragma once

#define EARTH_RADIUS 6378000
#define GRAVITY -9.8067

class Position;

class Acceleration
{
public:
    Acceleration() {}
    Acceleration(double ddx, double ddy) { this->ddx = ddx; this->ddy = ddy; }
    /* g - gravity, a - angle */
    void set(double g, double a) { gravity = g; angle = a; computeDdx(); computeDdy(); }
    
    double const getDdx() { return ddx; }
    double const getDdy() { return ddy; }
    void setDdx(double ddx) { this->ddx = ddx; }
    void setDdy(double ddy) { this->ddy = ddy; }
    void computeNewAcceleration(Position* p);
    friend class TestAcceleration;
private:
    double ddx;        // x acceleration
    double ddy;        // y acceleration
    double gravity;    
    double angle;  
    void computeDdx();
    void computeDdy();
    double computeHeight(Position* p);
    double computeGh(double h);
};