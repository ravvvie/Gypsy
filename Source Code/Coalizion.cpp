#include "Objects.h"

int check_differ_coordinate(SDL_Rect* hero, SDL_Rect* NPS)
{
    if (hero->y - NPS->y < 65)
        return 1;
    else
        return 2;
}

bool check_differ_coalizion(SDL_Rect* hero, SDL_Rect* NPS, int mode)
{
    switch (mode)
    {
    case(1):
    {
        if (hero->x - NPS->x <= 40 && hero->x - NPS->x >= -55)
        {
            if (hero->y - NPS->y >= -70 && hero->y - NPS->y <= 72)
            {
                return true;
            }
        }
        break;
    }
    case(2):
    {
        if (hero->x - NPS->x <= 200 && hero->x - NPS->x >= -180)
        {
            if (hero->y - NPS->y >= -180 && hero->y - NPS->y <= 200)
            {
                return true;
            }
        }
        break;
    }
    case(3):
    {
        if (hero->x - NPS->x <= 72 && hero->x - NPS->x >= -124)
        {
            if (hero->y - NPS->y >= -78 && hero->y - NPS->y <= 142)
            {
                return true;
            }
        }
        break;
    }
    }
    return false;
}

void check_position(NPS_default* checking, NPS_default* guy1, NPS_default* guy2, NPS_default* guy3, NPS_default* guy4, NPS_default* guy5, gypsy* hero)
{
    bool quit = false;
    int  i = 0;
    while (!quit)
    {
        if (!check_differ_coalizion(checking->GetdstRect(), guy1->GetdstRect(), 2))
            i++;
        if (!check_differ_coalizion(checking->GetdstRect(), guy2->GetdstRect(), 2))
            i++;
        if (!check_differ_coalizion(checking->GetdstRect(), guy3->GetdstRect(), 2))
            i++;
        if (!check_differ_coalizion(checking->GetdstRect(), guy4->GetdstRect(), 2))
            i++;
        if (!check_differ_coalizion(checking->GetdstRect(), guy5->GetdstRect(), 2))
            i++;
        if (!check_differ_coalizion(hero->GetdstRect(), checking->GetdstRect(), 1))
            i++;
        if (i == 6)
            quit = true;
        else
        {
            i = 0;
            checking->change_position();
        }

    }
}