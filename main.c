
#include "screens.h"

void display()
{
    show("sylvie","./images/sylvie/sylvie blue giggle.png",334,700);
}

int main()
{
    CreateWindow("demo",1280,720);
    mainloop(&display);

    return 0;
}
