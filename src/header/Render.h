#ifndef RENDER_H
#define RENDER_H

		/* OBJECTS */
void drawCircle(SDL_Renderer* renderer, object* obj, double radius, int r, int g, int b);

		/* LINES */
void drawVelocity(SDL_Renderer* renderer, object* obj, double dt);
void drawAcceleration(SDL_Renderer* renderer, object* obj, double dt);
void drawLinesBetweenCentres(SDL_Renderer *renderer, object *obj2, object *obj1);

	

#endif
