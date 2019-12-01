

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "message.h"
#include "gui.h"
#include "graphics.h"

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

static SDL_Window* window = NULL;
static char* window_title;
static int window_width = 0;
static int window_height = 0;

static Message* msg;

void CreateWindow(const char* title,int width,int height)
{
    SDL_Init(SDL_INIT_TIMER || SDL_INIT_GAMECONTROLLER || SDL_INIT_EVENTS);
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    window_title = (char*)title;
    window_width = width;
    window_height = height;

    msg = message_new();
/*
    game_message_N = 0;
    game_message_type = NONE;

    game_message_tag = malloc(sizeof(char*));
    game_message_path = malloc(sizeof(char*));
    game_message_name = malloc(sizeof(char*));
    game_message_word = malloc(sizeof(char*));

    game_message_tag[game_message_N] = calloc(1,sizeof(char));
    game_message_path[game_message_N] = calloc(1,sizeof(char));
    game_message_name[game_message_N] = calloc(1,sizeof(char));
    game_message_word[game_message_N] = calloc(1,sizeof(char));
*/
    init_graphics(window_width,window_height);
    init_gui(renderer);
}

void DestoryWindow()
{
    free(window_title);
    free(msg);

    release_gui();
    release_graphics();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif
