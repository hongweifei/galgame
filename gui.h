
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#define GAMESTATE_MAIN 0
#define GAMESTATE_MENU_LOAD 1
#define GAMESTATE_MENU_PREFERENCES 2
#define GAMESTATE_MENU_ABOUT 3
#define GAMESTATE_MENU_HELP 4
#define GAMESTATE_GAME 5

#define GUI_N 3
#define GUI_BACKGROUND 0
#define GUI_MAIN_MENU 1
#define GUI_GAME_MENU 2

#define LABEL_N 7
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

static int GameState = GAMESTATE_MAIN;

int mouse_x = 0;
int mouse_y = 0;

TTF_Font* font_default;
TTF_Font* font_big;
TTF_Font* font_small;
static SDL_Texture* texture_text;

static SDL_Texture* texture[GUI_N];

SDL_Rect label_position[LABEL_N];
int label_state = LABEL_STATE_NONE;

SDL_Color color_gray = {136,136,136};
SDL_Color color_blue = {0,153,204};
SDL_Color color_white = {255,255,255};

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

SDL_Rect draw_text(SDL_Renderer* renderer,TTF_Font* text_font,char* text,int x,int y,SDL_Color color)
{
    SDL_Surface* surface_text = TTF_RenderText_Solid(text_font,text,color);
    texture_text = SDL_CreateTextureFromSurface(renderer,surface_text);

    SDL_Rect dest = {x,y,surface_text->w,surface_text->h};

    SDL_RenderCopy(renderer,texture_text,NULL,&dest);

    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);

    return dest;
}

int get_text_width(TTF_Font* text_font,char* text)
{
    SDL_Color color = {0,0,0};
    SDL_Surface* surface_text = TTF_RenderText_Solid(text_font,text,color);

    int width = surface_text->w;

    SDL_FreeSurface(surface_text);

    return width;
}

int get_text_height(TTF_Font* text_font,char* text)
{
    SDL_Color color = {0,0,0};
    SDL_Surface* surface_text = TTF_RenderText_Solid(text_font,text,color);

    int height = surface_text->h;

    SDL_FreeSurface(surface_text);

    return height;
}

void gui_init(SDL_Renderer* renderer)
{
    TTF_Init();
    font_default = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",20);
    font_big = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",48);
    font_small = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",14);

    texture[GUI_BACKGROUND] = init_img(renderer,"./gui/main_menu.png");
    texture[GUI_MAIN_MENU] = init_img(renderer,"./gui/overlay/main_menu.png");
    texture[GUI_GAME_MENU] = init_img(renderer,"./gui/overlay/game_menu.png");
}

void render_gui_label(SDL_Renderer* renderer,TTF_Font* text_font,int window_width,int window_height)
{
    if(label_state == LABEL_STATE_START)
    {
        draw_text(renderer,text_font,"Start Game",label_position[LABEL_START].x,label_position[LABEL_START].y,color_white);
        GameState = GAMESTATE_GAME;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_START].x,label_position[LABEL_START].y,label_position[LABEL_START].w,label_position[LABEL_START].h))
        draw_text(renderer,text_font,"Start Game",label_position[LABEL_START].x,label_position[LABEL_START].y,color_blue);
    else
        label_position[0] = draw_text(renderer,text_font,"Start Game",window_width / 30,window_height / 3.2,color_gray);

    if(label_state == LABEL_STATE_LOAD)
    {
        draw_text(renderer,text_font,"Load",label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_white);
        GameState = GAMESTATE_MENU_LOAD;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,label_position[LABEL_LOAD].w,label_position[LABEL_LOAD].h))
        draw_text(renderer,text_font,"Load",label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_blue);
    else
        label_position[LABEL_LOAD] = draw_text(renderer,text_font,"Load",window_width / 30,window_height / 2.6,color_gray);

    if(label_state == LABEL_STATE_PREFERENCES)
    {
        draw_text(renderer,text_font,"Preferences",label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_white);
        GameState = GAMESTATE_MENU_PREFERENCES;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,label_position[LABEL_PREFERENCES].w,label_position[LABEL_PREFERENCES].h))
        draw_text(renderer,text_font,"Preferences",label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_blue);
    else
        label_position[LABEL_PREFERENCES] = draw_text(renderer,text_font,"Preferences",window_width / 30,window_height / 2.2,color_gray);

    if(label_state == LABEL_STATE_ABOUT)
    {
        draw_text(renderer,text_font,"About",label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_white);
        GameState = GAMESTATE_MENU_ABOUT;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,label_position[LABEL_ABOUT].w,label_position[LABEL_ABOUT].h))
        draw_text(renderer,text_font,"About",label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_blue);
    else
        label_position[LABEL_ABOUT] = draw_text(renderer,text_font,"About",window_width / 30,window_height / 1.9,color_gray);

    if(label_state == LABEL_STATE_HELP)
    {
        draw_text(renderer,text_font,"Help",label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_white);
        GameState = GAMESTATE_MENU_HELP;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,label_position[LABEL_HELP].w,label_position[LABEL_HELP].h))
        draw_text(renderer,text_font,"Help",label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_blue);
    else
        label_position[LABEL_HELP] = draw_text(renderer,text_font,"Help",window_width / 30,window_height / 1.68,color_gray);

    if(label_state == LABEL_STATE_QUIT)
    {
        draw_text(renderer,text_font,"Quit",label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_white);
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,label_position[LABEL_QUIT].w,label_position[LABEL_QUIT].h))
        draw_text(renderer,text_font,"Quit",label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_blue);
    else
        label_position[LABEL_QUIT] = draw_text(renderer,text_font,"Quit",window_width / 30,window_height / 1.5,color_gray);

    if (GameState >= GAMESTATE_MENU_LOAD && GameState <= GAMESTATE_MENU_HELP)
    {
        if(label_state == LABEL_STATE_RETURN)
        {
            draw_text(renderer,text_font,"Return",label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_white);
            GameState = GAMESTATE_MAIN;
        }
        else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,label_position[LABEL_RETURN].w,label_position[LABEL_RETURN].h))
            draw_text(renderer,text_font,"Return",label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_blue);
        else
            label_position[LABEL_RETURN] = draw_text(renderer,text_font,"Return",window_width / 30,window_height / 1.2,color_gray);
    }
}

