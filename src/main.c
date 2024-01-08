#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "header/Object.h"
#include "header/Physics.h"
#include "header/Render.h"

#define MAX_BALLS 4
#define WIDTH 800
#define HEIGHT 600

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* font;

void init()
{
}

void addRandomBall(ball *balls, int currentBall)
{
	balls[currentBall].objectBall.position.x = rand()%WIDTH;
	balls[currentBall].objectBall.position.y = rand()%HEIGHT;
	balls[currentBall].objectBall.oldPosition.x = balls[currentBall].objectBall.position.x;
	balls[currentBall].objectBall.oldPosition.y = balls[currentBall].objectBall.position.y;
	balls[currentBall].objectBall.velocity.x = rand() % 9; 
	balls[currentBall].objectBall.velocity.y = rand() % 9; 
	balls[currentBall].objectBall.acceleration.x = 0;
	balls[currentBall].objectBall.acceleration.y = 0;
	balls[currentBall].mass = rand() % 5;
	balls[currentBall].radius = 30;
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

	if (TTF_Init() < 0) 
	{
		printf("ERROR SDL_TTF");
	}
	window = SDL_CreateWindow("RigidBodySim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

	if (!window)
	{
		printf("WINDOW ERROR");
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

	//Vars used inside GameLoop
	Uint32 lastUpdate = 0;
	int calcPerFrame = 10;
	SDL_Event event;
	int quit = 0;

		/*Font Rendering */
	font = TTF_OpenFont("/home/fuck/Projects/rigidBodySimulator/src/TerminusMedium.ttf", 16);
	if (!font) { printf("Error Font Loading\n");}
	SDL_Color colour = { 0, 255, 255, 255};

	SDL_Surface* text;
	text = TTF_RenderText_Solid(font, "There's a lot to do.", colour);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, text);
	if (!Message) { printf( "Error, Texture creation failed\n");}
	SDL_Rect Message_rect;
	Message_rect.x = 0;
	Message_rect.y = 0;
	Message_rect.w = text->w;
	Message_rect.h = text->h;


	while (!quit)
	{
		Uint64 start = SDL_GetPerformanceCounter();
			/*Events*/
		while (SDL_PollEvent(&event) != 0 )
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
		}

					/*Render Loop*/
		Uint32 current = SDL_GetTicks(); // This allows us to set dt relative to how fast the simulation is running.
		double dt = (current - lastUpdate)/1000.0f;

		for (int calc = 0; calc < calcPerFrame; calc++)
		{
			for (int i = 0; i < MAX_BALLS; i++)
			{
				verlet(&balls[i].objectBall, dt, balls[i].radius);
				for (int j = i +1; j < MAX_BALLS; j++)
				{
					collisionBallonBall(&balls[j], &balls[i]);
				}
				
			}
		}
		lastUpdate = current;
			
					/*Render Loop */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		for (int i = 0; i < MAX_BALLS; i++)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			drawCircle(renderer, &balls[i].objectBall, balls[i].radius, 255, 255, 255);
		}
		
		SDL_RenderPresent(renderer);
		SDL_Delay(16);

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		printf("FPS: %f\n", 1.0f/elapsed);
	}
	SDL_FreeSurface(text);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}						
