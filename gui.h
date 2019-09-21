
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#define GUI_N 3
#define GUI_BACKGROUND 0
#define GUI_MAIN_MENU 1
#define GUI_GAME_MENU 2

#define LABEL_START 0
#define LABEL_LOAD 1
#define LABEL_PREFERENCES 2
#define LABEL_ABOUT 3
#define LABEL_HELP 4
#define LABEL_QUIT 5
#define LABEL_RETURN 6

#define LABEL_STATE_NONE 0
#define LABEL_STATE_START 1
#define LABEL_STATE_LOAD 2
#define LABEL_STATE_PREFERENCES 3
#define LABEL_STATE_ABOUT 4
#define LABEL_STATE_HELP 5
#define LABEL_STATE_QUIT 6
#define LABEL_STATE_RETURN 7

static TTF_Font* font;
static SDL_Texture* texture_text;

static SDL_Texture* texture[GUI_N];

SDL_Rect label_position[7];
int label_state = LABEL_STATE_NONE;

int collision(int x1,int y1,int width1,int height1,int x2,int y2,int width2,int height2)
{
    if((y1 + height1 > y2 && y1 + height1 < y2 + height2 && x1 + width1 > x2 && x1 < x2 + width2) || //stand
       (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 > y2)) //
    {
        return 1;
    }

    if((y1 < y2 + height2 && y1 + height1 > y2 && x1 < x2 + width2 && x1 > x2) || //left
        (y1 < y2 + height2 && y1 + height1 > y2 && x1 + width1 > x2 && x1 + width1 < x2 + width2))//right
    {
        return 1;
    }

    return 0;
}

static SDL_Texture* init_img(SDL_Renderer* renderer,char* path)
{
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect rect;

    surface = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);

    return texture;
}
static SDL_Rect init_rect(int x,int y,int width,int height)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    return rect;
}
void draw(SDL_Renderer* renderer,SDL_Texture* texture,int x,int y,int width,int height)
{
    SDL_Rect rect = {x,y,width,height};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

SDL_Rect draw_text(SDL_Renderer* renderer,char* text,int x,int y,SDL_Color color)
{
    SDL_Surface* surface_text = TTF_RenderText_Solid(font,text,color);
    texture_text = SDL_CreateTextureFromSurface(renderer,surface_text);

    SDL_Rect dest = {x,y,surface_text->w,surface_text->h};

    SDL_RenderCopy(renderer,texture_text,NULL,&dest);

    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);

    return dest;
}

void gui_init(SDL_Renderer* renderer)
{
    TTF_Init();
    font = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",20);

    texture[GUI_BACKGROUND] = init_img(renderer,"./gui/main_menu.png");
    texture[GUI_MAIN_MENU] = init_img(renderer,"./gui/overlay/main_menu.png");
    texture[GUI_GAME_MENU] = init_img(renderer,"./gui/overlay/game_menu.png");
}


#endif //GUI_H_INCLUDED
