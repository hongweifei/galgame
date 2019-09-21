
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gui.h"

#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED

#define GAMESTATE_MAIN 0
#define GAMESTATE_MENU_LOAD 1
#define GAMESTATE_MENU_PREFERENCES 2
#define GAMESTATE_MENU_ABOUT 3
#define GAMESTATE_MENU_HELP 4

static SDL_Window* window = NULL;
static int window_width = 0;
static int window_height = 0;
static int mouse_x = 0;
static int mouse_y = 0;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;
static int quit = 0;

static int GameState = GAMESTATE_MAIN;

static int sceneN = 0;
static char** scene_tag;
static char** scene_path;
static SDL_Surface** scene_surface = NULL;
static SDL_Texture** scene_texture = NULL;
static int scene_draw = 0,scene_finish = 0;

static int showN = 0;
static char** show_tag;
static char** show_path;
static SDL_Rect* show_rect;
static SDL_Surface** show_surface = NULL;
static SDL_Texture** show_texture = NULL;

SDL_Color color_gray = {136,136,136};
SDL_Color color_blue = {0,153,204};
SDL_Color color_white = {255,255,255};

void scene(char* tag,char* path)
{
    int i,new = 1;
    int lengh_tag = sizeof(tag) / sizeof(char);
    int lengh_path = sizeof(path) / sizeof(char);

    scene_draw = 1;

    for (i = 0; i < sceneN; i++)
    {
        if (scene_tag[i] == tag)
        {
            if (scene_path[i] != path)
            {
                SDL_FreeSurface(scene_surface[i]);
                scene_surface[i] = IMG_Load(scene_path[i]);
                scene_texture[i] = SDL_CreateTextureFromSurface(renderer,scene_surface[i]);
            }

            new = 0;
        }

        SDL_RenderCopy(renderer,scene_texture[i],NULL,NULL);

        if (i == sceneN - 1)
        {
            if (!new)
            {
                scene_finish = 1;
                return;
            }
            else
                break;
        }
    }

    scene_tag = realloc(scene_tag,sizeof(char*) * (sceneN + 1));
    scene_tag[sceneN] = calloc(lengh_tag,sizeof(char));

    scene_path = realloc(scene_path,sizeof(char*) * (sceneN + 1));
    scene_path[sceneN] = calloc(lengh_path,sizeof(char));

    scene_tag[sceneN] = tag;
    scene_path[sceneN] = path;

    sceneN++;

    scene_surface = (SDL_Surface**)realloc(scene_surface,sizeof(SDL_Surface*) * sceneN);
    scene_texture = (SDL_Texture**)realloc(scene_texture,sizeof(SDL_Texture*) * sceneN);

    scene_surface[sceneN - 1] = IMG_Load(path);
    scene_texture[sceneN - 1] = SDL_CreateTextureFromSurface(renderer,scene_surface[sceneN - 1]);

    SDL_RenderCopy(renderer,scene_texture[sceneN - 1],NULL,NULL);

    scene_finish = 1;
}

void show(char* tag,char* path)
{
    int i,new = 1;
    int lengh_tag = sizeof(tag) / sizeof(char);
    int lengh_path = sizeof(path) / sizeof(char);

    if (scene_draw)
        if (!scene_finish)
            return;

    for (i = 0; i < showN; i++)
    {
        if (show_tag[i] == tag)
        {
            if (show_path[i] != path)
            {
                SDL_FreeSurface(show_surface[i]);
                show_surface[i] = IMG_Load(show_path[i]);
                show_texture[i] = SDL_CreateTextureFromSurface(renderer,show_surface[i]);
                show_rect[i].w = show_surface[i]->w;
                show_rect[i].h = show_surface[i]->h;
            }

            new = 0;
        }

        SDL_RenderCopy(renderer,show_texture[i],NULL,&show_rect[i]);

        if (i == showN - 1)
        {
            if (!new)
                return;
            else
                break;
        }
    }

    show_surface = (SDL_Surface**)realloc(show_surface,sizeof(SDL_Surface*) * (showN + 1));
    show_texture = (SDL_Texture**)realloc(show_texture,sizeof(SDL_Texture*) * (showN + 1));

    show_surface[showN] = IMG_Load(path);
    show_texture[showN] = SDL_CreateTextureFromSurface(renderer,show_surface[showN]);

    show_tag = realloc(show_tag,sizeof(char*) * (showN + 1));
    show_tag[showN] = calloc(lengh_tag,sizeof(char));

    show_path = realloc(show_path,sizeof(char*) * (showN + 1));
    show_path[showN] = calloc(lengh_path,sizeof(char));

    show_rect = realloc(show_rect,sizeof(SDL_Rect) * (showN + 1));

    show_tag[showN] = tag;
    show_path[showN] = path;
    show_rect[showN].x = window_width / 2 - show_surface[showN]->w / 2;
    show_rect[showN].y = window_height - show_surface[showN]->h;
    show_rect[showN].w = show_surface[showN]->w;
    show_rect[showN].h = show_surface[showN]->h;

    showN++;

    SDL_RenderCopy(renderer,show_texture[showN - 1],NULL,&show_rect[showN - 1]);
}

