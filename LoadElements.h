#ifndef LOADELEMENTS_H_INCLUDED
#define LOADELEMENTS_H_INCLUDED

#include "SDL functions.h"
#include "Key Press.h"

using namespace std;

void LoadMenu(void);

void LoadGame(SDL_Renderer* &renderer);

void LoadBag (SDL_Event event, SDL_Renderer* &renderer, SDL_Texture* &img, SDL_Rect* &bag);

void LoadFruits (int time, SDL_Renderer* &renderer, SDL_Rect* &BagRect, int &score, int &life);

struct fruits
{
    SDL_Rect *rect = NULL;
    int speed;
    bool appeared;
    int imagecode;
    SDL_Texture *img = NULL;


    fruits();

    ~fruits();
};


void RenewFruit (fruits &fruit);    //make fruit falls again

void RenewAllFruits();

bool touched(SDL_Rect* &fruitRect , SDL_Rect* &BagRect);   //check if fruit touches the bag

void ShowStatus(SDL_Renderer* &renderer, int score, int life, TTF_Font* &font); //show score and lives remaining

bool ContinueGame(SDL_Renderer* &renderer); //load GameOver box and continue?


//enum PictureID
//{
//    apple = 0,
//    banana, cherry, durian,
//    figfruit, grapefruit, kiwi,
//    lemon, musklemon, orange,
//    papaya, passionfruit, peach,
//    pear, strawberry, watermelon
//};



#endif // LOADELEMENTS_H_INCLUDED
