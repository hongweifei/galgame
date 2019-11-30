

#include "gal.h"

Character s;

void game()
{
    scene("bg","./images/bg/bg meadow.jpg");
    show("sylvie","./images/sylvie/sylvie blue giggle.png");

    say(s,"I am a 15-year-old girl");
    say(s,"My name is");
    say(s,"S");
    say(s,"y");
    say(s,"l");
    say(s,"v");
    say(s,"i");
    say(s,"e");
}

int main()
{
    CreateWindow("demo",1280,720);

    s = character_new("Sylvie");

    game();

    mainloop();

    return 0;
}
