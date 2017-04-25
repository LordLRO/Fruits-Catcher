#ifndef KEY_PRESS_H_INCLUDED
#define KEY_PRESS_H_INCLUDED

#include <SDL_keycode.h>
#include <SDL.h>

SDL_Keycode KeyPressed(SDL_Event&);  //return the key that user pressed

void waitUntilKeyPressed();  // delay until user press key

class MouseAxis
    {
    public:
        int x;
        int y;
    };
void GetMouseClick(SDL_Event &event, MouseAxis &mouse);

bool ObjectClicked(SDL_Rect* &rect, MouseAxis &mouse);

#endif // KEY_PRESS_H_INCLUDED