void render_gui_lable_load(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,"Load",width / 25,height / 20,color_blue);
}

void render_gui_lable_Preferences(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,"Preferences",width / 25,height / 20,color_blue);
}

void render_gui_lable_about(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,"About",width / 25,height / 20,color_blue);
}

void render_gui_lable_help(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,"Help",width / 25,height / 20,color_blue);
}

void render_gui_label_game(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,"Back",width / 3.5,height - get_text_height(text_font,"Back"),color_gray);
    draw_text(renderer,text_font,"History",width / 3,height - get_text_height(text_font,"History"),color_gray);
    draw_text(renderer,text_font,"Skip",width / 2.5,height - get_text_height(text_font,"Skip"),color_gray);
    draw_text(renderer,text_font,"Auto",width / 2.2,height - get_text_height(text_font,"Auto"),color_gray);
    draw_text(renderer,text_font,"Save",width / 2,height - get_text_height(text_font,"Save"),color_gray);
    draw_text(renderer,text_font,"Q.Save",width / 1.8,height - get_text_height(text_font,"Q.Save"),color_gray);
    draw_text(renderer,text_font,"Q.Load",width / 1.6,height - get_text_height(text_font,"Q.Load"),color_gray);
    draw_text(renderer,text_font,"Preferences",width / 1.45,height - get_text_height(text_font,"Preferences"),color_gray);
}

void render_gui(SDL_Renderer* renderer,char* title,int window_width,int window_height)
{
    int i;

    if (GameState == GAMESTATE_MAIN)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_MAIN_MENU],0,0,window_width,window_height);
        draw_text(renderer,font_big,title,window_width / 1.01 - get_text_width(font_big,title),window_height / 1.2,color_blue);

        render_gui_label(renderer,font_default,window_width,window_height);
    }
    else if (GameState == GAMESTATE_MENU_LOAD)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label(renderer,font_default,window_width,window_height);
        render_gui_lable_load(renderer,font_big,window_width,window_height);
    }
    else if (GameState == GAMESTATE_MENU_PREFERENCES)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label(renderer,font_default,window_width,window_height);
        render_gui_lable_Preferences(renderer,font_big,window_width,window_height);
    }
    else if (GameState == GAMESTATE_MENU_ABOUT)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label(renderer,font_default,window_width,window_height);
        render_gui_lable_about(renderer,font_big,window_width,window_height);
    }
    else if (GameState == GAMESTATE_MENU_HELP)
    {
        draw(renderer,texture[GUI_BACKGROUND],0,0,window_width,window_height);
        draw(renderer,texture[GUI_GAME_MENU],0,0,window_width,window_height);

        render_gui_label(renderer,font_default,window_width,window_height);
        render_gui_lable_help(renderer,font_big,window_width,window_height);
    }
    else if (GameState == GAMESTATE_GAME)
    {
        draw(renderer,texture[],0,window_height - window_height / 3.9,window_width,window_height / 3.9);

        render_gui_label_game(renderer,font_small,window_width,window_height);
    }

}

#endif //GUI_H_INCLUDED
