#include "SDL functions.h"


void logSDLError(ostream& os, const string &msg, bool fatal = false)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
        {
            SDL_Quit();
            exit(1);
        }
}


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow("LordLRO - Fruits Catcher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
        logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}


SDL_Rect* loadIMG(string path ,SDL_Renderer* &renderer, SDL_Rect* &rect)
{
    SDL_Texture * img = nullptr;
    img = IMG_LoadTexture(renderer, path.c_str());
    SDL_RenderCopy(renderer, img, NULL, rect);
//    SDL_RenderPresent(renderer);                  //present the renderer -> the window
    return rect;
}

SDL_Rect* loadIMG(string path, int x,int y, int w, int h ,SDL_Renderer* &renderer, SDL_Rect* &rect)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    SDL_Texture* img = nullptr;
    img = IMG_LoadTexture(renderer, path.c_str());
    SDL_RenderCopy(renderer, img, NULL, rect);
    SDL_DestroyTexture(img);
//    SDL_RenderPresent(renderer);                  //present the renderer -> the window
    return rect;
}

SDL_Rect* loadIMG(SDL_Texture* img, int x,int y, int w, int h ,SDL_Renderer* &renderer, SDL_Rect* &rect)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
    SDL_RenderCopy(renderer, img, NULL, rect);
//    SDL_RenderPresent(renderer);                  //present the renderer -> the window
    return rect;
}

SDL_Rect* setRect(int x,int y, int w, int h, SDL_Rect* &rect)
{
    rect = new SDL_Rect;
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    return rect;
}

string IntToString(int number)
{
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

void SetFont(TTF_Font* &font)
{
    TTF_Init();
    if(font == nullptr)
    font = TTF_OpenFont("font/VAGRB__0.TTF", FONT_SIZE);
    if(font == nullptr)
    cout << "Error: " << TTF_GetError() << endl;
}


