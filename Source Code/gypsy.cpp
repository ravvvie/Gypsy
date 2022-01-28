#include "Objects.h"



gypsy::gypsy(SDL_Renderer* rend)
{
    vec_dstrct.h = 150;
    vec_dstrct.w = 200;
    vec_dstrct.x = 240;
    vec_dstrct.y = 250;

    if (!change_static(SDL_SCANCODE_S, 1, rend))
        throw - 1;

    if (!change_sprite(SDL_SCANCODE_S, 1, rend))
        throw - 2;

    if (!change_sprite(SDL_SCANCODE_D, 1, rend))
        throw - 3;

    if (!change_sprite(SDL_SCANCODE_A, 1, rend))
        throw - 4;

    if (!change_sprite(SDL_SCANCODE_W, 1, rend))
        throw - 5;

    coin.count_coin_rect.x += 100;
    coin.coin_rect.w = 70;
    coin.coin_rect.h = 70;
    coin.coin_texture = TextureManager::TextureService(".\\images\\Coin\\money.png", rend);
    coin.coin_count_font_size = 60;
    coin.coin_count_font_color = { 255, 255, 255, 255 };
    coin.coin_count_font = TTF_OpenFont(".\\Font\\BRADHITC.TTF", coin.coin_count_font_size);
    if (coin.coin_count_font == nullptr)
        throw - 6;


    coin.count_coin_texture = TextureManager::TextureRender_score_coin(coin.coin_count_font, rend, coin.coin_count, coin.coin_count_font_color);
    SDL_QueryTexture(coin.count_coin_texture, NULL, NULL, &coin.count_coin_rect.w, &coin.count_coin_rect.h);
    if (coin.count_coin_texture == nullptr)
        throw - 7;

}

gypsy::~gypsy()
{
    if (body.player_texture_back != nullptr)
        SDL_DestroyTexture(body.player_texture_back);
    if (body.player_texture_forward != nullptr)
        SDL_DestroyTexture(body.player_texture_forward);
    if (body.player_texture_left != nullptr)
        SDL_DestroyTexture(body.player_texture_left);
    if (body.player_texture_right != nullptr)
        SDL_DestroyTexture(body.player_texture_right);
    if (player_texture_static != nullptr)
        SDL_DestroyTexture(player_texture_static);
    if (coin.coin_texture != nullptr)
        SDL_DestroyTexture(coin.coin_texture);
    if (coin.count_coin_texture != nullptr)
        SDL_DestroyTexture(coin.count_coin_texture);
    if (coin.coin_count_font != nullptr)
        TTF_CloseFont(coin.coin_count_font);
}

void gypsy::copy_Rect(int what, SDL_Rect* current)
{
    switch (what)
    {
        case(1):
        {
            current->x = 580;
            current->y = 600;
            current->w = coin.coin_rect.w;
            current->h = coin.coin_rect.h;
            break;
        }
        case(2):
        {
            current->x = 660;
            current->y = 600;
            current->w = coin.count_coin_rect.w;
            current->h = coin.count_coin_rect.h;
            break;
        }
    }
}

void gypsy::move(bool coordin, bool direct)
{
    if (coordin == true)
        if (direct == true)
            vec_dstrct.x = (vec_dstrct.x + 8);
        else
            vec_dstrct.x = (vec_dstrct.x - 8);
    else
        if (direct == true)
            vec_dstrct.y = (vec_dstrct.y - 8);
        else
            vec_dstrct.y = (vec_dstrct.y + 8);
    //std::cout << "x = " << vec_dstrct.x << "  " << "y = " << vec_dstrct.y << std::endl;
}


