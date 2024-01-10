#include <math.h>
#include <SDL2/SDL.h>
#include "header/Object.h"

void drawCircle(SDL_Renderer* renderer, object* obj, double radius, unsigned int r, unsigned int g, unsigned int b)
{
	SDL_SetRenderDrawColor(renderer, 255, r, g, b);
	const int32_t diameter = (radius * 2);

	int32_t x =  ( radius  - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >=y)
	{
		SDL_RenderDrawPoint(renderer, obj->position.x + x, obj->position.y - y);
		SDL_RenderDrawPoint(renderer, obj->position.x + x, obj->position.y + y);
		SDL_RenderDrawPoint(renderer, obj->position.x - x, obj->position.y - y);
		SDL_RenderDrawPoint(renderer, obj->position.x - x, obj->position.y + y);
		SDL_RenderDrawPoint(renderer, obj->position.x + y, obj->position.y - x);
		SDL_RenderDrawPoint(renderer, obj->position.x + y, obj->position.y + x);
		SDL_RenderDrawPoint(renderer, obj->position.x - y, obj->position.y - x);
		SDL_RenderDrawPoint(renderer, obj->position.x - y, obj->position.y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
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
