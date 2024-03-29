#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "header/Object.h"
#include "header/Physics.h"
#include "header/Render.h"

#define MAX_BALLS 300
#define WIDTH 800
#define HEIGHT 600

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* font;

//Adds ball to a list
void addBallToList(ball **head)
{
	ball *newBall = (ball*)malloc(sizeof(ball));
	if (newBall == NULL)
	{
		printf("Error memory error");
	}

	newBall->objectBall.position.x = rand()%WIDTH;
	newBall->objectBall.position.y = rand()%HEIGHT;
	newBall->objectBall.oldPosition.x = newBall->objectBall.position.x;
	newBall->objectBall.oldPosition.y = newBall->objectBall.position.y;
	newBall->objectBall.velocity.x = rand() % 9; 
	newBall->objectBall.velocity.y = rand() % 9; 
	newBall->objectBall.acceleration.x = 0;
	newBall->objectBall.acceleration.y = 0;
	newBall->mass = rand() % 5;
	newBall->radius = 3;
	newBall->next = *head;
	*head = newBall;
}
int countBall(ball* head)
{
	int count = 0;
	ball *currentBall = head;
	while (currentBall != NULL)
	{
		count++;
		currentBall = currentBall->next;
	}
	return count;
}
void proccessBall(ball *head, double dt)
{
	ball *currentBall = head;
	while (currentBall != NULL)
	{
		verlet(&currentBall->objectBall, dt, currentBall->radius);
		currentBall = currentBall->next;
	}
}

void renderBall(SDL_Renderer *renderer, ball *head)
{
	ball* currentBall = head;
	while (currentBall != NULL)
	{
		drawCircle(renderer, &currentBall->objectBall, currentBall->radius, 255, 255, 255);
		currentBall = currentBall->next;
	}
		
}

void destroyBallList(ball **head)
{
	while(*head != NULL)
	{
		ball *temp = *head; //move to current node
		*head = (*head)->next; //moves to next node	
		free(temp); //frees
	}
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
	ball *head = NULL;
	

	//Vars used inside GameLoop
	Uint32 lastUpdate = 0;
	int calcPerFrame = 10;
	SDL_Event event;
	int quit = 0;

		/*Font Rendering */
	font = TTF_OpenFont("/home/fuck/projects/rigidBodySim/src/TerminusMedium.ttf", 16);
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

					/*PHYSICS*/
		Uint32 current = SDL_GetTicks(); // This allows us to set dt relative to how fast the simulation is running.
		double dt = (current - lastUpdate)/1000.0f;

		for (int calc = 0; calc < calcPerFrame; calc++)
		{
			proccessBall(head, dt);
		}
		lastUpdate = current;
			
					/*Render Loop */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		renderBall(renderer, head);

		
		SDL_RenderPresent(renderer);
		SDL_Delay(16);

		addBallToList(&head);

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		printf("FPS: %f\n", 1.0f/elapsed);
		printf("Amount of Balls: %i\n", countBall(head));
	}
	destroyBallList(&head);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}						
