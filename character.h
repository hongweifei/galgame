
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "message.h"

#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

typedef struct
{
    char* name;
}Character;

Character character_new(char* name)
{
    Character character;

    character.name = name;

    return character;
}

void say(Character character,char* text)
{
    message_add(msg,TALK,"nw",character.name,text);
}

#endif //CHARACTER_H_INCLUDED
