
#include "gal.h"

void display()
{
    scene("bg","./images/bg/bg meadow.jpg");
    show("sylvie","./images/sylvie/sylvie blue giggle.png");
}

int main()
{
    CreateWindow("demo",1280,720);
    mainloop(&display);

    return 0;
}
