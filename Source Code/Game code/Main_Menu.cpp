#include "Objects.h"

Main_Menu::Main_Menu(SDL_Renderer* rend)
{

	font_menu = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 120);
	font_game_over = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 35);
	if (font_menu == nullptr)
		throw - 13;
	if (font_game_over == nullptr)
		throw - 13;
	color_text = { 100, 30, 0, 0 };
	name_texture = TextureManager::TextureRender_Text(rend, "GYPSY", font_menu, color_text);
	SDL_QueryTexture(name_texture, NULL, NULL, &name_rect.w, &name_rect.h);
	Set_Centre_Rect(&name_rect, 1280);
	name_rect.y = 171;
	pause_text = TextureManager::TextureRender_Text(rend, "Pause", font_menu, color_text);
	SDL_QueryTexture(pause_text, NULL, NULL, &pause_rect.w, &pause_rect.h);
	Set_Centre_Rect(&pause_rect, 1280);
	pause_rect.y = 221;
	
	game_over_table_texture = TextureManager::TextureRender_Text(rend, "GAME OVER", font_menu, color_text);
	SDL_QueryTexture(game_over_table_texture, NULL, NULL, &game_over_table_rect.w, &game_over_table_rect.h);
	Set_Centre_Rect(&game_over_table_rect, 1280);
	game_over_table_rect.y = 221;

	TTF_CloseFont(font_menu);
	font_menu = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 72);
	if (font_menu == nullptr)
		throw - 14;
	Table_choose_name_text = TextureManager::TextureRender_Text(rend, "Enter your nickname:", font_menu, color_text);
	SDL_QueryTexture(Table_choose_name_text, NULL, NULL, &Table_choose_name_rect.w, &Table_choose_name_rect.h);
	Set_Centre_Rect(&Table_choose_name_rect, 1280);
	Table_choose_name_rect.y = 221;

	

	TTF_CloseFont(font_menu);
	font_menu = TTF_OpenFont(".\\Font\\BRADHITC.TTF",62);
	if (font_menu == nullptr)
		throw - 14;

	err_mess_text = nullptr;

	color_text = { 255, 255, 255, 0 };

	score_button_texture = TextureManager::TextureRender_Text(rend, "Rating", font_menu, color_text);
	start_button_texture = TextureManager::TextureRender_Text(rend, "New game", font_menu, color_text);
	exit_button_texture = TextureManager::TextureRender_Text(rend, "Quit", font_menu, color_text);
	continue_button_texture = TextureManager::TextureRender_Text(rend, "Continue", font_menu, color_text);
	
	SDL_QueryTexture(continue_button_texture, NULL, NULL, &button_rect_continue.w, &button_rect_continue.h);
	SDL_QueryTexture(exit_button_texture, NULL, NULL, &button_rect_exit.w, &button_rect_exit.h);
	SDL_QueryTexture(start_button_texture, NULL, NULL, &button_rect_start.w, &button_rect_start.h);
	SDL_QueryTexture(score_button_texture, NULL, NULL, &score_button_rect.w, &score_button_rect.h);

	Set_Centre_Rect(&button_rect_continue, 1280);
	button_rect_continue.y = 371;

	Set_Centre_Rect(&button_rect_start, 1280);
	button_rect_start.y = 371;

	Set_Centre_Rect(&score_button_rect, 1280);
	score_button_rect.y = 451;

	Set_Centre_Rect(&button_rect_exit, 1280);
	button_rect_exit.y = 531;

	game_over_message_texture = TextureManager::TextureRender_Text(rend, "asd", font_game_over, game_over_color);
	game_over_message_rect.y = 341;
	

}

void Main_Menu::game_over_state(SDL_Renderer* rend ,int quit_state)
{
	SDL_DestroyTexture(game_over_message_texture);
	switch (quit_state)
	{
		case(1):
		{
			game_over_message_texture = TextureManager::TextureRender_Text(rend, "So boooring... I guess, that should pass away", font_game_over, game_over_color);
			SDL_QueryTexture(game_over_message_texture, NULL, NULL, &game_over_message_rect.w, &game_over_message_rect.h);
			break;
		}
		case(2):
		{
			game_over_message_texture = TextureManager::TextureRender_Text(rend, "Hey! What are you doing there little bastard?!?!", font_game_over, game_over_color);
			SDL_QueryTexture(game_over_message_texture, NULL, NULL, &game_over_message_rect.w, &game_over_message_rect.h);
			break;
		}
		case(3):
		{
			game_over_message_texture = TextureManager::TextureRender_Text(rend, "Thief there! Guards! Help!", font_game_over, game_over_color);
			SDL_QueryTexture(game_over_message_texture, NULL, NULL, &game_over_message_rect.w, &game_over_message_rect.h);
			break;
		}
		case(4):
		{
			game_over_message_texture = TextureManager::TextureRender_Text(rend, "OOps!! What a pity! Your time is up!", font_game_over, game_over_color);
			SDL_QueryTexture(game_over_message_texture, NULL, NULL, &game_over_message_rect.w, &game_over_message_rect.h);
			break;
		}
	}
	Set_Centre_Rect(&game_over_message_rect, 1280);
}

