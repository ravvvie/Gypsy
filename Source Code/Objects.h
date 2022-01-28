#include "Systems.h"
#pragma warning (disable:6011)



class Human
{
public:
    virtual bool change_sprite() { return true; }
protected:
    SDL_Rect srcrct{};
    SDL_Rect vec_dstrct{};
};

class NPS_default : protected Human
{
public :
    NPS_default(SDL_Renderer* rend, int person);
    SDL_Rect* GetdstRect() { return &vec_dstrct; }
    bool change_sprite(SDL_Renderer* rend);
    void change_position() { vec_dstrct.x = rand() % 1008 - 72; vec_dstrct.y = rand() % 400 + 100; }
    void change_ticks(bool& key);
    void push_count_ticks() { count_ticks++; }
    int Get_ticks() { return ticks; }
    int Get_count_ticks() {  return count_ticks; }
    SDL_Texture* get_Texture() { return body; }
    ~NPS_default();

private:
   int count{};
   SDL_Texture* body = nullptr;
   int ticks{};
   int count_ticks{};
   int person{};
};


class gypsy : protected Human
{
public:
    bool key[SDL_NUM_SCANCODES]{};
    void move(bool coordin, bool direct);
    gypsy(SDL_Renderer* rend);
    bool change_sprite(int mode, int state, SDL_Renderer* rend);
    bool change_static(int orientation, int state, SDL_Renderer* rend);
    void check_block();
    int update(SDL_Renderer* rend, int count, int check);
    SDL_Rect* GetdstRect() { return &vec_dstrct; }
    ~gypsy();
    SDL_Texture* get_Texture() { return player_texture_static; }
    SDL_Texture* Get_Coin_Text() { return coin.coin_texture; }
    SDL_Texture* Get_Coin_Count_Text() { return coin.count_coin_texture; }
    SDL_Rect* Get_coin_rect() { return &coin.coin_rect; }
    SDL_Rect* Get_count_coin_rect() { return &coin.count_coin_rect; }
    void copy_Rect(int what, SDL_Rect* current);
    int Get_coin_res() { return coin.coin_count; }

    void push_coin_count(SDL_Renderer* rend)
    { 
        coin.coin_count++;
        SDL_DestroyTexture(coin.count_coin_texture);
        coin.count_coin_texture = TextureManager::TextureRender_score_coin(coin.coin_count_font, rend, coin.coin_count, coin.coin_count_font_color);
        SDL_QueryTexture(coin.count_coin_texture, NULL, NULL, &coin.count_coin_rect.w, &coin.count_coin_rect.h);
    }


private:
    SDL_Texture* player_texture_static = nullptr;
    struct player_body
    {
        SDL_Texture* player_texture_back = nullptr;
        SDL_Texture* player_texture_forward = nullptr;
        SDL_Texture* player_texture_right = nullptr;
        SDL_Texture* player_texture_left = nullptr;
    };
    player_body body;
    int count_y_w{};
    int count_y_s{};
    int count_x_a{};
    int count_x_d{};
    int count_static{};
    struct money
    {
        SDL_Texture* coin_texture = nullptr;
        SDL_Texture* count_coin_texture = nullptr;
        int coin_count{};
        SDL_Rect coin_rect{};
        SDL_Rect count_coin_rect{};
        TTF_Font* coin_count_font = nullptr;
        SDL_Color coin_count_font_color{};
        int coin_count_font_size{};
    };
    money coin{};
};

class button_QTE
{
public:

    button_QTE(SDL_Renderer* rend);
    ~button_QTE();
    void change_button(SDL_Renderer* rend);
    void push_count_ticks() { count_ticks++; }
    int Get_ticks() { return ticks; }
    int Get_count_ticks() { return count_ticks; }
    int Get_button_ID() { return button_ID; }
    SDL_Texture* get_Texture() { return button_texture; }
    SDL_Rect* GetdstRect() { return &button_rect; }

private:

    SDL_Rect button_rect{};
    SDL_Texture* button_texture = nullptr;
    int button_ID{};
    int rand_button{};
    int count_ticks{};
    int ticks{};

};

int check_differ_coordinate(SDL_Rect* hero, SDL_Rect* NPS);
bool check_differ_coalizion(SDL_Rect* hero, SDL_Rect* NPS, int mode);
void check_position(NPS_default* checking, NPS_default* guy1, NPS_default* guy2, NPS_default* guy3, NPS_default* guy4, NPS_default* guy5, gypsy* hero);

class Timer
{
public:
    Timer(SDL_Renderer* rend);
    void push_increment() { increment++; }
    int Get_increment() { return increment; }
    void Change_Timer(SDL_Renderer* rend, int mode);
    int Get_timer() { return timer; }
    SDL_Texture* Get_timer_Texture() { return timer_texture; }
    SDL_Rect* Get_timer_Rect() { return &timer_rect; }
    ~Timer();

private:
    int increment{};
    int timer{};
    TTF_Font* timer_font = nullptr;
    std::string timer_position;
    std::stringstream out_timer;
    SDL_Rect timer_rect{};
    SDL_Texture* timer_texture = nullptr;
    int Timer_font_Size{};
    char swap[10] = "";
    SDL_Color Timer_color{};
};

