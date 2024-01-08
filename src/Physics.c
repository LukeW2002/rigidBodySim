#include "header/Object.h"
#include "header/Vector.h"
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

void diagnosticVectors(object *obj)
{	
	printf("Position (%g, %g)\n", obj->position.x, obj->position.y);
	printf("Velocity (%g, %g)\n", obj->velocity.x, obj->velocity.y);
	printf("Acceleration (%g, %g)\n", obj->acceleration.x, obj->acceleration.y);
	printf("\033[2J\033[H");

}

double checkCollision(ball *ball2, ball *ball1)
{
 double distance = distanceScalar(&ball2->objectBall.position, &ball1->objectBall.position);
 double combinedRadius = ball2->radius + ball1->radius;

 if (distance < combinedRadius)
 {
	 return 1;
 } else {
	 return 0;
 }

	return 0;
}

void collisionBallonBall(ball *ball2, ball *ball1)
{
	vec3D distanceVec = distanceVector(&ball2->objectBall.position, &ball1->objectBall.position);
	double distanceScalar = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2) + pow(distanceVec.z, 2)); //distanceScalar() function calls on distanceVector, this is more efficient.
																																																			 //
	//If we are inside a ball, put back in bounds.
	double epsilon = 0.5*(distanceScalar - (ball2->radius + ball1->radius));
	if (checkCollision(ball1, ball2) == 1)
	{
		printf("COLLISON\n");
		ball1->objectBall.position.x += (epsilon * distanceVec.x)/distanceScalar;
		ball1->objectBall.position.y += (epsilon * distanceVec.y)/distanceScalar;
		
		ball2->objectBall.position.x -= (epsilon * distanceVec.x)/distanceScalar;
		ball2->objectBall.position.y -= (epsilon * distanceVec.y)/distanceScalar;
	}
}



void verlet(object *obj, double dt, int radius)
{
	if (obj->position.x - radius > WIDTH || obj->position.x + radius < 0)
	{

		obj->velocity.x = -obj->velocity.x;
	}
	if (obj->position.y - radius > HEIGHT || obj->position.y + radius < 0)
	{
		obj->velocity.y = -obj->velocity.y;
	}
	// 1: v(t + dt/2) = v(t) + 0.5 * dt * a(t)
	vec3D velHalfStep;
	velHalfStep.x = obj->velocity.x + 0.5f*dt*obj->acceleration.x; 
	velHalfStep.y = obj->velocity.y + 0.5f*dt*obj->acceleration.y; 

	// 2: x(t + dt) = x(t) + v(t +dt/2) * dt
	obj->position.x += velHalfStep.x*dt;
	obj->position.y += velHalfStep.y*dt;
	
	// 3: Update Acceleration
	obj->acceleration.x = 0.0f;
	obj->acceleration.y = 9.8f;

	// 4: v(t + dt) = v(t + dt/2) + 0.5 * dt * a(t)
	obj->velocity.x = velHalfStep.x + 0.5f*dt*obj->acceleration.x; 
	obj->velocity.y = velHalfStep.y + 0.5f*dt*obj->acceleration.y; 

	obj->oldPosition = obj->position;

	//diagnosticVectors(obj);
	}


