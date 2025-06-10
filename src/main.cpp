#include "system/include/Game.h"
#include "system/include/constants.h"

int main ()
{
    Game g { "Pong Program", screen_width, screen_height };
    g.start ();
}