struct _score
{
    SDL_Rect score_rect{};
    SDL_Texture* score_text = nullptr;
    int score{};

    SDL_Rect nick_rect{};
    SDL_Texture* nick_text = nullptr;
    std::string nick{};
};


class Main_Menu
{
public:
    bool key_state_buttons[4]{ false, false, false, false };
    Main_Menu(SDL_Renderer* rend);
    void Set_Centre_Rect(SDL_Rect* current, int cur_res_x);
    void change_text_color(SDL_Renderer* rend, int color, int what);
    bool mouse_detection(int what, int mouse_coord_x, int mouse_coord_y);
    void game_over_state(SDL_Renderer* rend, int quit_state);
    int textures_render_main(SDL_Renderer* rend);
    int enter_nickname(_score& buff, SDL_Renderer*& rend, SDL_Texture*& map);
    void change_quit_pos(bool flag);
    void err_mess(SDL_Renderer* rend, int state);
   
    SDL_Texture* Get_start_button_texture() { return start_button_texture; }
    SDL_Texture* Get_exit_button_texture() { return exit_button_texture; }
    SDL_Texture* Get_continue_button_texture() { return continue_button_texture; }
    SDL_Rect* Get_button_rect_start() { return &button_rect_start; }
    SDL_Rect* Get_button_rect_exit() { return &button_rect_exit; }
    SDL_Rect* Get_button_rect_continue() { return &button_rect_continue; }

    SDL_Rect* Get_pause_rect() { return &pause_rect; }
    SDL_Texture* Get_pause_texture() { return pause_text; }

    SDL_Rect* Get_game_over_message_rect() { return &game_over_message_rect; }
    SDL_Texture* Get_game_over_message_texture() { return game_over_message_texture; }

    SDL_Rect* Get_game_over_table_rect() { return &game_over_table_rect; }
    SDL_Texture* Get_game_over_table_texture() { return game_over_table_texture; }

    SDL_Rect* Get_name_rect() { return &name_rect; }
    SDL_Texture* Get_name_texture() { return name_texture; }
    ~Main_Menu();

private:
    SDL_Texture* start_button_texture = nullptr;
    SDL_Texture* exit_button_texture = nullptr;
    SDL_Texture* continue_button_texture = nullptr;
    SDL_Texture* score_button_texture = nullptr;
    SDL_Rect button_rect_start{};
    SDL_Rect button_rect_exit{};
    SDL_Rect button_rect_continue{};
    SDL_Rect score_button_rect{};

    SDL_Rect pause_rect{};
    SDL_Texture* pause_text = nullptr;

    SDL_Rect err_mess_rect{};
    SDL_Texture* err_mess_text = nullptr;

    TTF_Font* font_game_over = nullptr;
    SDL_Color game_over_color{ 255, 255, 255, 0 };
    SDL_Rect game_over_message_rect{};
    SDL_Texture* game_over_message_texture = nullptr;

    SDL_Rect game_over_table_rect{};
    SDL_Texture* game_over_table_texture = nullptr;

    SDL_Rect name_rect{};
    SDL_Texture* name_texture = nullptr;
    
    SDL_Texture* Table_choose_name_text = nullptr;
    SDL_Rect Table_choose_name_rect{};

    TTF_Font* font_menu = nullptr;
    SDL_Color color_text{};
};



class Rating_Lst
{
public:

    Rating_Lst(SDL_Renderer*& rend);
    ~Rating_Lst();


    bool push_back(_score& data, SDL_Renderer*& rend);
    int Get_size() { return size; }
    void clear();
    _score& operator() (const int _ind);
    bool pop_front();

    int check_name(_score& current_check, SDL_Renderer*& rend);
    void sort(int place, SDL_Renderer*& rend);
    
    int show_list(SDL_Renderer*& rend, SDL_Texture* map);
    

private:
   
    void scroll_list(bool direct);

    class Node_score
    {
    public:

        Node_score* pNext;
        Node_score* pPrev;
        _score data;
        int Place{};
        SDL_Texture* Place_text = nullptr;
        SDL_Rect Place_rect{};
        Node_score(_score data = _score(), Node_score* pNext = nullptr, Node_score* pPrev = nullptr)
            : data(data), pNext(pNext), pPrev(pPrev)
        {}
        
    };

    int size{};
    Node_score* head = nullptr;
    Node_score* curr = nullptr;

    SDL_Rect Table_score_rect{};
    SDL_Texture* Table_score_text = nullptr;

    SDL_Rect Table_nick_rect{};
    SDL_Texture* Table_nick_text = nullptr;

    
    TTF_Font* table_font = nullptr;
    SDL_Color table_color{};
};

void input_data(Rating_Lst& lst, std::ifstream& score_base, SDL_Renderer* rend);
void output_data(Rating_Lst& lst, std::ofstream& score_base);


