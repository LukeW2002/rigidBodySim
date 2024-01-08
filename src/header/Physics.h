#ifndef PHYSICS_H
#define PHYSICS_H
#include "Object.h"

double checkCollision(ball *ball2, ball *ball1);
void collisionBallonBall(ball *ball2, ball *ball1);
void verlet(object *obj, double dt, int radius);

#endif
