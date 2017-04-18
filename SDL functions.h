#ifndef SDL_FUNCTIONS_H_INCLUDED
#define SDL_FUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include<stdint.h>
#include <cstdlib>
#include <string>
#include <SDL.h>
#include <SDL_keycode.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include <SDL_image.h>

int const SCREEN_WIDTH = 450;
int const SCREEN_HEIGHT = 640;
int const FONT_SIZE = 20;

const SDL_Color CYAN = {0,255,255};
const SDL_Color BLUE = {0,0,255};
const SDL_Color ORANGE = {255,165,0};
const SDL_Color YELLOW = {255,255,0};
const SDL_Color LIME = {0,255,0};
const SDL_Color PURPLE = {128,0,128};
const SDL_Color RED = {255,0,0};
const SDL_Color WHITE = {255,255,255};
const SDL_Color BLACK = {0,0,0};
const SDL_Color GREEN = {0,128,0};

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal);     //Show errors

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);                         //Initialize Window and Renderer

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer);                         //Quit

SDL_Rect* loadIMG(string path, SDL_Renderer* &renderer, SDL_Rect* &rect);    //Load image to the renderer

SDL_Rect* loadIMG(SDL_Texture* img, int x,int y, int w, int h ,SDL_Renderer* &renderer, SDL_Rect* &rect);

SDL_Rect* loadIMG(string path, int x,int y, int w, int h ,SDL_Renderer* &renderer, SDL_Rect* &rect);

SDL_Rect* setRect(int x,int y, int w, int h, SDL_Rect* &rect);  //set Rectangle

string IntToString(int number);

void SetFont(TTF_Font* &font);

#endif // SDL_FUNCTIONS_H_INCLUDED
