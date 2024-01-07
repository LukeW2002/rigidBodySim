#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "header/Object.h"
#include "header/Physics.h"
#include "header/Render.h"

#define MAX_BALLS 100
#define WIDTH 800
#define HEIGHT 600



void addRandomBall(ball *balls, int currentBall)
{
	balls[currentBall].objectBall.position.x = rand() % WIDTH;
	balls[currentBall].objectBall.position.y = rand() % HEIGHT;
	balls[currentBall].objectBall.oldPosition.x = balls[currentBall].objectBall.position.x;
	balls[currentBall].objectBall.oldPosition.y = balls[currentBall].objectBall.position.y;
	balls[currentBall].objectBall.velocity.x = 3; 
	balls[currentBall].objectBall.velocity.y = 9; 
	balls[currentBall].objectBall.acceleration.x = 0;
	balls[currentBall].objectBall.acceleration.y = 0;
	balls[currentBall].mass = rand() % 5;
	balls[currentBall].radius = 5;
}

int main()
{
	//Init
	srand(time(NULL));	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL INIT ERROR");
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow( "rigidBodySim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	if (!window)
	{
		printf("WINDOW ERROR");
		return -1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		printf("RENDER ERROR");
		return -1;
	}

	//Declerations
	ball balls[MAX_BALLS];
	for (int ballCount = 0; ballCount < MAX_BALLS; ballCount++)
	{
		addRandomBall(balls, ballCount);
	}

	double dt = 0.001;
	int calcPerFrame = 10;


	SDL_Event event;
	int quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0 )
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (int calc = 0; calc < calcPerFrame; calc++)
		{
			for (int i = 0; i < MAX_BALLS; i++)
			{
				verlet(&balls[i].objectBall, dt);
				for (int j = i + 1; j < MAX_BALLS; j++)
				{
					//collisionBallonBall(&balls[i], &balls[j]);
					//drawLinesBetweenCentres(renderer, &balls[i].objectBall, &balls[j].objectBall);
				}
			}
		}
			
		for (int i = 0; i < MAX_BALLS; i++)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			drawCircle(renderer, &balls[i].objectBall, balls[i].radius, 255, 255, 255);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}						