void Main_Menu::Set_Centre_Rect(SDL_Rect* current, int cur_res_x)
{
	current->x = (cur_res_x / 2) - (current->w / 2);
}

void Main_Menu::change_text_color(SDL_Renderer* rend, int color, int what)
{
	switch (color)
	{
		case(1):
		{
			color_text = { 255, 255, 255, 0 };
			break;
		}
		case(2):
		{
			color_text = { 150, 40, 0, 0 };
			break;
		}
	}

	switch (what)
	{
		case(1):
		{
			SDL_DestroyTexture(start_button_texture);
			start_button_texture = TextureManager::TextureRender_Text(rend, "New game", font_menu, color_text);
			break;
		}
		case(2):
		{
			SDL_DestroyTexture(exit_button_texture);
			exit_button_texture = TextureManager::TextureRender_Text(rend, "Quit", font_menu, color_text);
			break;
		}
		case(3):
		{
			SDL_DestroyTexture(continue_button_texture);
			continue_button_texture = TextureManager::TextureRender_Text(rend, "Continue", font_menu, color_text);
			break;
		}
		case(4):
		{
			SDL_DestroyTexture(score_button_texture);
			score_button_texture = TextureManager::TextureRender_Text(rend, "Rating", font_menu, color_text);
			break;
		}
	}
}

bool Main_Menu::mouse_detection(int what, int mouse_coord_x, int mouse_coord_y)
{
	switch (what)
	{
		case(1):
		{
			if ((button_rect_start.x <= mouse_coord_x) && (button_rect_start.x + button_rect_start.w >= mouse_coord_x) && (button_rect_start.y <= mouse_coord_y) && (button_rect_start.y + button_rect_start.h >= mouse_coord_y))
				return true;
			break;
		}
		case(2):
		{
			if ((button_rect_exit.x <= mouse_coord_x) && (button_rect_exit.x + button_rect_exit.w >= mouse_coord_x) && (button_rect_exit.y <= mouse_coord_y) && (button_rect_exit.y + button_rect_exit.h >= mouse_coord_y))
				return true;
			break;
		}
		case(3):
		{
			if ((button_rect_continue.x <= mouse_coord_x) && (button_rect_continue.x + button_rect_continue.w >= mouse_coord_x) && (button_rect_continue.y <= mouse_coord_y) && (button_rect_continue.y + button_rect_continue.h >= mouse_coord_y))
				return true;
			break;
		}
		case(4):
		{
			if ((score_button_rect.x <= mouse_coord_x) && (score_button_rect.x + score_button_rect.w >= mouse_coord_x) && (score_button_rect.y <= mouse_coord_y) && (score_button_rect.y + score_button_rect.h >= mouse_coord_y))
				return true;
			break;
		}
	}
	return false;
}

int Main_Menu::textures_render_main(SDL_Renderer* rend)
{

	if (SDL_RenderCopy(rend, name_texture, NULL, &name_rect) < 0)
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



	if (SDL_RenderCopy(rend, start_button_texture, NULL, &button_rect_start) < 0)
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
		return -136;
	}

	if (SDL_RenderCopy(rend, score_button_texture, NULL, &score_button_rect) < 0)
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
		return -137;
	}


	if (SDL_RenderCopy(rend, exit_button_texture, NULL, &button_rect_exit) < 0)
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
		return -138;
	}

	return 0;
}

void Main_Menu:: err_mess(SDL_Renderer* rend, int state)
{
	color_text = { 100, 30, 0, 0 };
	TTF_CloseFont(font_menu);
	font_menu = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 52);
	if (font_menu == nullptr)
		throw - 14;
	if (err_mess_text != nullptr)
		SDL_DestroyTexture(err_mess_text);

	err_mess_text = TextureManager::TextureRender_Text(rend, "The null string and \"space\" are not avalible", font_menu, color_text);
	SDL_QueryTexture(err_mess_text, NULL, NULL, &err_mess_rect.w, &err_mess_rect.h);
	Set_Centre_Rect(&err_mess_rect, 1280);
	err_mess_rect.y = 640;

	
	if (state == 1)
		err_mess_text = TextureManager::TextureRender_Text(rend, "The null string and \"space\" are not avalible", font_menu, color_text);
	else
		err_mess_text = TextureManager::TextureRender_Text(rend, "You can use either UK or USA keyboards for inputing ", font_menu, color_text);
		
	SDL_QueryTexture(err_mess_text, NULL, NULL, &err_mess_rect.w, &err_mess_rect.h);
	Set_Centre_Rect(&err_mess_rect, 1280);
	err_mess_rect.y = 640;

	color_text = { 255, 255, 255, 0 };
	TTF_CloseFont(font_menu);
	font_menu = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 62);
	if (font_menu == nullptr)
		throw - 14;
}

