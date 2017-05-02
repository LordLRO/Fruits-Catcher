
#include "LoadElements.h"
#include "SDL functions.h"
#include "Key Press.h"

string fruitsLink[16] =
{
    "img/apple.png", "img/banana.png", "img/cherry.png",
    "img/durian.png", "img/figfruit.png", "img/grapefruit.png",
    "img/kiwi.png", "img/lemon.png", "img/muskmelon.png",
    "img/orange.png", "img/papaya.png", "img/passionfruit.png",
    "img/peach.png", "img/pear.png", "img/strawberry.png",
    "img/watermelon.png"
};

fruits::fruits()
    {
        rect = new SDL_Rect;
        rect->y = 0;
        appeared = false;
        img = nullptr;
    }

fruits::~fruits()
    {
        delete rect;
        SDL_DestroyTexture(img);
    }

bool ContinueGame(SDL_Renderer* &renderer)
{
    SDL_Rect *GameOverRect = new SDL_Rect, *ReplayRect = new SDL_Rect, *ExitRect = new SDL_Rect;
    GameOverRect = loadIMG("img/gameover.png", 75 , 25, 300, 300, renderer, GameOverRect);
    ReplayRect = loadIMG("img/playagain.png", 50 , 350, 150, 150, renderer, ReplayRect);
    ExitRect = loadIMG("img/x.png", 250, 350, 150, 150, renderer, ExitRect);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool choosing = true;
    while (choosing)
    {
        MouseAxis static mouse;
        GetMouseClick(event, mouse);
        if (ObjectClicked(ReplayRect, mouse) == true)
        {
            delete (GameOverRect);
            delete (ReplayRect);
            delete (ExitRect);
            return 1;
        }

        else
        if (ObjectClicked(ExitRect, mouse) == true)
        {

            delete (GameOverRect);
            delete (ReplayRect);
            delete (ExitRect);
            return 0;
        }

    }
}

void Load(void)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    initSDL(window, renderer);

    SDL_Rect *BackgroundRect = nullptr, *StartRect = nullptr, *ExitRect = nullptr;
    BackgroundRect = new SDL_Rect;
    StartRect = new SDL_Rect;
    ExitRect = new SDL_Rect;
    BackgroundRect = loadIMG("img/menuback.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, BackgroundRect);
    StartRect = loadIMG("img/gamestart.png", 25 , 160, 400, 200, renderer, StartRect);
    ExitRect = loadIMG("img/gameexit.png", 125, 420, 200, 100, renderer, ExitRect);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    SDL_SetWindowGrab(window, SDL_TRUE );
    bool gameRunning = true;
    while (gameRunning)
    {
        MouseAxis static mouse;
        GetMouseClick(event, mouse);
        if (ObjectClicked(StartRect, mouse) == true)
        {
            bool gameLoad = true;
            while(gameLoad)
            {
                LoadGame(renderer);
                if (ContinueGame(renderer) == false)
                {
                    gameRunning = false;
                    gameLoad = false;
                }
                else
                {
                    SDL_RenderClear(renderer);
                    RenewAllFruits();
                }
            }
        }
        else
        if (ObjectClicked(ExitRect, mouse) == true) gameRunning = false;
    }
    quitSDL(window, renderer);
    SDL_free(BackgroundRect);
    SDL_free(StartRect);
    SDL_free(ExitRect);

}

void LoadGame(SDL_Renderer* &renderer)
{
    SDL_Rect *BackgroundRect = nullptr;
    SDL_Rect *BagRect = nullptr;
    BackgroundRect = new SDL_Rect;
    BagRect = new SDL_Rect;
    SDL_Texture *backgroundimage = nullptr, *bagimage = nullptr;
    backgroundimage = IMG_LoadTexture(renderer, "img/back.jpg");
    bagimage = IMG_LoadTexture(renderer, "img/bag1.png");

    TTF_Font *font = nullptr;
    SetFont(font);

    int timeOfEvent = SDL_GetTicks();
    SDL_Event event;
    int score = 0;
    int life = 5;

    SDL_ShowCursor(0);

    bool gameRunning = true;

    while (gameRunning)
    {
            SDL_RenderClear(renderer);

            SDL_PollEvent(&event);

            BackgroundRect = loadIMG(backgroundimage, 0, 0, 450, 640, renderer, BackgroundRect);

            LoadBag(event, renderer, bagimage, BagRect);

            int timeSinceEvent = (SDL_GetTicks() - timeOfEvent);

            LoadFruits(timeSinceEvent, renderer, BagRect, score, life);

            ShowStatus(renderer, score, life, font);

            if (life <= 0) gameRunning = false;

            SDL_RenderPresent(renderer);

    }

    SDL_ShowCursor(1);
    SDL_free(BackgroundRect);
    SDL_free(BagRect);
    TTF_CloseFont(font);
    SDL_DestroyTexture(bagimage);
    SDL_DestroyTexture(backgroundimage);
}

