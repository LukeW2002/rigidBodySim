#include <math.h>
#include "header/Object.h"

vec3D distanceVector(vec3D *vec2, vec3D *vec1)
{
	vec3D vec3DResult;
	vec3DResult.x = vec2->x - vec1->x;
	vec3DResult.y = vec2->y - vec1->y;
	vec3DResult.z = vec2->z - vec1->z;
	
	return vec3DResult;
}

double dotproduct(vec3D *vec2, vec3D *vec1)
{
	double scalarTemp;
	scalarTemp = vec2->x * vec1->x  + vec2->y * vec1->y + vec2->z * vec1->x;
	return scalarTemp;
}

double distanceScalar(vec3D *vec2, vec3D *vec1)
{
	vec3D vecTemp;
	vecTemp = distanceVector(vec2, vec1);

	double scalarResult = sqrt(pow(vecTemp.x,2) + pow(vecTemp.y,2) + pow(vecTemp.z,2));
	return scalarResult;
}