int Main_Menu:: enter_nickname(_score& buff, SDL_Renderer*& rend, SDL_Texture*& map)
{
	bool flag = false;
	int wchars_num{};
	int chars_num{};
	bool err_flag = false;
	std::string sym_str = u8"";
	int ID_KeyBoard;
	SDL_Event curr{};
	

	SDL_StartTextInput();
	while (!flag)
	{
		while (SDL_PollEvent(&curr) != 0)
		{
			switch (curr.type)
			{
			case(SDL_QUIT):
				return 1;
			case SDL_KEYDOWN:
			{
				switch (curr.key.keysym.scancode)
				{
				case (SDL_SCANCODE_ESCAPE):
				{
					SDL_DestroyTexture(buff.nick_text);
					buff.nick = "";
					return 2;
				}
				case (SDL_SCANCODE_BACKSPACE):
				{
					if (buff.nick != "")
					{
						buff.nick.erase(buff.nick.length() - 1, 1);
						if (buff.nick_text != nullptr)
							SDL_DestroyTexture(buff.nick_text);
						buff.nick_text = TextureManager::TextureRender_Text(rend, buff.nick, font_menu, color_text);
						SDL_QueryTexture(buff.nick_text, NULL, NULL, &buff.nick_rect.w, &buff.nick_rect.h);
						Set_Centre_Rect(&buff.nick_rect, 1280);
					}
					break;
				}
				case (SDL_SCANCODE_RETURN):
				{
					if ((buff.nick != "") && (buff.nick.find(" ") == buff.nick.npos))
						flag = true;
					else
					{
						err_flag = true;
						err_mess(rend, 1);
						buff.nick = "";
					}
					break;
				}
				}
				break;
			}
			case (SDL_TEXTINPUT):
			{
				if (buff.nick.size() >= 10)
					break;

				ID_KeyBoard = (int)GetKeyboardLayout(GetCurrentThreadId());
				
				if ((ID_KeyBoard != 67699721) && (ID_KeyBoard != 134809609))
				{
					err_mess(rend, 2);
					err_flag = true;
					break;
				}
				else
					err_flag = false;

				sym_str += curr.text.text;
				buff.nick += sym_str;			

				if (buff.nick_text != nullptr)
					SDL_DestroyTexture(buff.nick_text);
				buff.nick_text = TextureManager::TextureRender_Text(rend, buff.nick, font_menu, color_text);
				SDL_QueryTexture(buff.nick_text, NULL, NULL, &buff.nick_rect.w, &buff.nick_rect.h);
				Set_Centre_Rect(&buff.nick_rect, 1280);
				buff.nick_rect.y = 420;

				sym_str = u8"";
				break;
			}
			}
		}
		SDL_RenderClear(rend);

		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(genMusic, -1);

		if (SDL_RenderCopy(rend, map, NULL, NULL) < 0)
			return -300;

		if (SDL_RenderCopy(rend, Table_choose_name_text, NULL, &Table_choose_name_rect) < 0)
			return -301;

		if (buff.nick != "")
			if (SDL_RenderCopy(rend, buff.nick_text, NULL, &buff.nick_rect) < 0)
				return -302;
		
		if (err_flag)
			if (SDL_RenderCopy(rend, err_mess_text, NULL, &err_mess_rect) < 0)
				return -303;

		SDL_RenderPresent(rend);
	}
	return 0;
}



Main_Menu::~Main_Menu()
{
	if (name_texture != nullptr)
	{
		SDL_DestroyTexture(name_texture);
		name_texture = nullptr;
	}
	if (start_button_texture != nullptr)
	{
		SDL_DestroyTexture(start_button_texture);
		start_button_texture = nullptr;
	}

	SDL_DestroyTexture(exit_button_texture);
	SDL_DestroyTexture(game_over_message_texture);
	SDL_DestroyTexture(pause_text);
	SDL_DestroyTexture(game_over_table_texture);
	SDL_DestroyTexture(continue_button_texture);
	TTF_CloseFont(font_game_over);
	TTF_CloseFont(font_menu);
}

void Main_Menu::change_quit_pos(bool flag)
{
	if (flag)
		button_rect_exit.y = 451;
	else
		button_rect_exit.y = 531;
}