#include "system/include/Game.h"
#include "system/include/constants.h"

int main ()
{
    Game g { "Safe Zone", screen_width, screen_height };
    g.start ();
}
