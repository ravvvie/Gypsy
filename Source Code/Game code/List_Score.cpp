#include "Objects.h"

Rating_Lst :: ~Rating_Lst()
{
	if (curr != nullptr)
	{
		curr = nullptr;
		head = nullptr;
	}
}

Rating_Lst :: Rating_Lst(SDL_Renderer*& rend)
	: head (nullptr), curr (nullptr), size (0),
	Table_nick_rect {300,  250}, 
	Table_score_rect {800, 250}
{
	table_font = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 72);
	table_color = { 100, 30, 0, 0 };
	Table_nick_text = TextureManager::TextureRender_Text(rend, "Nickname", table_font, table_color);
	Table_score_text = TextureManager::TextureRender_Text(rend, "Score", table_font, table_color);
	SDL_QueryTexture(Table_nick_text, NULL, NULL, &Table_nick_rect.w, &Table_nick_rect.h);
	SDL_QueryTexture(Table_score_text, NULL, NULL, &Table_score_rect.w, &Table_score_rect.h);
	table_color = { 255, 255, 255, 0 };

	TTF_CloseFont(table_font);
	table_font = nullptr;
	table_font = TTF_OpenFont(".\\Font\\BRADHITC.TTF", 62);
	if (table_font == nullptr)
		throw - 14;

}