bool gypsy::change_sprite(int mode, int state, SDL_Renderer* rend)
{
    bool check = true;
    switch (mode)
    {
        case (SDL_SCANCODE_S):
        {
            SDL_DestroyTexture(body.player_texture_forward);
            switch (state)
            {
            case(1):
            {
                body.player_texture_forward = TextureManager::TextureService(".\\images\\Sprites_Walk\\face walk - 2.png", rend);
                if (body.player_texture_forward == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                body.player_texture_forward = TextureManager::TextureService(".\\images\\Sprites_Walk\\face walk - 1.png", rend);
                if (body.player_texture_forward == nullptr)
                    check = false;
                break;
            }
            }

            break;
        }
        case(SDL_SCANCODE_W):
        {
            SDL_DestroyTexture(body.player_texture_back);
            switch (state)
            {
            case(1):
            {
                body.player_texture_back = TextureManager::TextureService(".\\images\\Sprites_Walk\\back walk - 2.png", rend);
                if (body.player_texture_back == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                body.player_texture_back = TextureManager::TextureService(".\\images\\Sprites_Walk\\back walk - 1.png", rend);
                if (body.player_texture_back == nullptr)
                    check = false;
                break;
            }
            }
            break;
        }
        case(SDL_SCANCODE_D):
        {
            SDL_DestroyTexture(body.player_texture_right);
            switch (state)
            {
            case(1):
            {
                body.player_texture_right = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk r - 1.png", rend);
                if (body.player_texture_right == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                body.player_texture_right = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk r - 2.png", rend);
                if (body.player_texture_right == nullptr)
                    check = false;
                break;
            }
            case(3):
            {
                body.player_texture_right = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk r - 3( end).png", rend);
                if (body.player_texture_right == nullptr)
                    check = false;
                break;
            }
            break;
            }
            break;
        }
        case(SDL_SCANCODE_A):
        {
            SDL_DestroyTexture(body.player_texture_left);
            switch (state)
            {
            case(1):
            {
                body.player_texture_left = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk l - 1 .png", rend);
                if (body.player_texture_left == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                body.player_texture_left = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk l - 2.png", rend);
                if (body.player_texture_left == nullptr)
                    check = false;
                break;
            }
            case(3):
            {
                body.player_texture_left = TextureManager::TextureService(".\\images\\Sprites_Walk\\walk l - 3 (end).png", rend);
                if (body.player_texture_left == nullptr)
                    check = false;
                break;
            }
            break;
            }
            break;
        }
    }
    return check;
}


bool gypsy::change_static(int orientation, int state, SDL_Renderer* rend)
{
    bool check = true;
    switch (orientation)
    {
        case (SDL_SCANCODE_S):
        {
            SDL_DestroyTexture(player_texture_static);
            switch (state)
            {
            case(1):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\face idle - 2.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\face idle - 1.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            }
            break;
        }
        case (SDL_SCANCODE_W):
        {
            SDL_DestroyTexture(player_texture_static);
            switch (state)
            {
            case(1):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\back idle - 2.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\back idle - 1.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            }
            break;
        }
        case (SDL_SCANCODE_D):
        {
            SDL_DestroyTexture(player_texture_static);
            switch (state)
            {
            case(1):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\idle r - 2.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\idle r - 1.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            }
            break;
        }
        case (SDL_SCANCODE_A):
        {
            SDL_DestroyTexture(player_texture_static);
            switch (state)
            {
            case(1):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\idle l - 2.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            case(2):
            {
                player_texture_static = TextureManager::TextureService(".\\images\\Sprites_Idle\\idle l - 1.png", rend);
                if (player_texture_static == nullptr)
                    check = false;
                break;
            }
            }
            break;
        }
    }
    return check;
}

void gypsy::check_block()
{
    if (vec_dstrct.x < -72)
    {
        vec_dstrct.x += 8;
    }
    
    if (vec_dstrct.y < 118)
    {
        vec_dstrct.y += 8;
    }

    if (vec_dstrct.y > 582)
    {
        vec_dstrct.y -= 8;
    }

    if (vec_dstrct.x > 1152)
        vec_dstrct.x -= 8;    
}

int gypsy::update(SDL_Renderer* rend, int count, int check)
{
    switch (count)
    {
    case(1):
    {
        if (key[SDL_SCANCODE_S])
        {
            count_y_s++;
            if (count_y_s % 4 == 0)
                if (!change_sprite(SDL_SCANCODE_S, count_y_s / 3, rend))
                    return -50;
            if (SDL_RenderCopy(rend, body.player_texture_forward, NULL, GetdstRect()) < 0)
                return -11;
        }
        if (key[SDL_SCANCODE_W])
        {
            count_y_w++;
            if (count_y_w % 4 == 0)
                if (!change_sprite(SDL_SCANCODE_W, count_y_w / 3, rend))
                    return -51;

            if (SDL_RenderCopy(rend, body.player_texture_back, NULL, GetdstRect()) < 0)
                return -12;
        }
        if (key[SDL_SCANCODE_A])
        {
           
            count_x_a++;
            if (count_x_a % 3 == 0)
                if (!change_sprite(SDL_SCANCODE_A, count_x_a / 3, rend))
                    return -52;

            if (SDL_RenderCopy(rend, body.player_texture_left, NULL, GetdstRect()) < 0)
                return -13;
        }
        if (key[SDL_SCANCODE_D])
        {
           
            count_x_d++;
            if (count_x_d % 3 == 0)
                if (!change_sprite(SDL_SCANCODE_D, count_x_d / 3, rend))
                    return -53;

            if (SDL_RenderCopy(rend, body.player_texture_right, NULL, GetdstRect()) < 0)
                return -14;
        }
        break;
    }
    case(2):
    {
        if ((key[SDL_SCANCODE_D] && key[SDL_SCANCODE_A]) || (key[SDL_SCANCODE_W] && key[SDL_SCANCODE_S]))
        {
            if (SDL_RenderCopy(rend, player_texture_static, NULL, GetdstRect()) < 0)
                return -15;
        }
        else
        {
            if (key[SDL_SCANCODE_D])
            {
                count_x_d++;
                if (count_x_d % 3 == 0)
                    if (!change_sprite(SDL_SCANCODE_D, count_x_d / 3, rend))
                        return -54;
                if (SDL_RenderCopy(rend, body.player_texture_right, NULL, GetdstRect()) < 0)
                    return -16;
            }
            if (key[SDL_SCANCODE_A])
            {
                count_x_a++;
                if (count_x_a % 3 == 0)
                    if (!change_sprite(SDL_SCANCODE_A, count_x_a / 3, rend))
                        return -55;
                if (SDL_RenderCopy(rend, body.player_texture_left, NULL, GetdstRect()) < 0)
                    return -17;
            }
        }
        break;
    }

    case(3):
    {
        if (key[SDL_SCANCODE_D] && key[SDL_SCANCODE_A])
        {
            if (key[SDL_SCANCODE_W])
            {
                count_y_w++;
                if (count_y_w % 4 == 0)
                    if (!change_sprite(SDL_SCANCODE_W, count_y_w / 3, rend))
                        return -56;
                if (SDL_RenderCopy(rend, body.player_texture_back, NULL, GetdstRect()) < 0)
                    return -18;
            }
            if (key[SDL_SCANCODE_S])
            {
                count_y_s++;
                if (count_y_s % 4 == 0)
                    if (!change_sprite(SDL_SCANCODE_S, count_y_s / 3, rend))
                        return -57;
                if (SDL_RenderCopy(rend, body.player_texture_forward, NULL, GetdstRect()) < 0)
                    return -19;
            }
        }

        if (key[SDL_SCANCODE_W] && key[SDL_SCANCODE_S])
        {
            if (key[SDL_SCANCODE_D])
            {
                count_x_d++;
                if (count_x_d % 3 == 0)
                    if (!change_sprite(SDL_SCANCODE_D, count_x_d / 3, rend))
                        return -58;
                if (SDL_RenderCopy(rend, body.player_texture_right, NULL, GetdstRect()) < 0)
                    return -20;
            }
            if (key[SDL_SCANCODE_A])
            {
                count_x_a++;
                if (count_x_a % 3 == 0)
                    if (!change_sprite(SDL_SCANCODE_A, count_x_a / 3, rend))
                        return -59;
                if (SDL_RenderCopy(rend, body.player_texture_left, NULL, GetdstRect()) < 0)
                    return -21;
            }
        }
        break;
    }
    case(4):
    {
        if (SDL_RenderCopy(rend, player_texture_static, NULL, GetdstRect()) < 0)
            return -22;
        break;
    }


    case(0):
    {
        count_static++;
        if (count_static % 7 == 0)
            if (check == SDL_SCANCODE_S)
            {
                if (!change_static(check, count_static / 7, rend))
                    return -60;
            }
            else
                if (!change_static(check, count_static / 7, rend))
                    return -61;
        if (SDL_RenderCopy(rend, player_texture_static, NULL, GetdstRect()) < 0)
            return -23;
        break;
    }
    }

    if (count_static == 14)
        count_static = 0;
    if (count_y_w == 8)
        count_y_w = 0;
    if (count_y_s == 8)
        count_y_s = 0;
    if (count_x_a == 9)
        count_x_a = 0;
    if (count_x_d == 9)
        count_x_d = 0;

    return 1;
}