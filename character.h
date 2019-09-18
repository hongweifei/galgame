
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "screens.h"

typedef struct
{
    char* name;
    SDL_Color color;
}Character;

void show(char* path)
{
    int lengh = sizeof(path) / sizeof(char);
    
    show_path = realloc(show_path,sizeof(char*) * (showN + 1));
    show_path[showN] = calloc(lengh,sizeof(char));

    show_path[showN] = path;

    showN++;
}
