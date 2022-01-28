#include "Systems.h"


int button_id{};
Mix_Music* genMusic = nullptr;

error_mess take;

SDL_MessageBoxData messageboxdata {
    SDL_MESSAGEBOX_ERROR, /* .flags */
        NULL, /* .window */
        "Error!", /* .title */
        nullptr, /* .message */
        SDL_arraysize(take.buttons), /* .numbuttons */
        take.buttons, /* .buttons */
        & take.colorScheme /* .colorScheme */
};

bool _Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if (TTF_Init() < 0)       
        return false;

    int flag = IMG_INIT_PNG;
    int init = IMG_Init(flag);
    if ((flag & init) != flag)
        return false;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
       return false;

    return true;
}
 
int Init_video(SDL_Window*& window, SDL_Surface*& surface, SDL_Renderer*& render)
{
    window = SDL_CreateWindow("Gypsy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window == NULL)
        return -2;
    else
        surface = SDL_GetWindowSurface(window);
        if (surface == NULL)
            return -3;
    render = SDL_CreateRenderer(window, -1, 0);
    if (render == NULL)
        return -4;
    else
        if (SDL_SetRenderDrawColor(render, 0x0, 0x0, 0x0, 0x0) < 0)
            return -5;
    SDL_Surface* surf = IMG_Load("_GYPSY.ico");
    SDL_SetWindowIcon(window, surf);
    SDL_FreeSurface(surf);
    return 0;
}

void exit(SDL_Window*& window, SDL_Renderer*& rend)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
}