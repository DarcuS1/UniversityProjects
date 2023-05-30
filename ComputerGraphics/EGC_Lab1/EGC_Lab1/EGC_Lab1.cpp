//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {200, 200, 200, 200};
Uint32 rectagleColor;
SDL_Rect circleCoordinates = { 100, 100, 100, 100 };
Uint32 circleColor;

int r = 0,g=0,b=0;

char colorChannel;
SDL_Rect newCoordinates;

bool quit = false;

int mouseX, mouseY;

bool initWindow()
{
    bool success = true;
    
    //Try to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else{
        //Try to create the window
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        
        if(window == NULL)
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Try to get the window surface
            windowSurface = SDL_GetWindowSurface(window);
            
            if(windowSurface == NULL)
            {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize surface color
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
               
                
                //Update the surface
                SDL_UpdateWindowSurface(window);
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

                    rectangleCoordinates.x = mouseX;
                    rectangleCoordinates.y = mouseY;
                    rectangleCoordinates.w = 10;
                    rectangleCoordinates.h = 10;
                }
            }

            //Mouse event -> mouse movement
            if (currentEvent.type == SDL_MOUSEMOTION)
            {
                if (currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);

                    int relativeX = mouseX - rectangleCoordinates.x;
                    int relativeY = mouseY - rectangleCoordinates.y;

                    rectangleCoordinates.w = relativeX;
                    rectangleCoordinates.h = relativeY;
                }

            }

            //Keyboard event
            if (currentEvent.type == SDL_KEYDOWN)
            {
                switch (currentEvent.key.keysym.sym)
                {
                case SDLK_r:
                     r += 1;
                    break;
                case SDLK_g:
                    g += 1;
                    break;
                case SDLK_b:
                   b += 1;
                    break;
                }
            }




            SDL_FillRect(windowSurface, nullptr, SDL_MapRGB(windowSurface->format, 255, 255, 255));

            SDL_Rect newRect = rectangleCoordinates;

            if (newRect.w < 0)
            {
                newRect.x = rectangleCoordinates.x + rectangleCoordinates.w;
                newRect.w = rectangleCoordinates.x - newRect.x;
            }
            if (newRect.h < 0)
            {
                newRect.y = newRect.y + newRect.h;
                newRect.h = rectangleCoordinates.y - newRect.y;
            }
            SDL_FillRect(windowSurface, &newRect, SDL_MapRGB(windowSurface->format, r, g, b));
            SDL_UpdateWindowSurface(window);
        }
    }

    destroyWindow();
    return 0;
}