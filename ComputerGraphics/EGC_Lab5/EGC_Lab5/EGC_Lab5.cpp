//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//


#include <iostream>
#include "include\SDL.h"
#include "transform.h"

using namespace egc;

SDL_Renderer* windowRenderer;
// define rectangle vertices
vec3 O(0, 0, 0);
vec3 P[] = { {100, 150, 1} ,{300, 250, 1}, {200, 100, 1} };
mat3 originalTranslation;
mat3 translatePoint;
mat3 Rotation;
mat3 Scaleing;
mat3 resTrans;

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = { 100, 100, 200, 200 };

bool quit = false;

int mouseX, mouseY;


void rotatePoints(float angle)
{
	Rotation = rotate(angle);
	O.x = (P[0].x + P[1].x) / 2;
	O.y = (P[1].y + P[0].y) / 2;

	translatePoint = translate(-O.x, -O.y);
	originalTranslation = translate(O.x, O.y);
	resTrans = originalTranslation * Rotation * translatePoint;
	for (int i = 0; i < 3; i++)
	{
		P[i] = resTrans * P[i];
	}
}

void scalePoints(float scaleFactor1, float scaleFactor2)
{
	Scaleing = scale(scaleFactor1,scaleFactor2);
	O.x = P[0].x;
	O.y = P[0].y;
	translatePoint = translate(-O.x, -O.y);
	originalTranslation = translate(O.x, O.y);


	resTrans = originalTranslation * Scaleing * translatePoint;
	for (int i = 0; i < 3; i++)
	{
		P[i] = resTrans * P[i];
	}
}





bool initWindow()
{
	bool success = true;

	//Try to initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed" << std::endl;
		success = false;
	}
	else {
		//Try to create the window
		window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (window == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Create a renderer for the current window
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (windowRenderer == NULL)
			{
				std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Set background color
				SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);

				//Apply background color
				SDL_RenderClear(windowRenderer);
			}

		}
	}

	return success;
}

void destroyWindow()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	if (!initWindow())
	{
		std::cout << "Failed to initialize" << std::endl;
		return -1;
	}


	while (!quit) {
		//Handle events on queue
		if (SDL_WaitEvent(&currentEvent) != 0)
		{
			//User requests quit
			if (currentEvent.type == SDL_QUIT)
			{
				quit = true;
			}

			//Mouse event -> pressed button
			if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
				}
			}

			//Mouse event -> mouse movement
			if (currentEvent.type == SDL_MOUSEMOTION)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
				}
			}

			//Keyboard event
			if (currentEvent.type == SDL_KEYDOWN)
			{
				switch (currentEvent.key.keysym.sym)
				{
				case SDLK_RIGHT:
					rotatePoints(15);
					break;

				case SDLK_LEFT:
					rotatePoints(-15);
					break;

				case SDLK_DOWN:
					scalePoints(1.3,1.3);
					break;

				case SDLK_UP:
					scalePoints(1 / 1.3,1/1.3);
					break;

				default:
					break;
				}
			}

			}

			SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			SDL_RenderClear(windowRenderer);
			SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);
			SDL_RenderDrawLine(windowRenderer, P[0].x, P[0].y, P[2].x, P[2].y);
			SDL_RenderDrawLine(windowRenderer, P[2].x, P[2].y, P[1].x, P[1].y);
			SDL_RenderDrawLine(windowRenderer, P[0].x, P[0].y, P[1].x, P[1].y);
		
		
			SDL_RenderPresent(windowRenderer);
		
	}

	destroyWindow();
	return 0;
}