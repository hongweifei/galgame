
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED

static SDL_Window* window = NULL;
static int window_width = 0;
static int window_height = 0;
static SDL_Renderer* renderer = NULL;
static SDL_Surface** surface = NULL;
static SDL_Texture** texture = NULL;
static SDL_Event event;

static int showN = 0;
static char** show_tag;
static char** show_path;
static SDL_Rect* show_rect;

void show(char* tag,char* path,int width,int height)
{
    int i;
    int lengh_tag = sizeof(tag) / sizeof(char);
    int lengh_path = sizeof(path) / sizeof(char);

    SDL_RenderClear(renderer);

    for (i = 0; i < showN; i++)
    {
        if (show_tag[i] == tag)
        {
            if (show_path[i] != path)
            {
                SDL_FreeSurface(surface[i]);
                surface[i] = IMG_Load(show_path[i]);
                texture[i] = SDL_CreateTextureFromSurface(renderer,surface[i]);
                show_rect[i].w = width;
                show_rect[i].h = height;
            }
        }

        SDL_RenderCopy(renderer,texture[i],NULL,&show_rect[i]);

        if (i == showN - 1)
        {
            SDL_RenderPresent(renderer);
            return;
        }
    }

    show_tag = realloc(show_tag,sizeof(char*) * (showN + 1));
    show_tag[showN] = calloc(lengh_tag,sizeof(char));

    show_path = realloc(show_path,sizeof(char*) * (showN + 1));
    show_path[showN] = calloc(lengh_path,sizeof(char));

    show_rect = realloc(show_rect,sizeof(SDL_Rect) * (showN + 1));

    show_tag[showN] = tag;
    show_path[showN] = path;
    show_rect[showN].x = window_width / 2 - width / 2;
    show_rect[showN].y = window_height - height;
    show_rect[showN].w = width;
    show_rect[showN].h = height;

    showN++;

    surface = (SDL_Surface**)realloc(surface,sizeof(SDL_Surface*) * showN);
    texture = (SDL_Texture**)realloc(texture,sizeof(SDL_Texture*) * showN);

    surface[showN - 1] = IMG_Load(path);
    texture[showN - 1] = SDL_CreateTextureFromSurface(renderer,surface[showN - 1]);

    SDL_RenderCopy(renderer,texture[showN - 1],NULL,&show_rect[showN - 1]);
    SDL_RenderPresent(renderer);
}

void hide(char* tag)
{

}

void CreateWindow(const char* title,int width,int height)
{
    SDL_Init(SDL_INIT_TIMER || SDL_INIT_GAMECONTROLLER || SDL_INIT_EVENTS);
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    window_width = width;
    window_height = height;

    show_tag = (char**)malloc(sizeof(char*));
    show_path = (char**)malloc(sizeof(char*));
    show_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
}

void mainloop(void (*DisplayFunction)())
{
    int i;

    int quit = 0;

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

        DisplayFunction();
    }

    for (i = 0; i < showN; i++)
    {
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(texture[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

#endif
