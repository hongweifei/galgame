
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED

static SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
static SDL_Surface* surface = NULL;
static SDL_Texture* texture = NULL;
static SDL_Event event;
static int quit = 0;

int showN = 0;
char** show_path = (char**)calloc(sizeof(char*));

void mainloop()
{
    int i;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:quit = 1;
                break;
            }
        }

        SDL_RenderClear(renderer);

        for (i = 0; i < showN; i++)
        {
            surface = IMG_Load(show_path[i]);
            texture = SDL_CreateTextureFromSurface(renderer,surface);

            SDL_RenderCopy(renderer,texture,NULL,NULL);
        }

        SDL_RenderPresent(renderer);
    }
}

#endif









