#include "ship.h"
#define T 48

void Ship::fire()
{
    double x = position->getMetersX() + 2500000 * sin(angle);
    double y = position->getMetersY() + 2500000 * cos(angle);
    double dX = velocity->getDx() + 9000.0 * sin(angle);
    double dY = velocity->getDy() + 9000.0 * cos(angle);

    bullets.push_back(new Bullet(new Position(x, y), new Velocity(dX, dY), 1.0));
}

void Ship::update()
{
    thrust = false;

    double h = computeHeight();
    double gH = computeGh(h);

    double accAngle = atan2(position->getMetersX(), position->getMetersY());

    acceleration->set(gH, accAngle);


    velocity->computeNewVelocity(acceleration);

    if (ui.isDown())
    {
        velocity->setDx(velocity->getDx() + 2.0 * T * sin(angle));
        velocity->setDy(velocity->getDy() + 2.0 * T * cos(angle));
        thrust = true;
    }

    if (ui.isLeft())
        angle -= .1;
    if (ui.isRight())
        angle += .1;
    if (ui.isSpace())
        fire();

    position->computeNewPostion(velocity, acceleration);

    for (auto bullet : bullets)
        bullet->update();
}



void Ship::draw(ogstream* gout)
{
    gout->drawShip(*position, angle, thrust);

    for (auto bullet : bullets)
        bullet->draw(gout);

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if ((*it)->hasExpired() || (*it)->isDead)
            it = bullets.erase(it);
        else
            it++;
    }
}