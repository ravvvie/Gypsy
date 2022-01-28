#include "Objects.h"


void input_data(Rating_Lst& lst, std::ifstream& score_base, SDL_Renderer* rend)
{
	_score buff_sc{};
	score_base >> buff_sc.nick;
	std::string buff_str;
	while (!score_base.eof())
	{
		score_base >> buff_str;
		buff_sc.score = std::stoi(buff_str, NULL, 10);
		lst.push_back(buff_sc, rend);
		score_base >> buff_sc.nick;
	}
}

void output_data(Rating_Lst& lst, std::ofstream& score_base)
{
	int size = lst.Get_size();
	_score buff{};
	for (int i = 0; i < size; i++)
	{
		buff = lst(i);
		score_base << buff.nick << "   " << buff.score << "\n";
	}
}