fruits static fruit[15];
void LoadFruits (int time, SDL_Renderer* &renderer, SDL_Rect* &BagRect, int &score, int &life)
{
    for (int i = 0 ; i < 15 && fruit[i].appeared == true ; i++)
    {
        if ( touched(fruit[i].rect , BagRect) )
        {
            score++;
            RenewFruit(fruit[i]);
        }

        if ( (fruit[i].rect->y + fruit[i].speed) > SCREEN_HEIGHT - 50)
        {
            RenewFruit(fruit[i]);
            life--;
        }
        else if ( (fruit[i].rect->y + fruit[i].speed) <= SCREEN_HEIGHT)
        {
            if (fruit[i].img == nullptr) fruit[i].img = IMG_LoadTexture(renderer, fruitsLink[fruit[i].imagecode].c_str());
            fruit[i].rect->y += fruit[i].speed;
            fruit[i].rect = loadIMG(fruit[i].img, fruit[i].rect->x, fruit[i].rect->y, 50, 50, renderer, fruit[i].rect);
        }
    }

    if (time <= 30000)
        for ( int i = 0 ; i < 15 ; i++)
        {
            if ( i*2 < time/1000 && fruit[i].rect->y == 0 && fruit[i].appeared == false )
            {
                if (i <= 2)
                {
                    fruit[i].speed = i + 3;
                    fruit[i].rect->x = rand() % 400;
                    fruit[i].imagecode = rand() % 16;
                }
                if (i >= 3)
                {
                    fruit[i].speed = rand() % 8 + 5;
                    fruit[i].rect->x = rand() % 400;
                    fruit[i].imagecode = rand() % 16;
                }
                if (fruit[i].img == nullptr) fruit[i].img = IMG_LoadTexture(renderer, fruitsLink[fruit[i].imagecode].c_str());
                fruit[i].appeared = true;
                fruit[i].rect = loadIMG(fruit[i].img, fruit[i].rect->x, 0, 50, 50, renderer, fruit[i].rect);
            }

        }
}

void LoadBag (SDL_Event event, SDL_Renderer* &renderer, SDL_Texture* &img, SDL_Rect* &bag)
{
    int static bag_x = 150;
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_LEFT && bag_x > 0) bag_x -= 10; else
        if (event.key.keysym.sym == SDLK_RIGHT && bag_x < 300) bag_x += 10;
    }

    if (event.type == SDL_MOUSEMOTION)
    {
        if (event.motion.x >= 0 && event.motion.x <= SCREEN_WIDTH)
        {
            bag_x = event.motion.x;
            if (bag_x > 300) bag_x = 300;
        }
    }

    bag = loadIMG(img, bag_x, 560, 150, 75, renderer, bag);
}

void RenewFruit (fruits &fruit)
{
    fruit.speed = rand() % 5 + 3;
    fruit.rect->x = rand() % 400;
    fruit.rect->y = 0;
    fruit.imagecode = rand() % 16;
//    fruit.img = nullptr;
}

void RenewAllFruits()
{
    for (int i = 0; i < 15; i++)
    {
        fruit[i].appeared = false;
        fruit[i].rect->y = 0;
    }

}

bool touched(SDL_Rect* &fruitRect , SDL_Rect* &BagRect)
{
    if ( fruitRect->y + fruitRect->h <= BagRect->y || fruitRect->y >= BagRect->y + BagRect->h ) return 0;
    else
    {
        if ( (fruitRect->x < BagRect->x + BagRect->w && fruitRect->x > BagRect->x) ||
            (fruitRect->x < BagRect->x && fruitRect->x + fruitRect->w > BagRect->x) )
            return 1;
        else return 0;
    }
}

void ShowStatus(SDL_Renderer* &renderer,int score,int life, TTF_Font* &font)
{
    string ScoreStr = "Score:" + IntToString(score);
    string LifeStr = "Life: " + IntToString(life) ;

    SDL_Surface static *ScoreSurface;
    ScoreSurface = TTF_RenderText_Solid(font, ScoreStr.c_str(), GREEN); // TTF_RenderText_Solid could only be used on SDL_Surface -> create the surface first
    SDL_Texture static *ScoreTexture;
    ScoreTexture = SDL_CreateTextureFromSurface(renderer, ScoreSurface); //convert it into a texture
    SDL_Rect static *ScoreRect = setRect(330, 0, 100, 70, ScoreRect);
    SDL_RenderCopy(renderer, ScoreTexture, NULL, ScoreRect);
    SDL_FreeSurface(ScoreSurface);
    SDL_DestroyTexture(ScoreTexture);

    SDL_Surface static *LifeSurface;
    LifeSurface = TTF_RenderText_Solid(font, LifeStr.c_str(), RED);
    SDL_Texture static *LifeTexture;
    LifeTexture = SDL_CreateTextureFromSurface(renderer, LifeSurface);
    SDL_Rect static *LifeRect = setRect(15, 0, 80, 70, LifeRect);
    SDL_RenderCopy(renderer, LifeTexture, NULL, LifeRect);
    SDL_FreeSurface(LifeSurface);
    SDL_DestroyTexture(LifeTexture);

//    SDL_free(ScoreRect);
//    SDL_free(LifeRect);
//    SDL_free(LifeSurface);
//    SDL_free(ScoreSurface);
//    SDL_free(LifeTexture);
//    SDL_free(ScoreTexture);
}

