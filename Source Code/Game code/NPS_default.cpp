#include "Objects.h"

bool NPS_default::change_sprite(SDL_Renderer* rend)
{
	count++;
	bool chase = true;

	switch (person)
	{
		case(1):
		{
			break;
		}
		case(2):
		{
			switch (count)
			{
				case(8):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_3_-_idle_-2.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
				case(16):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_3_-_idle_-1.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
			}
			break;
		}
		case(3):
		{
			switch (count)
			{
					case (8):
					{
						SDL_DestroyTexture(body);
						body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_2_-_idle_-2.png", rend);
						if (body == nullptr)
							chase = false;
						break;
					}
					case(16):
					{
						SDL_DestroyTexture(body);
						body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_2_-_idle_-1.png", rend);
						if (body == nullptr)
							chase = false;
						break;
					}
			}
			break;
		}
		case(4):
		{
			switch (count)
			{
				case (8):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_1-idle-2.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
				case(16):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_1-idle-1.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
			}
			break;
		}
		case(5):
		{
			switch (count)
			{
				case (8):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprite_Knight\\knight-2.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
				case(16):
				{
					SDL_DestroyTexture(body);
					body = TextureManager::TextureService(".\\images\\Sprite_Knight\\knight-1.png", rend);
					if (body == nullptr)
						chase = false;
					break;
				}
			}
			break;
		}
	}
	count = count % 16;
	
	return chase;
}

NPS_default::NPS_default(SDL_Renderer* rend, int person)
{
	ticks = rand() % 200 + 100;
	vec_dstrct.w = 175;
	vec_dstrct.h = 175;
	this->person = person;
	switch (person)
	{
		case(1):
		{
			body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_4.png", rend);
			if (body == nullptr)
				throw - 5;
			break;
		}
		case(2):
		{
			body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_3_-_idle_-1.png", rend);
			if (body == nullptr)
				throw - 5;
			break;
		}
		case(3):
		{
			body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_2_-_idle_-1.png", rend);
			if (body == nullptr)
				throw - 5;
			break;
		}
		case(4):
		{
			body = TextureManager::TextureService(".\\images\\Sprites_NPS\\arab_-_1-idle-1.png", rend);
			if (body == nullptr)
				throw - 5;
			break;
		}
		case(5):
		{
			ticks = rand() % 401 + 300;
			vec_dstrct.w = 185;
			vec_dstrct.h = 185;
			body = TextureManager::TextureService(".\\images\\Sprite_Knight\\knight-1.png", rend);
			if (body == nullptr)
				throw - 5;
			break;
		}
	}
	vec_dstrct.x = rand() % 1008 - 72;
	vec_dstrct.y = rand() % 400 + 100;
}

NPS_default :: ~NPS_default()
{
	if (body != nullptr)
		SDL_DestroyTexture(body);
}

void NPS_default::change_ticks(bool& key)
{
	count_ticks = 0; 

	if (key)
	{
		key = false;
		if (person == 5)
			ticks = rand() % 401 + 300;
		else
			ticks = ticks = rand() % 300 + 100;
		
	}
	else
	{
		key = true;
		if (person == 5)
			ticks = rand() % 101 + 50;
		
		else
			ticks = rand() % 11 + 200;
	}
}