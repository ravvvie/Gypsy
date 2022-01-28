#include "Objects.h"

Timer::Timer(SDL_Renderer* rend)
{
    timer_rect.x = 1280 - 150;
    Timer_font_Size = 64;
    Timer_color = { 255, 255, 255, 0 };
    timer_font = TTF_OpenFont(".\\Font\\BRADHITC.TTF", Timer_font_Size);
    if (timer_font == nullptr)
        throw - 10;
    timer = 30;
    out_timer << timer;
    timer_position = "0:" + out_timer.str();
    timer_texture = TextureManager::TextureRender_Text(rend, timer_position, timer_font, Timer_color);
    SDL_QueryTexture(timer_texture, NULL, NULL, &timer_rect.w, &timer_rect.h);
    if (timer_texture == nullptr)
        throw - 11;
}

void Timer::Change_Timer(SDL_Renderer* rend, int mode)
{
    int timer_hour{};
    int timer_sec{};
    int count{};
    timer_position = "";
    out_timer.str(std::string());
    SDL_DestroyTexture(timer_texture);
    switch (mode)
    {
        case(1):
        {
            timer--;
            break;
        }
        case(2):
        {
            timer += 3;
            break;
        }
    }
    if (timer == 0)
    {
        count++;
    }
    else
    {
        int timer_check = timer;
        timer_hour = timer / 60;
        timer_sec = timer % 60;
        while (timer_check > 0)
        {
            timer_check /= 10;
            count++;
        }
        switch (count)
        {
        case(1):
        {
            out_timer << timer_hour;
            timer_position = out_timer.str() + ":0";
            out_timer.str(std::string());
            out_timer << timer_sec;
            timer_position += out_timer.str();
            break;
        }
        case(2):
        {
            out_timer << timer_hour;
            timer_position = out_timer.str() + ":";
            out_timer.str(std::string());
            out_timer << timer_sec;
            timer_position += out_timer.str();
            break;
        }
        }
        timer_texture = TextureManager::TextureRender_Text(rend, timer_position, timer_font, Timer_color);
        SDL_QueryTexture(timer_texture, NULL, NULL, &timer_rect.w, &timer_rect.h);
        if (timer_texture == nullptr)
            throw - 12;
    }
}

Timer:: ~Timer()
{
    if (timer_texture != nullptr)
        SDL_DestroyTexture(timer_texture);
    if (timer_font != nullptr)
        TTF_CloseFont(timer_font);
}