#include <math.h>
#include <SDL2/SDL.h>
#include "header/Object.h"

void drawCircle(SDL_Renderer* renderer, object* obj, double radius, unsigned int r, unsigned int g, unsigned int b)
{
	for (int i = 0; i < 360; i++)
	{
		double angle = i * M_PI / 180.0;
		double circleX = obj->position.x + radius * cos(angle);
		double circleY = obj->position.y + radius * sin(angle);
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawPoint(renderer, (int)circleX, (int)circleY);
	}
}

void drawVelocity(SDL_Renderer* renderer, object* obj, double dt)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawLine(renderer, (int)obj->position.x, (int)obj->position.y, (int)obj->position.x + (int)obj->velocity.x*dt*10000, (int)obj->position.y + (int)obj->velocity.y*dt*10000);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
}

void LineBetweenCentres(SDL_Renderer *renderer, object *obj1, object *obj2)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, (int)obj1->position.x, (int)obj2->position.y, (int)obj2->position.x, (int)obj2->position.y);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void drawAcceleration(SDL_Renderer* renderer, object* obj, double dt)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderDrawLine(renderer, (int)obj->position.x, (int)obj->position.y, (int)obj->position.x + (int)obj->acceleration.x*dt, (int)obj->position.y + (int)obj->acceleration.y*dt);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
}
