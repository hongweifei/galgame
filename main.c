
#include "gal.h"

Character m;

void game()
{
    scene("bg","./images/bg/bg meadow.jpg");
    show("sylvie","./images/sylvie/sylvie blue giggle.png");

    say(m,"i am a sb.");
    say(m,"i am 12 years old.");
}

int main()
{
    CreateWindow("demo",1280,720);

    m = character_new("weifei",0,200,200);

    game();

    mainloop();

    return 0;
}
