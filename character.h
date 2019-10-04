
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gui.h"
#include "event.h"

#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

static TTF_Font* font_character_name;
static TTF_Font* font_character_say;

typedef struct
{
    char* name;
    SDL_Texture* name_texture;
    SDL_Color color;
}Character;

Character character_new(char* name,int r,int g,int b)
{
    Character character;

    font_character_name = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",36);
    font_character_say = TTF_OpenFont("SourceHanSans-Light-Lite.ttf",24);

    character.color.r = r;
    character.color.g = g;
    character.color.b = b;

    character.name = name;

    character.name_texture = create_text(renderer,font_character_name,name,character.color);

    return character;
}

void say(Character character,char* text)
{
    SDL_Color color = {255,255,255};

    draw(renderer,texture[GUI_TEXTBOX],0,window_height - window_height / 3.9,window_width,window_height / 3.9);
    draw(renderer,character.name_texture,window_width / 5.2,window_height - window_height / 3.9,get_text_width(font_character_name,character.name),get_text_height(font_character_name,character.name));

    draw_text(renderer,font_character_say,text,window_width / 4.7,window_height - window_height / 5.5,color);

    //message_add(msg,TALK,"nw",character.name,text);
}

#endif //CHARACTER_H_INCLUDED
