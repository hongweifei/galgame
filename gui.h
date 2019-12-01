
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
#define GAMESTATE_GAMEOVER 6

#define GUI_N 4
#define GUI_BACKGROUND 0
#define GUI_MAIN_MENU 1
#define GUI_GAME_MENU 2
#define GUI_TEXTBOX 3

#define LABEL_N 7
#define LABEL_START 0
#define LABEL_LOAD 1
#define LABEL_PREFERENCES 2
#define LABEL_ABOUT 3
#define LABEL_HELP 4
#define LABEL_QUIT 5
#define LABEL_RETURN 6

#define LABEL_TEXT_START "Start"
#define LABEL_TEXT_LOAD "Load"
#define LABEL_TEXT_PREFERENCES "Preferences"
#define LABEL_TEXT_ABOUT "About"
#define LABEL_TEXT_HELP "Help"
#define LABEL_TEXT_QUIT "Quit"
#define LABEL_TEXT_RETURN "Return"

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

SDL_Texture* texture[GUI_N];

TTF_Font* font_default;
TTF_Font* font_big;
TTF_Font* font_small;

SDL_Texture** label_texture;
SDL_Rect label_position[LABEL_N];
int label_state = LABEL_STATE_NONE;

SDL_Color color_gray = {136,136,136};
SDL_Color color_blue = {0,153,204};
SDL_Color color_black = {0,0,0};
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

SDL_Rect draw(SDL_Renderer* renderer,SDL_Texture* texture,int x,int y,int width,int height)
{
    SDL_Rect rect = {x,y,width,height};
    SDL_RenderCopy(renderer,texture,NULL,&rect);

    return rect;
}

int get_text_width(TTF_Font* font,char* text)
{
    SDL_Color color = {0,0,0};
    SDL_Surface* surface_text = TTF_RenderText_Solid(font,text,color);

    int width = surface_text->w;

    SDL_FreeSurface(surface_text);

    return width;
}

int get_text_height(TTF_Font* font,char* text)
{
    SDL_Color color = {0,0,0};
    SDL_Surface* surface_text = TTF_RenderText_Solid(font,text,color);

    int height = surface_text->h;

    SDL_FreeSurface(surface_text);

    return height;
}

SDL_Texture* create_text(SDL_Renderer* renderer,TTF_Font* font,char* text,SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font,text,color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Rect draw_text(SDL_Renderer* renderer,TTF_Font* font,char* text,int x,int y,SDL_Color color)
{
    SDL_Texture* texture = create_text(renderer,font,text,color);

    SDL_Rect dest = {x,y,get_text_width(font,text),get_text_height(font,text)};

    SDL_RenderCopy(renderer,texture,NULL,&dest);

    SDL_DestroyTexture(texture);

    return dest;
}

void init_gui(SDL_Renderer* renderer)
{
    printf("init gui\n");

    TTF_Init();
    font_default = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",20);
    font_big = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",48);
    font_small = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",14);

    label_texture = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * LABEL_N);
    label_texture[LABEL_START] = create_text(renderer,font_default,LABEL_TEXT_START,color_gray);
    label_texture[LABEL_LOAD] = create_text(renderer,font_default,LABEL_TEXT_LOAD,color_gray);
    label_texture[LABEL_PREFERENCES] =  create_text(renderer,font_default,LABEL_TEXT_PREFERENCES,color_gray);
    label_texture[LABEL_ABOUT] =  create_text(renderer,font_default,LABEL_TEXT_ABOUT,color_gray);
    label_texture[LABEL_HELP] =  create_text(renderer,font_default,LABEL_TEXT_HELP,color_gray);
    label_texture[LABEL_QUIT] =  create_text(renderer,font_default,LABEL_TEXT_QUIT,color_gray);
    label_texture[LABEL_RETURN] =  create_text(renderer,font_default,LABEL_TEXT_RETURN,color_gray);

    texture[GUI_BACKGROUND] = init_img(renderer,"./gui/main_menu.png");
    texture[GUI_MAIN_MENU] = init_img(renderer,"./gui/overlay/main_menu.png");
    texture[GUI_GAME_MENU] = init_img(renderer,"./gui/overlay/game_menu.png");
    texture[GUI_TEXTBOX] = init_img(renderer,"./gui/textbox.png");
}

