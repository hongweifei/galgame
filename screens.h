
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "gui.h"
#include "graphics.h"
#include "message.h"

#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED

static SDL_Event event;
static int quit = 0;

static int check = 0;

static Message* msg;
/*
static int game_message_N;
static int game_message_type;
static char** game_message_tag;
static char** game_message_path;
static char** game_message_name;
static char** game_message_word;
*/

void scene(char* tag,char* path)
{
    message_add(msg,SCENE,"tp",tag,path);
    return;
}

void show(char* tag,char* path)
{
    message_add(msg,SHOW,"tp",tag,path);
    return;
}

void hide(char* tag)
{}

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
    init_graphics();
    init_gui(renderer);
}

void mainloop()
{
    int i,talk_n = 0,talk_now = 0;
    char** information[msg->type_list_N];
    int* information_type = calloc(1,sizeof(int));
    int* information_talk = calloc(1,sizeof(int));

    printf("mainloop now\n");

    for (i = 0; i < msg->type_list_N; i++)
    {
        information_type = realloc(information_type,sizeof(int) * (i + 1));

        information[i] = message_get(msg);
        information_type[i] = msg->type;

        if(information_type[i] == TALK)
        {
            information_talk = realloc(information_talk,sizeof(int) * (talk_n + 1));
            information_talk[talk_n] = i;
            talk_n++;
        }
    }

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (GameState == GAMESTATE_GAME)
                    {
                        if ((talk_now + 1) < talk_n)
                            talk_now++;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                for (i = 0; i < 7; i++)
                {
                     if(collision(mouse_x,mouse_y,1,1,label_position[i].x,label_position[i].y,label_position[i].w,label_position[i].h))
                     {
                          if (i == LABEL_START)
                              label_state = LABEL_STATE_START;
                          else if(i == LABEL_LOAD)
                              label_state = LABEL_STATE_LOAD;
                          else if(i == LABEL_PREFERENCES)
                              label_state = LABEL_STATE_PREFERENCES;
                          else if(i == LABEL_ABOUT)
                              label_state = LABEL_STATE_ABOUT;
                          else if(i == LABEL_HELP)
                              label_state = LABEL_STATE_HELP;
                          else if(i == LABEL_QUIT)
                          {
                              label_state = LABEL_STATE_QUIT;
                              quit = 1;
                          }
                          else if(i == LABEL_RETURN)
                              label_state = LABEL_STATE_RETURN;
                     }
                }
                break;
            }
        }

        SDL_GetMouseState(&mouse_x,&mouse_y);

        SDL_RenderClear(renderer);

        if (GameState == GAMESTATE_GAME)
        {
            for (i = 0; i < msg->type_list_N; i++)
            {
                if (information_type[i] == SCENE)
                    render_scene(information[i][TYPE_TAG],information[i][TYPE_PATH]);
                else if(information_type[i] == SHOW)
                    render_picture(information[i][TYPE_TAG],information[i][TYPE_PATH]);
            }

            render_text(information[information_talk[talk_now]][TYPE_NAME],information[information_talk[talk_now]][TYPE_WORD]);
        }

        render_gui(renderer,window_title,window_width,window_height);

        SDL_RenderPresent(renderer);
    }

    for (i = 0;i < sceneN;i++)
    {
        SDL_FreeSurface(scene_surface[i]);
        SDL_DestroyTexture(scene_texture[i]);
    }
    for (i = 0; i < showN; i++)
    {
        SDL_FreeSurface(show_surface[i]);
        SDL_DestroyTexture(show_texture[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif
