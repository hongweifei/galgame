

#include "window.h"
#include "gui.h"

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

static SDL_Renderer* renderer = NULL;

static int sceneN = 0;
static char** scene_tag;
static char** scene_path;
static SDL_Surface** scene_surface = NULL;
static SDL_Texture** scene_texture = NULL;

static int showN = 0;
static char** show_tag;
static char** show_path;
static SDL_Rect* show_rect;
static SDL_Surface** show_surface = NULL;
static SDL_Texture** show_texture = NULL;

static TTF_Font* font_name;
static TTF_Font* font_text;

void init_graphics()
{
    TTF_Init();
    font_name = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",36);
    font_text = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",24);

    show_tag = (char**)malloc(sizeof(char*));
    show_path = (char**)malloc(sizeof(char*));
    show_rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
}

void render_scene(char* tag,char* path)
{
    int i,new = 1;
    int lengh_tag = sizeof(tag) / sizeof(char);
    int lengh_path = sizeof(path) / sizeof(char);

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
                return;
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
}

void render_picture(char* tag,char* path)
{
    int i,new = 1;
    int lengh_tag = sizeof(tag) / sizeof(char);
    int lengh_path = sizeof(path) / sizeof(char);

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

void render_text(char* name,char* text)
{
    SDL_Color color_name = {0,200,200};
    SDL_Color color_text = {255,255,255};

    draw(renderer,texture[GUI_TEXTBOX],0,window_height - window_height / 3.9,window_width,window_height / 3.9);

    draw_text(renderer,font_name,name,window_width / 5.2,window_height - window_height / 3.9,color_name);
    draw_text(renderer,font_text,text,window_width / 4.7,window_height - window_height / 5.5,color_text);
}

















#endif //GRAPHICS_H_INCLUDED
