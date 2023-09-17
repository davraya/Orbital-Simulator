#pragma once

class Acceleration;

class Velocity
{
public:
    Velocity() {}
    Velocity(double dx, double dy) : dx{ dx }, dy{ dy } {}

    void computeNewVelocity(Acceleration* acc);
    double const getDx() { return dx; }
    double const getDy() { return dy; }
    void setDx(double dx) { this->dx = dx; }
    void setDy(double dy) { this->dy = dy; }
    friend class TestVelocity;
private:
    double dx;
    double dy;
    void computeDx(double ddx, double t);
    void computeDy(double ddy, double t);
};