void render_gui_label(SDL_Renderer* renderer,TTF_Font* text_font,int window_width,int window_height)
{
    if(label_state == LABEL_STATE_START)
    {
        draw_text(renderer,text_font,LABEL_TEXT_START,label_position[LABEL_START].x,label_position[LABEL_START].y,color_white);
        GameState = GAMESTATE_GAME;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_START].x,label_position[LABEL_START].y,label_position[LABEL_START].w,label_position[LABEL_START].h))
        draw_text(renderer,text_font,LABEL_TEXT_START,label_position[LABEL_START].x,label_position[LABEL_START].y,color_blue);
    else
        label_position[0] = draw(renderer,label_texture[LABEL_START],window_width / 30,window_height / 3.2,get_text_width(text_font,LABEL_TEXT_START),get_text_height(text_font,LABEL_TEXT_START));

    if(label_state == LABEL_STATE_LOAD)
    {
        draw_text(renderer,text_font,LABEL_TEXT_LOAD,label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_white);
        GameState = GAMESTATE_MENU_LOAD;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,label_position[LABEL_LOAD].w,label_position[LABEL_LOAD].h))
        draw_text(renderer,text_font,LABEL_TEXT_LOAD,label_position[LABEL_LOAD].x,label_position[LABEL_LOAD].y,color_blue);
    else
        label_position[LABEL_LOAD] = draw(renderer,label_texture[LABEL_LOAD],window_width / 30,window_height / 2.6,get_text_width(text_font,LABEL_TEXT_LOAD),get_text_height(text_font,LABEL_TEXT_LOAD));

    if(label_state == LABEL_STATE_PREFERENCES)
    {
        draw_text(renderer,text_font,LABEL_TEXT_PREFERENCES,label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_white);
        GameState = GAMESTATE_MENU_PREFERENCES;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,label_position[LABEL_PREFERENCES].w,label_position[LABEL_PREFERENCES].h))
        draw_text(renderer,text_font,LABEL_TEXT_PREFERENCES,label_position[LABEL_PREFERENCES].x,label_position[LABEL_PREFERENCES].y,color_blue);
    else
        label_position[LABEL_PREFERENCES] = draw(renderer,label_texture[LABEL_PREFERENCES],window_width / 30,window_height / 2.2,get_text_width(text_font,LABEL_TEXT_PREFERENCES),
                                                get_text_height(text_font,LABEL_TEXT_PREFERENCES));

    if(label_state == LABEL_STATE_ABOUT)
    {
        draw_text(renderer,text_font,LABEL_TEXT_ABOUT,label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_white);
        GameState = GAMESTATE_MENU_ABOUT;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,label_position[LABEL_ABOUT].w,label_position[LABEL_ABOUT].h))
        draw_text(renderer,text_font,LABEL_TEXT_ABOUT,label_position[LABEL_ABOUT].x,label_position[LABEL_ABOUT].y,color_blue);
    else
        label_position[LABEL_ABOUT] = draw(renderer,label_texture[LABEL_ABOUT],window_width / 30,window_height / 1.9,get_text_width(text_font,LABEL_TEXT_ABOUT),get_text_height(text_font,LABEL_TEXT_ABOUT));

    if(label_state == LABEL_STATE_HELP)
    {
        draw_text(renderer,text_font,LABEL_TEXT_HELP,label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_white);
        GameState = GAMESTATE_MENU_HELP;
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,label_position[LABEL_HELP].w,label_position[LABEL_HELP].h))
        draw_text(renderer,text_font,LABEL_TEXT_HELP,label_position[LABEL_HELP].x,label_position[LABEL_HELP].y,color_blue);
    else
        label_position[LABEL_HELP] = draw(renderer,label_texture[LABEL_HELP],window_width / 30,window_height / 1.68,get_text_width(text_font,LABEL_TEXT_HELP),get_text_height(text_font,LABEL_TEXT_HELP));

    if(label_state == LABEL_STATE_QUIT)
    {
        draw_text(renderer,text_font,LABEL_TEXT_QUIT,label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_white);
    }
    else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,label_position[LABEL_QUIT].w,label_position[LABEL_QUIT].h))
        draw_text(renderer,text_font,LABEL_TEXT_QUIT,label_position[LABEL_QUIT].x,label_position[LABEL_QUIT].y,color_blue);
    else
        label_position[LABEL_QUIT] = draw(renderer,label_texture[LABEL_QUIT],window_width / 30,window_height / 1.5,get_text_width(text_font,LABEL_TEXT_QUIT),get_text_height(text_font,LABEL_TEXT_QUIT));

    if (GameState >= GAMESTATE_MENU_LOAD && GameState <= GAMESTATE_MENU_HELP)
    {
        if(label_state == LABEL_STATE_RETURN)
        {
            draw_text(renderer,text_font,LABEL_TEXT_RETURN,label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_white);
            GameState = GAMESTATE_MAIN;
        }
        else if (collision(mouse_x,mouse_y,1,1,label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,label_position[LABEL_RETURN].w,label_position[LABEL_RETURN].h))
            draw_text(renderer,text_font,LABEL_TEXT_RETURN,label_position[LABEL_RETURN].x,label_position[LABEL_RETURN].y,color_blue);
        else
            label_position[LABEL_RETURN] = draw(renderer,label_texture[LABEL_RETURN],window_width / 30,window_height / 1.2,get_text_width(text_font,LABEL_TEXT_RETURN),get_text_height(text_font,LABEL_TEXT_RETURN));
    }
}

void render_gui_lable_load(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,LABEL_TEXT_LOAD,width / 25,height / 20,color_blue);
}

void render_gui_lable_Preferences(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,LABEL_TEXT_PREFERENCES,width / 25,height / 20,color_blue);
}

void render_gui_lable_about(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,LABEL_TEXT_ABOUT,width / 25,height / 20,color_blue);
}

void render_gui_lable_help(SDL_Renderer* renderer,TTF_Font* text_font,int width,int height)
{
    draw_text(renderer,text_font,LABEL_TEXT_HELP,width / 25,height / 20,color_blue);
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
        render_gui_label_game(renderer,font_small,window_width,window_height);
    }

}

void release_gui()
{
    int i = 0;

    for (i = 0; i < LABEL_N; i++)
    {
        SDL_DestroyTexture(label_texture[i]);
    }
    for (i = 0;i < GUI_N;i++)
    {
        SDL_DestroyTexture(texture[i]);
    }
}









#endif //GUI_H_INCLUDED
