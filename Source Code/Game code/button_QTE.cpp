#include "Objects.h"

button_QTE::button_QTE(SDL_Renderer* rend)
{
	rand_button = rand() % 4 + 1;
	button_rect.x = 640;
	button_rect.y = 360;
	button_rect.w = 75;
	button_rect.h = 75;
	switch (rand_button)
	{
	case(1):
	{
		button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_B.png", rend);
		button_ID = SDL_SCANCODE_B;
		break;
	}
	case(2):
	{
		button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_E.png", rend);
		button_ID = SDL_SCANCODE_E;
		break;
	}
	case(3):
	{
		button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_L.png", rend);
		button_ID = SDL_SCANCODE_L;
		break;
	}
	case(4):
	{
		button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_Y.png", rend);
		button_ID = SDL_SCANCODE_Y;
		break;
	}
	}
	ticks = 50;
}

void button_QTE::change_button(SDL_Renderer* rend)
{
	count_ticks = 0;
	rand_button = rand() % 4 + 1;
	SDL_DestroyTexture(button_texture);
	switch (rand_button)
	{
		case(1):
		{
			button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_B.png", rend);
			button_ID = SDL_SCANCODE_B;
			break;
		}
		case(2):
		{
			button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_E.png", rend);
			button_ID = SDL_SCANCODE_E;
			break;
		}
		case(3):
		{
			button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_L.png", rend);
			button_ID = SDL_SCANCODE_L;
			break;
		}
		case(4):
		{
			button_texture = TextureManager::TextureService(".\\images\\Buttons_QTE_sprite\\key_Y.png", rend);
			button_ID = SDL_SCANCODE_Y;
			break;
		}
	}
}

button_QTE:: ~button_QTE()
{
	if (button_texture != nullptr)
		SDL_DestroyTexture(button_texture);
}