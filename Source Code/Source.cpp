#include "Objects.h"


int main(int argc, char* argv[])
{
    srand(time(NULL));
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Renderer* render = nullptr;
    if (!_Init())
    {
        messageboxdata.message = SDL_GetError();
        if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
        {
            SDL_Log("error displaying message box");
            SDL_Log(SDL_GetError());
            std::cout << SDL_GetError() << std::endl;
        }
        if (button_id < 0)
        {
            SDL_Log("no selection of button \"OK\"");
        }
        return -1;
    }
    else
    {
        int init_vid = Init_video(window, surface, render);
        if (init_vid != 0)
        {
            messageboxdata.message = SDL_GetError();
            if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
            {
                SDL_Log("error displaying message box");
                SDL_Log(SDL_GetError());
                std::cout << SDL_GetError() << std::endl;
            }
            if (button_id < 0)
            {
                SDL_Log("no selection of button \"OK\"");
            }
            return init_vid;
        }

      
        if ((genMusic = Mix_LoadMUS(".\\msc\\east.mp3")) == nullptr)
        {
            messageboxdata.message = SDL_GetError();
            if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
            {
                SDL_Log("error displaying message box");
                SDL_Log(SDL_GetError());
                std::cout << SDL_GetError() << std::endl;
            }
            if (button_id < 0)
            {
                SDL_Log("no selection of button \"OK\"");
            }
            return -7;
        }

        Mix_VolumeMusic(30);

        int quit{};
        bool interim;
        bool quit_pause = false;
        bool quit_game_over = false;
        const int FPS = 60;
        const int frameDelay = 2500 / FPS;
        int counter{};
        int check_update{};
        Uint32 framestart;
        int frameTime;
        int check = SDL_SCANCODE_S;
        int value_check{};
        int check_move{};
        int check_render_menu{};

        _score buff_score;
        buff_score.nick_text = nullptr;
        buff_score.score_text = nullptr;
        int state_enter_nick;
        
        button_QTE QTE(render);
        gypsy alpha(render);
        Timer gameplay_timer(render);
        NPS_default micros[6]{ {render, 1} , {render,2} , {render, 3} , {render, 4} , {render , 3} , {render, 5} };
        Rating_Lst Score_LST(render);
        SDL_Rect coin_game_over{};
        SDL_Rect coin_game_over_message{};
        bool key_open_NPS[6] {false, false, false, false, false, false};
        check_position(&micros[0], &micros[1], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
        check_position(&micros[1], &micros[0], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
        check_position(&micros[2], &micros[1], &micros[0], &micros[3], &micros[4], &micros[5], &alpha);
        check_position(&micros[3], &micros[1], &micros[2], &micros[0], &micros[4], &micros[5], &alpha);
        check_position(&micros[4], &micros[1], &micros[2], &micros[3], &micros[0], &micros[5], &alpha);
        check_position(&micros[5], &micros[1], &micros[2], &micros[3], &micros[4], &micros[0], &alpha);
        int qte_cycle{};
        SDL_Texture* map = TextureManager::TextureService(".\\images\\map\\Demo_.png", render);
        std::ifstream if_score(".\\base\\score.db", std::ifstream::in | std::ifstream::app | std::ifstream::binary);
        if (!if_score.is_open())
            return 0;
        input_data(Score_LST, if_score, render);
        bool quit_game = false;

        SDL_Event glaive{};
        SDL_MouseButtonEvent glaive_mouse{};

        Main_Menu current_menu(render);
        int mouse_x{};
        int mouse_y{};

        while (!quit_game)
        {
            framestart = SDL_GetTicks();
            while (SDL_PollEvent(&glaive) != 0)
            {
                switch (glaive.type)
                {
                    case(SDL_QUIT):
                    {
                        exit(window, render);
                        return 0;
                    }
                    case SDL_KEYDOWN:
                    {
                        if (glaive.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                            quit_game = true;
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        glaive_mouse = glaive.button;
                        case (SDL_BUTTON_LEFT):
                        {

                            if (current_menu.key_state_buttons[0])
                            {
                                interim = false;
                                    while (!interim)
                                    {
                                        quit = 0;
                                        state_enter_nick = current_menu.enter_nickname(buff_score, render, map);
                                        if (state_enter_nick == 2)      
                                            break;
                                        if (state_enter_nick == 1)
                                        {
                                            quit_game = true;
                                            break;
                                        }
                                        if (state_enter_nick < 0)
                                        {
                                            messageboxdata.message = SDL_GetError();
                                            if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                                                SDL_Log("error displaying message box");
                                                SDL_Log(SDL_GetError());
                                                std::cout << SDL_GetError() << std::endl;

                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -4;
                                            }
                                        }
                                        current_menu.change_quit_pos(true);
                                        SDL_ShowCursor(SDL_DISABLE);
                                        while (quit == 0)
                                        {
                                            framestart = SDL_GetTicks();
                                            while (SDL_PollEvent(&glaive) != 0)
                                            {
                                                switch (glaive.type)
                                                {
                                                case (SDL_QUIT):
                                                {
                                                    exit(window, render);
                                                    return 0;
                                                }
                                                case SDL_KEYDOWN:
                                                {
                                                    if (glaive.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                                                    {
                                                        quit_pause = false;
                                                        SDL_ShowCursor(SDL_ENABLE);
                                                        while (!quit_pause)
                                                        {
                                                            while (SDL_PollEvent(&glaive) != 0)
                                                            {
                                                                switch (glaive.type)
                                                                {
                                                                case(SDL_QUIT):
                                                                {
                                                                    exit(window, render);
                                                                    return 0;
                                                                }
                                                                case SDL_MOUSEBUTTONDOWN:
                                                                {
                                                                    glaive_mouse = glaive.button;
                                                                    if (glaive_mouse.button == SDL_BUTTON_LEFT)
                                                                    {
                                                                        if (current_menu.key_state_buttons[1])
                                                                        {
                                                                            quit_pause = true;
                                                                            quit = 1;
                                                                        }
                                                                        if (current_menu.key_state_buttons[2])
                                                                        {
                                                                            quit_pause = true;
                                                                            SDL_ShowCursor(SDL_DISABLE);
                                                                        }

                                                                    }
                                                                    break;
                                                                }
                                                                }
                                                            }

                                                            if (Mix_PlayingMusic() == 0)
                                                                Mix_PlayMusic(genMusic, -1);

                                                            if (quit_pause == true)
                                                                continue;



                                                            SDL_GetMouseState(&mouse_x, &mouse_y);
                                                            for (int i = 2; i <= 3; i++)
                                                            {
                                                                current_menu.key_state_buttons[i - 1] = current_menu.mouse_detection(i, mouse_x, mouse_y);
                                                                if (current_menu.key_state_buttons[i - 1])
                                                                    current_menu.change_text_color(render, 2, i);
                                                                else
                                                                    current_menu.change_text_color(render, 1, i);
                                                            }

                                                            if (SDL_RenderClear(render) < 0)
                                                            {
                                                                messageboxdata.message = SDL_GetError();
                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                                                                    SDL_Log("error displaying message box");
                                                                    SDL_Log(SDL_GetError());
                                                                    std::cout << SDL_GetError() << std::endl;
                                                                }
                                                                if (button_id < 0)
                                                                {
                                                                    SDL_Log("no selection of button \"OK\"");
                                                                }
                                                                return -4;
                                                            }

                                                            if (SDL_RenderCopy(render, current_menu.Get_pause_texture(), NULL, current_menu.Get_pause_rect()) < 0)
                                                            {
                                                                messageboxdata.message = SDL_GetError();
                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                {
                                                                    SDL_Log("error displaying message box");
                                                                    SDL_Log(SDL_GetError());
                                                                    std::cout << SDL_GetError() << std::endl;
                                                                }
                                                                if (button_id < 0)
                                                                {
                                                                    SDL_Log("no selection of button \"OK\"");
                                                                }
                                                                return -135;
                                                            }

                                                            if (SDL_RenderCopy(render, current_menu.Get_continue_button_texture(), NULL, current_menu.Get_button_rect_continue()) < 0)
                                                            {
                                                                messageboxdata.message = SDL_GetError();
                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                {
                                                                    SDL_Log("error displaying message box");
                                                                    SDL_Log(SDL_GetError());
                                                                    std::cout << SDL_GetError() << std::endl;
                                                                }
                                                                if (button_id < 0)
                                                                {
                                                                    SDL_Log("no selection of button \"OK\"");
                                                                }
                                                                return -135;
                                                            }

                                                            if (SDL_RenderCopy(render, current_menu.Get_exit_button_texture(), NULL, current_menu.Get_button_rect_exit()) < 0)
                                                            {
                                                                messageboxdata.message = SDL_GetError();
                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                {
                                                                    SDL_Log("error displaying message box");
                                                                    SDL_Log(SDL_GetError());
                                                                    std::cout << SDL_GetError() << std::endl;
                                                                }
                                                                if (button_id < 0)
                                                                {
                                                                    SDL_Log("no selection of button \"OK\"");
                                                                }
                                                                return -135;
                                                            }


                                                            SDL_RenderPresent(render);

                                                            frameTime = SDL_GetTicks() - framestart;
                                                            if (frameDelay > frameTime)
                                                            {
                                                                SDL_Delay(frameDelay - frameTime);
                                                            }
                                                        }
                                                        break;
                                                    }

                                                    if (glaive.key.repeat == 0)
                                                    {
                                                        alpha.key[glaive.key.keysym.scancode] = true;
                                                        value_check = glaive.key.keysym.scancode;
                                                        if (value_check == SDL_SCANCODE_W || value_check == SDL_SCANCODE_S || value_check == SDL_SCANCODE_A || value_check == SDL_SCANCODE_D)
                                                            check_move = value_check;
                                                    }
                                                    break;
                                                }
                                                case SDL_KEYUP:
                                                {
                                                    if (glaive.key.repeat == 0)
                                                    {
                                                        alpha.key[glaive.key.keysym.scancode] = false;
                                                        value_check = glaive.key.keysym.scancode;
                                                        alpha.change_static(value_check, 1, render);
                                                        if (value_check == SDL_SCANCODE_W || value_check == SDL_SCANCODE_S || value_check == SDL_SCANCODE_A || value_check == SDL_SCANCODE_D)
                                                            check = value_check;
                                                    }
                                                    break;
                                                }
                                                }
                                            }

                                            if (Mix_PlayingMusic() == 0)
                                                Mix_PlayMusic(genMusic, -1);

                                            if (quit != 0)
                                                continue;


                                            if (alpha.key[SDL_SCANCODE_S])
                                            {
                                                alpha.move(0, 0);
                                                counter++;
                                            }
                                            if (alpha.key[SDL_SCANCODE_W])
                                            {

                                                alpha.move(0, 1);
                                                counter++;
                                            }
                                            if (alpha.key[SDL_SCANCODE_A])
                                            {
                                                alpha.move(1, 0);
                                                counter++;
                                            }
                                            if (alpha.key[SDL_SCANCODE_D])
                                            {
                                                alpha.move(1, 1);
                                                counter++;
                                            }

                                            alpha.check_block();


                                            if (SDL_RenderClear(render) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -3;
                                            }


                                            if (SDL_RenderCopy(render, map, NULL, NULL) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -101;
                                            }

                                            for (int i = 0; i < 6; i++)
                                            {
                                                if (key_open_NPS[i])
                                                {

                                                    micros[i].change_sprite(render);

                                                    if (check_differ_coordinate(alpha.GetdstRect(), micros[i].GetdstRect()) == 2)
                                                        if (SDL_RenderCopy(render, micros[i].get_Texture(), NULL, micros[i].GetdstRect()) < 0)
                                                        {
                                                            messageboxdata.message = SDL_GetError();
                                                            if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                            {
                                                                SDL_Log("error displaying message box");
                                                                SDL_Log(SDL_GetError());
                                                                std::cout << SDL_GetError() << std::endl;
                                                            }
                                                            if (button_id < 0)
                                                            {
                                                                SDL_Log("no selection of button \"OK\"");
                                                            }
                                                            return -110 - i;
                                                        }
                                                }
                                            }

                                            check_update = alpha.update(render, counter, check);

                                            if (check_update != 1)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return check_update;
                                            }



                                            for (int i = 0; i < 6; i++)
                                            {
                                                if (key_open_NPS[i])
                                                    if (check_differ_coordinate(alpha.GetdstRect(), micros[i].GetdstRect()) == 1)
                                                        if (SDL_RenderCopy(render, micros[i].get_Texture(), NULL, micros[i].GetdstRect()) < 0)
                                                        {
                                                            messageboxdata.message = SDL_GetError();
                                                            if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                            {
                                                                SDL_Log("error displaying message box");
                                                                SDL_Log(SDL_GetError());
                                                                std::cout << SDL_GetError() << std::endl;
                                                            }
                                                            if (button_id < 0)
                                                            {
                                                                SDL_Log("no selection of button \"OK\"");
                                                            }
                                                            return -116 - i;
                                                        }
                                            }

                                            counter = 0;

                                            if (SDL_RenderCopy(render, alpha.Get_Coin_Text(), NULL, alpha.Get_coin_rect()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }

                                            if (SDL_RenderCopy(render, alpha.Get_Coin_Count_Text(), NULL, alpha.Get_count_coin_rect()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -134;
                                            }

                                            if (SDL_RenderCopy(render, gameplay_timer.Get_timer_Texture(), NULL, gameplay_timer.Get_timer_Rect()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -134;
                                            }

                                            if (quit == 0)
                                                SDL_RenderPresent(render);

                                            for (int i = 0; i < 5; i++)
                                            {
                                                micros[i].push_count_ticks();
                                                if (micros[i].Get_count_ticks() >= micros[i].Get_ticks())
                                                {
                                                    micros[i].change_ticks(key_open_NPS[i]);
                                                    if (!key_open_NPS[i])
                                                    {
                                                        micros[i].change_position();
                                                        switch (i)
                                                        {
                                                        case(0):
                                                        {
                                                            check_position(&micros[0], &micros[1], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                                            break;
                                                        }
                                                        case(1):
                                                        {
                                                            check_position(&micros[1], &micros[0], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                                            break;
                                                        }
                                                        case(2):
                                                        {
                                                            check_position(&micros[2], &micros[1], &micros[0], &micros[3], &micros[4], &micros[5], &alpha);
                                                            break;
                                                        }
                                                        case(3):
                                                        {
                                                            check_position(&micros[3], &micros[1], &micros[2], &micros[0], &micros[4], &micros[5], &alpha);
                                                            break;
                                                        }
                                                        case(4):
                                                        {
                                                            check_position(&micros[4], &micros[1], &micros[2], &micros[3], &micros[0], &micros[5], &alpha);
                                                            break;
                                                        }
                                                        }
                                                    }
                                                }

                                                if (key_open_NPS[i])
                                                    if (check_differ_coalizion(alpha.GetdstRect(), micros[i].GetdstRect(), 1))
                                                    {
                                                        if (!key_open_NPS[5])
                                                        {
                                                            qte_cycle = 0;
                                                            while (qte_cycle == 0)
                                                            {
                                                                framestart = SDL_GetTicks();
                                                                if (SDL_RenderClear(render) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -4;
                                                                }

                                                                if (SDL_RenderCopy(render, map, NULL, NULL) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -133;
                                                                }

                                                                if (SDL_RenderCopy(render, alpha.Get_Coin_Text(), NULL, alpha.Get_coin_rect()) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -135;
                                                                }

                                                                if (SDL_RenderCopy(render, alpha.Get_Coin_Count_Text(), NULL, alpha.Get_count_coin_rect()) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -134;
                                                                }

                                                                if (SDL_RenderCopy(render, gameplay_timer.Get_timer_Texture(), NULL, gameplay_timer.Get_timer_Rect()) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -134;
                                                                }


                                                                for (int j = 0; j < 5; j++)
                                                                {
                                                                    if (key_open_NPS[j])
                                                                        if (check_differ_coordinate(alpha.GetdstRect(), micros[j].GetdstRect()) == 2)
                                                                            if (SDL_RenderCopy(render, micros[j].get_Texture(), NULL, micros[j].GetdstRect()) < 0)
                                                                            {
                                                                                messageboxdata.message = SDL_GetError();
                                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                                {
                                                                                    SDL_Log("error displaying message box");
                                                                                    SDL_Log(SDL_GetError());
                                                                                    std::cout << SDL_GetError() << std::endl;
                                                                                }
                                                                                if (button_id < 0)
                                                                                {
                                                                                    SDL_Log("no selection of button \"OK\"");
                                                                                }
                                                                                return -120 - j;
                                                                            }
                                                                }

                                                                if (SDL_RenderCopy(render, alpha.get_Texture(), NULL, alpha.GetdstRect()) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -125;
                                                                }

                                                                for (int j = 0; j < 5; j++)
                                                                {
                                                                    if (key_open_NPS[j])
                                                                        if (check_differ_coordinate(alpha.GetdstRect(), micros[j].GetdstRect()) == 1)
                                                                            if (SDL_RenderCopy(render, micros[j].get_Texture(), NULL, micros[j].GetdstRect()) < 0)
                                                                            {
                                                                                messageboxdata.message = SDL_GetError();
                                                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                                {
                                                                                    SDL_Log("error displaying message box");
                                                                                    SDL_Log(SDL_GetError());
                                                                                    std::cout << SDL_GetError() << std::endl;
                                                                                }
                                                                                if (button_id < 0)
                                                                                {
                                                                                    SDL_Log("no selection of button \"OK\"");
                                                                                }
                                                                                return -126 - j;
                                                                            }
                                                                }

                                                                if (SDL_RenderCopy(render, QTE.get_Texture(), NULL, QTE.GetdstRect()) < 0)
                                                                {
                                                                    messageboxdata.message = SDL_GetError();
                                                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                                    {
                                                                        SDL_Log("error displaying message box");
                                                                        SDL_Log(SDL_GetError());
                                                                        std::cout << SDL_GetError() << std::endl;
                                                                    }
                                                                    if (button_id < 0)
                                                                    {
                                                                        SDL_Log("no selection of button \"OK\"");
                                                                    }
                                                                    return -132;
                                                                }

                                                                SDL_RenderPresent(render);

                                                                if (SDL_PollEvent(&glaive) == 1)
                                                                {
                                                                    if (glaive.type == SDL_KEYUP)
                                                                    {
                                                                        if (glaive.key.repeat == 0)
                                                                        {
                                                                            alpha.key[glaive.key.keysym.scancode] = false;
                                                                            value_check = glaive.key.keysym.scancode;
                                                                            alpha.change_static(value_check, 1, render);
                                                                            if (value_check == SDL_SCANCODE_W || value_check == SDL_SCANCODE_S || value_check == SDL_SCANCODE_A || value_check == SDL_SCANCODE_D)
                                                                                check = value_check;
                                                                        }
                                                                    }
                                                                    if (glaive.type == SDL_KEYDOWN)
                                                                    {
                                                                        if (glaive.key.keysym.scancode == QTE.Get_button_ID())
                                                                        {
                                                                            qte_cycle = 1;
                                                                            QTE.change_button(render);
                                                                        }
                                                                        else
                                                                            if (glaive.key.keysym.scancode != SDL_SCANCODE_W && glaive.key.keysym.scancode != SDL_SCANCODE_S && glaive.key.keysym.scancode != SDL_SCANCODE_A && glaive.key.keysym.scancode != SDL_SCANCODE_D)
                                                                                qte_cycle = 2;
                                                                    }
                                                                }

                                                                QTE.push_count_ticks();
                                                                if (QTE.Get_count_ticks() >= QTE.Get_ticks())
                                                                    qte_cycle = 2;

                                                                frameTime = SDL_GetTicks() - framestart;
                                                                if (frameDelay > frameTime)
                                                                {
                                                                    SDL_Delay(frameDelay - frameTime);
                                                                }
                                                            }
                                                            if (qte_cycle == 2)
                                                            {
                                                                quit = 3;
                                                                break;
                                                            }
                                                            else
                                                            {
                                                                alpha.push_coin_count(render);
                                                                gameplay_timer.Change_Timer(render, 2);
                                                            }

                                                            micros[i].change_ticks(key_open_NPS[i]);
                                                            micros[i].change_position();
                                                            switch (i)
                                                            {
                                                            case(0):
                                                            {
                                                                check_position(&micros[0], &micros[1], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                                                break;
                                                            }
                                                            case(1):
                                                            {
                                                                check_position(&micros[1], &micros[0], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                                                break;
                                                            }
                                                            case(2):
                                                            {
                                                                check_position(&micros[2], &micros[1], &micros[0], &micros[3], &micros[4], &micros[5], &alpha);
                                                                break;
                                                            }
                                                            case(3):
                                                            {
                                                                check_position(&micros[3], &micros[1], &micros[2], &micros[0], &micros[4], &micros[5], &alpha);
                                                                break;
                                                            }
                                                            case(4):
                                                            {
                                                                check_position(&micros[4], &micros[1], &micros[2], &micros[3], &micros[0], &micros[5], &alpha);
                                                                break;
                                                            }
                                                            }
                                                        }
                                                        else if (micros[5].Get_count_ticks() > 20)
                                                        {
                                                            quit = 2;
                                                            break;
                                                        }
                                                    }
                                            }
                                            if (quit != 0)
                                                continue;

                                            micros[5].push_count_ticks();
                                            if (micros[5].Get_count_ticks() >= micros[5].Get_ticks())
                                            {
                                                micros[5].change_ticks(key_open_NPS[5]);
                                                if (!key_open_NPS[5])
                                                {
                                                    micros[5].change_position();
                                                    check_position(&micros[5], &micros[1], &micros[2], &micros[3], &micros[4], &micros[0], &alpha);
                                                }
                                            }
                                            if (key_open_NPS[5])
                                                if (micros[5].Get_count_ticks() > 20)
                                                    if (check_differ_coalizion(alpha.GetdstRect(), micros[5].GetdstRect(), 3))
                                                    {
                                                        quit = 2;
                                                        continue;
                                                    }
                                           
                                            gameplay_timer.push_increment();
                                            
                                            if (gameplay_timer.Get_increment() % 25 == 0)
                                                gameplay_timer.Change_Timer(render, 1);
                                             
                                            if (gameplay_timer.Get_timer() <= 0)
                                                quit = 4;
                                             

                                            frameTime = SDL_GetTicks() - framestart;
                                            if (frameDelay > frameTime)
                                            {
                                                SDL_Delay(frameDelay - frameTime);
                                            }


                                        }

                                        SDL_ShowCursor(SDL_ENABLE);
                                        alpha.copy_Rect(1, &coin_game_over);
                                        alpha.copy_Rect(2, &coin_game_over_message);
                                        current_menu.game_over_state(render, quit);
                                        quit_game_over = false;
                                        while (!quit_game_over)
                                        {
                                            while (SDL_PollEvent(&glaive) != 0)
                                            {
                                                switch (glaive.type)
                                                {
                                                case(SDL_QUIT):
                                                {
                                                    exit(window, render);
                                                    return 0;
                                                }
                                                case SDL_MOUSEBUTTONDOWN:
                                                {
                                                    glaive_mouse = glaive.button;
                                                    if (glaive_mouse.button == SDL_BUTTON_LEFT)
                                                    {
                                                        if (current_menu.key_state_buttons[1])
                                                        {
                                                            quit_game_over = true;
                                                            interim = true;
                                                            current_menu.key_state_buttons[1] = false;
                                                        }
                                                        if (current_menu.key_state_buttons[0])
                                                        {
                                                            quit_game_over = true;
                                                            SDL_ShowCursor(SDL_DISABLE);
                                                        }

                                                    }
                                                    break;
                                                }
                                                }
                                            }

                                            if (Mix_PlayingMusic() == 0)
                                                Mix_PlayMusic(genMusic, -1);

                                            SDL_GetMouseState(&mouse_x, &mouse_y);

                                            for (int i = 1; i <= 2; i++)
                                            {
                                                current_menu.key_state_buttons[i - 1] = current_menu.mouse_detection(i, mouse_x, mouse_y);
                                                if (current_menu.key_state_buttons[i - 1])
                                                    current_menu.change_text_color(render, 2, i);
                                                else
                                                    current_menu.change_text_color(render, 1, i);
                                            }


                                            if (SDL_RenderClear(render) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -4;
                                            }

                                            if (SDL_RenderCopy(render, alpha.Get_Coin_Text(), NULL, &coin_game_over) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }

                                            if (SDL_RenderCopy(render, alpha.Get_Coin_Count_Text(), NULL, &coin_game_over_message) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -134;
                                            }

                                            if (SDL_RenderCopy(render, current_menu.Get_game_over_table_texture(), NULL, current_menu.Get_game_over_table_rect()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }

                                            if (SDL_RenderCopy(render, current_menu.Get_game_over_message_texture(), NULL, current_menu.Get_game_over_message_rect()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }


                                            if (SDL_RenderCopy(render, current_menu.Get_start_button_texture(), NULL, current_menu.Get_button_rect_start()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }



                                            if (SDL_RenderCopy(render, current_menu.Get_exit_button_texture(), NULL, current_menu.Get_button_rect_exit()) < 0)
                                            {
                                                messageboxdata.message = SDL_GetError();
                                                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                                {
                                                    SDL_Log("error displaying message box");
                                                    SDL_Log(SDL_GetError());
                                                    std::cout << SDL_GetError() << std::endl;
                                                }
                                                if (button_id < 0)
                                                {
                                                    SDL_Log("no selection of button \"OK\"");
                                                }
                                                return -135;
                                            }


                                            SDL_RenderPresent(render);

                                            frameTime = SDL_GetTicks() - framestart;
                                            if (frameDelay > frameTime)
                                            {
                                                SDL_Delay(frameDelay - frameTime);
                                            }
                                        }

                                        buff_score.score = alpha.Get_coin_res();
                                        int check_name_state{};
                                        check_name_state = Score_LST.check_name(buff_score, render);
                                        switch (check_name_state)
                                        {
                                        case(-1):
                                            break;
                                        case(-2):
                                        {
                                            Score_LST.push_back(buff_score, render);
                                            check_name_state = Score_LST.Get_size() - 1;
                                            break;
                                        }
                                        default:
                                            break;
                                        }

                                        if (check_name_state > 0)
                                            Score_LST.sort(check_name_state, render);

                                        buff_score.nick = "";
                                        buff_score.score = 0;
                                        if (buff_score.nick_text != nullptr)
                                        {
                                            SDL_DestroyTexture(buff_score.nick_text);
                                            buff_score.nick_text = nullptr;
                                        }
                                        if (buff_score.score_text != nullptr)
                                        {
                                            SDL_DestroyTexture(buff_score.score_text);
                                            buff_score.nick_text = nullptr;
                                        }

                                        QTE.~button_QTE();
                                        new(&QTE) button_QTE(render);

                                        alpha.~gypsy();
                                        new(&alpha) gypsy(render);

                                        gameplay_timer.~Timer();
                                        new(&gameplay_timer) Timer(render);

                                        for (int i = 0; i < 6; i++)
                                        {
                                            micros[i].~NPS_default();
                                            key_open_NPS[i] = false;
                                        }

                                        new(&micros[0]) NPS_default{ render, 1 };
                                        new(&micros[1]) NPS_default{ render,2 };
                                        new(&micros[2]) NPS_default{ render, 3 };
                                        new(&micros[3]) NPS_default{ render, 4 };
                                        new(&micros[4]) NPS_default{ render , 3 };
                                        new(&micros[5]) NPS_default{ render, 5 };
                                        
                                        check_position(&micros[0], &micros[1], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                        check_position(&micros[1], &micros[0], &micros[2], &micros[3], &micros[4], &micros[5], &alpha);
                                        check_position(&micros[2], &micros[1], &micros[0], &micros[3], &micros[4], &micros[5], &alpha);
                                        check_position(&micros[3], &micros[1], &micros[2], &micros[0], &micros[4], &micros[5], &alpha);
                                        check_position(&micros[4], &micros[1], &micros[2], &micros[3], &micros[0], &micros[5], &alpha);
                                        check_position(&micros[5], &micros[1], &micros[2], &micros[3], &micros[4], &micros[0], &alpha);
                                        check = SDL_SCANCODE_S;
                                        current_menu.change_quit_pos(false);
                                    }
                                break;
                            }
                            if (current_menu.key_state_buttons[1])  
                                quit_game = true;
                            if (current_menu.key_state_buttons[3])
                            {
                                int state_score_LST = Score_LST.show_list(render, map);
                                if (state_score_LST == 1)
                                    quit_game = true;
                                if (state_score_LST < 0)
                                {
                                    messageboxdata.message = SDL_GetError();
                                    if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                                    {
                                        SDL_Log("error displaying message box");
                                        SDL_Log(SDL_GetError());
                                        std::cout << SDL_GetError() << std::endl;
                                    }
                                    if (button_id < 0)
                                    {
                                        SDL_Log("no selection of button \"OK\"");
                                    }
                                    return state_score_LST;
                                }
                            }
                        }
                        break;
                    }
                }
            }

            if (quit_game)
                continue;

            if (Mix_PlayingMusic() == 0)
                Mix_PlayMusic(genMusic, -1);

            SDL_GetMouseState(&mouse_x, &mouse_y);
            for (int i = 1; i <= 4; i++)
            {
                if (i == 3)
                    continue;
                current_menu.key_state_buttons[i - 1] = current_menu.mouse_detection(i, mouse_x, mouse_y);
                if (current_menu.key_state_buttons[i - 1])
                    current_menu.change_text_color(render, 2, i);
                else
                    current_menu.change_text_color(render, 1, i);
            }


            if (SDL_RenderClear(render) < 0)
            {
                messageboxdata.message = SDL_GetError();
                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
                    SDL_Log("error displaying message box");
                    SDL_Log(SDL_GetError());
                    std::cout << SDL_GetError() << std::endl;
                }
                if (button_id < 0)
                {
                    SDL_Log("no selection of button \"OK\"");
                }
                return -4;
            }


            if (SDL_RenderCopy(render, map, NULL, NULL) < 0)
            {
                messageboxdata.message = SDL_GetError();
                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                {
                    SDL_Log("error displaying message box");
                    SDL_Log(SDL_GetError());
                    std::cout << SDL_GetError() << std::endl;
                }
                if (button_id < 0)
                {
                    SDL_Log("no selection of button \"OK\"");
                }
                return -135;
            }

            check_render_menu = current_menu.textures_render_main(render);
            if (check_render_menu != 0)
            {
                messageboxdata.message = SDL_GetError();
                if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0)
                {
                    SDL_Log("error displaying message box");
                    SDL_Log(SDL_GetError());
                    std::cout << SDL_GetError() << std::endl;
                }
                if (button_id < 0)
                {
                    SDL_Log("no selection of button \"OK\"");
                }
                return check;
            }

            SDL_RenderPresent(render);

            frameTime = SDL_GetTicks() - framestart;
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }


        }
        std::ofstream of_score(".\\base\\score.db", std::ofstream::in | std::ofstream::app | std::ofstream::binary || std::ofstream::trunc);
        output_data(Score_LST, of_score);
        of_score.close();
        Score_LST.clear();
    }
        
   
    exit(window, render);
    
    return 0;
}