void hide(char* tag)
{

}

void render_gui_label()
{
    if(label_state == LABEL_STATE_START)
    {
        draw_text(renderer,"Start Game",label_position[LABEL_START].x,label_position[LABEL_START].y,color_white);
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_START].x,label_position[LABEL_START].y,label_position[LABEL_START].w,label_position[LABEL_START].h))
        draw_text(renderer,"Start Game",label_position[LABEL_START].x,label_position[LABEL_START].y,color_blue);
    else
        label_position[0] = draw_text(renderer,"Start Game",window_width / 30,window_height / 3.2,color_gray);

    if(label_state == LABEL_STATE_LOAD)
    {
        draw_text(renderer,"Load",label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_white);
        GameState = GAMESTATE_MENU_LOAD;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,label_position[LABEL_LOAD].w,label_position[LABEL_LOAD].h))
        draw_text(renderer,"Load",label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_blue);
    else
        label_position[LABEL_LOAD] = draw_text(renderer,"Load",window_width / 30,window_height / 2.6,color_gray);

    if(label_state == LABEL_STATE_PREFERENCES)
    {
        draw_text(renderer,"Preferences",label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_white);
        GameState = GAMESTATE_MENU_PREFERENCES;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,label_position[LABEL_PREFERENCES].w,label_position[LABEL_PREFERENCES].h))
        draw_text(renderer,"Preferences",label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_blue);
    else
        label_position[LABEL_PREFERENCES] = draw_text(renderer,"Preferences",window_width / 30,window_height / 2.2,color_gray);

    if(label_state == LABEL_STATE_ABOUT)
    {
        draw_text(renderer,"About",label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_white);
        GameState = GAMESTATE_MENU_ABOUT;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,label_position[LABEL_ABOUT].w,label_position[LABEL_ABOUT].h))
        draw_text(renderer,"About",label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_blue);
    else
        label_position[LABEL_ABOUT] = draw_text(renderer,"About",window_width / 30,window_height / 1.9,color_gray);

    if(label_state == LABEL_STATE_HELP)
    {
        draw_text(renderer,"Help",label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_white);
        GameState = GAMESTATE_MENU_HELP;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,label_position[LABEL_HELP].w,label_position[LABEL_HELP].h))
        draw_text(renderer,"Help",label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_blue);
    else
        label_position[LABEL_HELP] = draw_text(renderer,"Help",window_width / 30,window_height / 1.68,color_gray);

    if(label_state == LABEL_STATE_QUIT)
    {
        draw_text(renderer,"Quit",label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_white);
        quit = 1;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,label_position[LABEL_QUIT].w,label_position[LABEL_QUIT].h))
        draw_text(renderer,"Quit",label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_blue);
    else
        label_position[LABEL_QUIT] = draw_text(renderer,"Quit",window_width / 30,window_height / 1.5,color_gray);

    if (GameState >= GAMESTATE_MENU_LOAD && GameState <= GAMESTATE_MENU_HELP)
    {
        if(label_state == LABEL_STATE_RETURN)
        {
            draw_text(renderer,"Return",label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_white);
            GameState = GAMESTATE_MAIN;
        }
        else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,label_position[LABEL_RETURN].w,label_position[LABEL_RETURN].h))
            draw_text(renderer,"Return",label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_blue);
        else
            label_position[LABEL_RETURN] = draw_text(renderer,"Return",window_width / 30,window_height / 1.2,color_gray);
    }
}

void render_gui()
{
    int i;

    if (GameState == GAMESTATE_MAIN)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);

        render_gui_label();
    }
    else if (GameState == GAMESTATE_MENU_LOAD)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label();
    }
    else if (GameState == GAMESTATE_MENU_PREFERENCES)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label();
    }
    else if (GameState == GAMESTATE_MENU_ABOUT)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label();
    }
    else if (GameState == GAMESTATE_MENU_HELP)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label();
    }
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

    gui_init(renderer);
}

void mainloop(void (*DisplayFunction)())
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
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
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
                            label_state = LABEL_STATE_QUIT;
                          else if(i == LABEL_RETURN)
                            label_state = LABEL_STATE_RETURN;
                          break;
                       }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:

                break;
            }
        }

        SDL_GetMouseState(&mouse_x,&mouse_y);

        SDL_RenderClear(renderer);

        render_gui();

        DisplayFunction();
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
