#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>
#include <sstream>
#include <Windows.h>
#include <fstream>

extern int button_id;
extern Mix_Music* genMusic;

struct error_mess
{
    const SDL_MessageBoxButtonData buttons[1]{
      { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "OK" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 0,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 0, 0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 0,   0, 0 }
        }
    };
};

extern error_mess take;

extern SDL_MessageBoxData messageboxdata;


class TextureManager
{
public:
    static SDL_Texture* TextureService(const char* texture, SDL_Renderer* rend);
    static SDL_Texture* TextureRender_score_coin(TTF_Font* font, SDL_Renderer* rend, int number, SDL_Color color_coin);
    static SDL_Texture* TextureRender_Text(SDL_Renderer* rend, std::string transpozition, TTF_Font* font, SDL_Color color);
    static SDL_Texture* TextureRender_Text(SDL_Renderer* rend, std::wstring transpozition, TTF_Font* font, SDL_Color color);
};

bool _Init();

int Init_video(SDL_Window*& window, SDL_Surface*& surface, SDL_Renderer*& render);

void exit(SDL_Window*& window, SDL_Renderer*& rend);
