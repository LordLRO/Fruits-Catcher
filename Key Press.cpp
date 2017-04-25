
#include "Key Press.h"

SDL_Keycode KeyPressed(SDL_Event &e)
{
    while (true)
    {
        if ( SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN )
            return e.key.keysym.sym;
    }
}


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && ( e.type == SDL_QUIT || e.type == SDL_KEYDOWN) )
            return;
        SDL_Delay(100);
    }
}

void GetMouseClick(SDL_Event &event, MouseAxis &mouse)
{
    while (true)
    {
        if ( SDL_PollEvent(&event) != 0 && event.type == SDL_MOUSEBUTTONDOWN )
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            mouse.x = x;
            mouse.y = y;
            return;
        }

    }
}

bool ObjectClicked(SDL_Rect* &rect, MouseAxis &mouse)
{
    bool inside = true;

        //Mouse is left of the button
        if( mouse.x < rect->x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( mouse.x > rect->x + rect->w )
        {
            inside = false;
        }
        //Mouse above the button
        else if( mouse.y < rect->y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( mouse.y > rect->y + rect->h )
        {
            inside = false;
        }

        return inside;
}