int Rating_Lst::show_list(SDL_Renderer*& rend, SDL_Texture* map)
{
	bool looP_lst = false;
	SDL_Event curr{};
	while (!looP_lst)
	{
		while (SDL_PollEvent(&curr) != 0)
		{
			switch (curr.type)
			{
			case(SDL_QUIT):
				return 1;
			case(SDL_KEYDOWN):
			{
				if (curr.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					looP_lst = true;
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				if (size > 0)
				{
					if (curr.wheel.y > 0)
					{
						if (head->Place_rect.y < 100 + 250)
							scroll_list(true);
					}
					else
						if (head->pPrev->Place_rect.y > 100 * 4 + 250)
							scroll_list(false);
				}
			}
			}
		}

		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(genMusic, -1);

		SDL_RenderClear(rend);
		if (SDL_RenderCopy(rend, map, NULL, NULL) < 0)
			return -400;
		if (SDL_RenderCopy(rend, Table_nick_text, NULL, &Table_nick_rect) < 0)
			return -401;
		if (SDL_RenderCopy(rend, Table_score_text, NULL, &Table_score_rect) < 0)
			return -402;
		for (int i = 3; i <= 5; i++)
		{
			if (SDL_RenderDrawLine(rend, Table_nick_rect.x - i, Table_nick_rect.y - i, Table_score_rect.x + Table_score_rect.w + i, Table_score_rect.y - i) < 0)
				return -403;
			if (SDL_RenderDrawLine(rend, Table_nick_rect.x - i, Table_nick_rect.y + Table_nick_rect.h + i, Table_score_rect.x + Table_score_rect.w + i, Table_score_rect.y + Table_score_rect.h + i) < 0)
				return -404;
		}
		this->curr = head;
		if (size > 0)
		{
			for (int i = 0; i < size; i++)
			{
				if ((this->curr->Place_rect.y >= 100 + 250) && (this->curr->Place_rect.y <= 100 * 4 + 250))
				{
					if (SDL_RenderCopy(rend, this->curr->Place_text, NULL, &this->curr->Place_rect) < 0)
						return -405 - i;
					if (SDL_RenderCopy(rend, this->curr->data.nick_text, NULL, &this->curr->data.nick_rect) < 0)
						return -406 - i;
					if (SDL_RenderCopy(rend, this->curr->data.score_text, NULL, &this->curr->data.score_rect) < 0)
						return -407 - i;
				}
				this->curr = this->curr->pNext;
			}
		}
		SDL_RenderPresent(rend);

	}
	return 0;
}

bool Rating_Lst::push_back(_score& data, SDL_Renderer*& rend)
{
	switch (size)
	{
	case(0):
	{
		head = new Node_score(data);
		head->pNext = head;
		head->pPrev = head;
		curr = head;
		break;
	}
	case(1):
	{
		head->pPrev = new Node_score(data);
		head->pPrev->pNext = head;
		head->pPrev->pPrev = head;
		head->pNext = head->pPrev;
		curr = head->pPrev;
		break;
	}
	default:
	{
		curr = head->pPrev;
		head->pPrev = new Node_score(data);
		curr->pNext = head->pPrev;
		curr->pNext->pPrev = curr;
		curr->pNext->pNext = head;
		curr = curr->pNext;
		break;
	}
	}
	size++;
	curr->Place = size;
	if (size <= 3)
		table_color = { 80, 30, 0, 0 };

	curr->data.nick_text = TextureManager::TextureRender_Text(rend, curr->data.nick, table_font, table_color);
	curr->data.score_text = TextureManager::TextureRender_score_coin(table_font, rend, curr->data.score, table_color);
	curr->Place_text = TextureManager::TextureRender_score_coin(table_font, rend, curr->Place, table_color);

	SDL_QueryTexture(curr->data.nick_text, NULL, NULL, &curr->data.nick_rect.w, &curr->data.nick_rect.h);
	SDL_QueryTexture(curr->data.score_text, NULL, NULL, &curr->data.score_rect.w, &curr->data.score_rect.h);
	SDL_QueryTexture(curr->Place_text, NULL, NULL, &curr->Place_rect.w, &curr->Place_rect.h);
	
	curr->data.nick_rect.x = 420;
	curr->data.nick_rect.y = 100 * curr->Place + 250;

	curr->data.score_rect.x = 840;
	curr->data.score_rect.y = 100 * curr->Place + 250;

	curr->Place_rect.x = 300;
	curr->Place_rect.y = 100 * curr->Place + 250;

	table_color = { 255, 255, 255, 0 };
	return false;
}

int Rating_Lst::check_name(_score& current_check, SDL_Renderer*& rend)
{
	int ind{};
	curr = head;
	for (ind = 0; ind < size; ind++)
	{
		if (curr->data.nick == current_check.nick)
			break;
		curr = curr->pNext;
	}

	if (ind < size)
	{
		if (curr->data.score < current_check.score)
		{
			SDL_DestroyTexture(curr->data.score_text);
			if (curr->Place <= 3)
				table_color = { 80, 30, 0, 0 };
			curr->data.score = current_check.score;
			curr->data.score_text = TextureManager::TextureRender_score_coin(table_font, rend, curr->data.score, table_color);
			SDL_QueryTexture(curr->data.score_text, NULL, NULL, &curr->data.score_rect.w, &curr->data.score_rect.h);
			
			table_color = { 255, 255, 255, 0 };
		}
		else
			ind = -1;
	}
	else
		ind = -2;

	return ind;
	
}

void Rating_Lst::sort(int place, SDL_Renderer*& rend)
{
	_score buff{};
	curr = head;
	if (place == size - 1)
		curr = head->pPrev;
	else
		for (int i = 0; i < place; i++)
			curr = curr->pNext;
	
	while ((curr->data.score > curr->pPrev->data.score) && (curr != head))
	{
		buff = curr->pPrev->data;
		curr->pPrev->data = curr->data;
		curr->data = buff;

		curr->pPrev->data.score_rect.y = curr->pPrev->Place_rect.y;
		curr->pPrev->data.nick_rect.y = curr->pPrev->Place_rect.y;
		curr->data.score_rect.y = curr->Place_rect.y;
		curr->data.nick_rect.y = curr->Place_rect.y;

		if (curr->pPrev->Place == 3)
		{
			table_color = { 80, 30, 0, 0 };
			SDL_DestroyTexture(curr->pPrev->data.nick_text);
			SDL_DestroyTexture(curr->pPrev->data.score_text);
			curr->pPrev->data.score_text = TextureManager::TextureRender_score_coin(table_font, rend, curr->pPrev->data.score, table_color);
			curr->pPrev->data.nick_text = TextureManager::TextureRender_Text(rend, curr->pPrev->data.nick, table_font,  table_color);

			table_color = { 255, 255, 255, 0 };
			SDL_DestroyTexture(curr->data.nick_text);
			SDL_DestroyTexture(curr->data.score_text);
			curr->data.score_text = TextureManager::TextureRender_score_coin(table_font, rend, curr->data.score, table_color);
			curr->data.nick_text = TextureManager::TextureRender_Text(rend, curr->data.nick, table_font, table_color);
		}
		curr = curr->pPrev;
	}
}

void Rating_Lst:: scroll_list(bool direct)
{
	int dir{};
	if (!direct)
		dir = -1;
	else
		dir = 1;

	curr = head;
	for (int i = 0; i < size; i++)
	{
		curr->Place_rect.y += (dir * 100);
		curr->data.nick_rect.y += (dir * 100);
		curr->data.score_rect.y += (dir * 100);
		curr = curr->pNext;
	}
}

_score& Rating_Lst:: operator() (const int _ind)
{
	if (_ind < size)
	{
		if (_ind <= (size / 2))
		{
			curr = head;
			for (int i = 0; i < _ind; i++)
				curr = curr->pNext;
		}
		else
		{
			curr = head->pPrev;
			for (int i = size - 1; i > _ind; i--)
				curr = curr->pPrev;
		}
	}
	else
	{
		throw - 1;
	}
	return curr->data;
}

bool Rating_Lst::pop_front()
{
	switch (size)
	{
	case(0):
		return true;

	case(1):
	{
		delete head;
		break;
	}
	default:
	{
		Node_score* temp = head;
		head = head->pNext;
		head->pPrev = temp->pPrev;
		delete temp;
		break;
	}
	}

	size--;
	return true;
}

void Rating_Lst::clear()
{
	while (size > 0)
		pop_front();
}
