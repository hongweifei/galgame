

#include "gal.h"

Character* s,*m;

void game()
{
    scene("bg","./images/bg/bg meadow.jpg");
    show("sylvie","./images/sylvie/sylvie blue giggle.png");

    say(s,"I am 15 years old");
    say(s,"My name is Sylvie");
    say(s,"I like playing computer games");
    say(s,"What is your name?");
    say(m,"Oh,I am Fly");

    scene("bg","./images/bg/bg club.jpg");
    show("sylvie","./images/sylvie/sylvie green giggle.png");
    //show("sylvie","./images/sylvie/sylvie blue giggle.png");

    say(s,"I watched <Naruto>  yesterday");
    say(m,"Me too");

    //scene("uni","./images/bg/bg uni.jpg");
    show("sylvie","./images/sylvie/sylvie green surprised.png");

    say(m,"Did you like to play basketball");
    say(s,"No,I did not like");
}

int main()
{
    CreateWindow("A  demo",1280,720);

    s = character_new("Sylvie");
    m = character_new("Me");

    game();

    mainloop();

    return 0;
}
