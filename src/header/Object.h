#ifndef OBJECT_H
#define OBJECT_H

typedef struct 
{
	double x;
	double y;
	double z;

}vec3D;

typedef struct 
{
	vec3D position;
	vec3D oldPosition;
	vec3D velocity;
	vec3D acceleration;
}object;

typedef struct 
{
	object objectBall;
	double radius;
	double mass;
}ball;

#endif
