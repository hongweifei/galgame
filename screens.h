

#include "window.h"
#include "gui.h"
#include "graphics.h"
#include "message.h"
#include "character.h"

#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED

#define PAST_SCENE 0
#define PAST_CHARACTER 1
#define PAST_TALK 2

static SDL_Event event;
static int quit = 0;
static int check = 0;

static int now = 0;
static int past[9] = {0,1,0,0,0,0,0,0,0};

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
}

void show(char* tag,char* path)
{
    message_add(msg,SHOW,"tp",tag,path);
}

void hide(char* tag)
{}

void mainloop()
{
    int i;
    int scene_n = 0,scene_now = 0;
    int talk_n = 0,talk_now = 0;
    char** information[msg->type_list_N];
    //int* information_type = malloc(sizeof(int));

    printf("mainloop now\n");

    for (i = 0; i < msg->type_list_N; i++)
    {
        //information_type = realloc(information_type,sizeof(int) * (i + 1));

        information[i] = message_get(msg);
        //information_type[i] = msg->type;
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
                //if (event.button.button == SDL_BUTTON_LEFT)
                break;
            case SDL_MOUSEBUTTONUP:
                if (GameState != GAMESTATE_GAME)
                {
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
                }
              else if (GameState == GAMESTATE_GAME)
              {
                  now++;
                  if (now >= msg->type_list_N)
                  {
                      GameState = GAMESTATE_GAMEOVER;
                  }

                  /*
                    if (scene_n > 1 && msg->type_list[information_talk[talk_now] + 1] == SCENE)
                        scene_now++;

                    if ((talk_now + 1) < talk_n)
                        talk_now++;
                    else if ((talk_now + 1) >= talk_n)
                        GameState = GAMESTATE_GAMEOVER;*/
              }
              break;
            }
        }

        SDL_GetMouseState(&mouse_x,&mouse_y);

        const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
        if (keyboard_state[SDL_SCANCODE_ESCAPE])
        {
            printf("<ESCAPE> is pressed.\n");
            quit = 1;
        }

        SDL_RenderClear(renderer);

        if (GameState == GAMESTATE_GAME)
        {
            render_scene(information[past[PAST_SCENE]][TYPE_TAG],information[past[PAST_SCENE]][TYPE_PATH]);
            render_picture(information[past[PAST_CHARACTER]][TYPE_TAG],information[past[PAST_CHARACTER]][TYPE_PATH]);

            if (msg->type_list[now] == SCENE)
            {
                past[PAST_SCENE] = now;
                now++;
            }
            else if (msg->type_list[now] == SHOW)
            {
                past[PAST_CHARACTER] = now;
                now++;
            }
            else if (msg->type_list[now] == TALK)
            {
                past[PAST_TALK] = now;
                render_text(information[past[PAST_TALK]][TYPE_NAME],information[past[PAST_TALK]][TYPE_WORD]);
            }
        }
        else if (GameState == GAMESTATE_GAMEOVER)
        {
            draw_text(renderer,font_big,"Game Over",window_width / 2 - get_text_width(font_big,"Game Over") / 2,window_height / 2 - get_text_height(font_big,"Game Over"),color_white);
        }

        render_gui(renderer,window_title,window_width,window_height);

        SDL_RenderPresent(renderer);
    }

    free(information);
    DestoryWindow();
}

#endif
