#include <iostream>
#include <array>
#include <string>

static char convert(unsigned int play)
{
	if (play == 0)return ' ';
	else if (play == 1)return 'O';
	else if (play == 2)return 'X';
	else return '~';
}

static std::array<int,2> check_winD(const std::array<std::array<unsigned int, 3>, 3>& game)
{
	for (int i = 0; i < 3; i++)
	{
		if ((game[i][0] == game[i][1] && game[i][1] == game[i][2]) && game[i][0] != 0)return { 1,i };
		else if ((game[0][i] == game[1][i] && game[1][i] == game[2][i]) && game[0][i] != 0)return { 2,i };
	}

	if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[1][1] != 0) return {3,0};
	else if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] != 0) return { 4,0 };

	return { 0,0 };
}

static bool check_tie(const std::array<std::array<unsigned int, 3>, 3>& game);

static std::pair<bool,bool> check_win(const std::array<std::array<unsigned int, 3>, 3>& game)
{
	if (check_tie(game))
	{
		return { true,true };
	}

	for (int i = 0; i < 3; i++)
	{
		if ((game[i][0] == game[i][1] && game[i][1] == game[i][2]) && game[i][0] != 0) return { true,false };
		else if ((game[0][i] == game[1][i] && game[1][i] == game[2][i]) && game[0][i] != 0) return { true,false };
	}

	if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[1][1] != 0) return { true,false };
	else if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[1][1] != 0) return { true,false };

	return { false,false };
}

static bool check_tie(const std::array<std::array<unsigned int, 3>, 3>& game)
{
	for (std::array<unsigned int, 3> row : game)
	{
		for (unsigned int cell : row)if (cell == 0)return false;
	}
	return true;
}

static void display(const std::array<std::array<unsigned int, 3>,3>& game)
{
	for (const auto& i : game)
	{
		for (const auto& j : i)
		{
			std::cout << " " << convert(j) << "";
			if(&j != &i.back())std::cout << " |";
		}
		std::cout << std::endl;
		if (&i != &game.back())
		{
			std::cout << "---|---|---" << std::endl;
		}
	}
}

static std::pair<int, int> getInput(int player)
{
	int row, col;
	std::cout << "Player " << player << "(" << (player == 1 ? "O): " : "X): ");
	std::cin >> row >> col;
	return { row,col };
}

static bool check_input(std::pair<int, int> play, std::array<std::array<unsigned int, 3>, 3> game)
{
	return (play.first < 3 && play.first >= 0 && play.second < 3 && play.second >= 0 && game[play.first][play.second] == 0);
}

int main()
{
	std::array<std::array<unsigned int, 3>, 3> game;
	game = { {
		{0,0,0},
		{0,0,0},
		{0,0,0}
	} };

	//display(game);
	//for (int i : check_winD(game))std::cout << i << " ";

	int player = 1;
	std::pair<bool, bool> game_state = check_win(game);
	do
	{
		display(game);

		std::pair<int, int> input = getInput(player);
		while (!check_input(input, game)) input = getInput(player);

		game[input.first][input.second] = player;

		if (player == 1)player = 2;
		else player = 1;

		//for (int i : check_winD(game))std::cout << i << " ";
		//std::cout << '\n';

		game_state = check_win(game);

	} while (!game_state.first);

	std::cout << "\n\n\n";

	std::cout << "--------------------------------\n";
	if (game_state.second)std::cout << "Twas a tie\n";
	else std::cout << "Player " << convert(player) << " won! \n";
	std::cout << "--------------------------------\n";

	display(game);

	return 0;
}