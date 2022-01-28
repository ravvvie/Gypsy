#include "Systems.h"



SDL_Texture* TextureManager::TextureService(const char* texture, SDL_Renderer* rend)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tempText = SDL_CreateTextureFromSurface(rend, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (tempText == nullptr)
        return nullptr;
	else
		return tempText;
}

SDL_Texture* TextureManager::TextureRender_score_coin(TTF_Font* font, SDL_Renderer* rend, int number, SDL_Color color_coin)
{
    char swap[10] = "";
    _itoa(number, swap, 10);
    SDL_Surface* surf = TTF_RenderText_Blended(font, swap, color_coin);
    if (surf == nullptr)
        return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    return texture;
}

SDL_Texture* TextureManager::TextureRender_Text(SDL_Renderer* rend, std::string transpozition, TTF_Font* font, SDL_Color color)
{
    SDL_Surface* surf = TTF_RenderText_Blended(font, transpozition.c_str(), color);
    if (surf == nullptr)
        return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    return texture;
}

SDL_Texture* TextureManager::TextureRender_Text(SDL_Renderer* rend, std::wstring transpozition, TTF_Font* font, SDL_Color color)
{
    SDL_Surface* surf = TTF_RenderUNICODE_Blended(font, reinterpret_cast<Uint16 const*> (transpozition.c_str()), color);
    if (surf == nullptr)
        return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    return texture;
}