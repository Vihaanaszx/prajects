#include <iostream>
#include <random>
#include <cmath>

void give_hint(double hint)
{
	//std::cout << hint << std::endl;
	if (hint == -696969) std::cout << "bruh!!" << std::endl;
	else if (hint == 696969) std::cout;
	else if (hint > 0.9) std::cout << "very close" << std::endl;
	else if (hint > 0.8) std::cout << "close" << std::endl;
	else if (hint > 0.5) std::cout << "keep trying" << std::endl;
	else if (hint > 0.3) std::cout << "far" << std::endl;
	else if (hint > 0.1) std::cout << "very far" << std::endl;
	else if (hint < 0.1) std::cout << "bro what you doing" << std::endl;
}

int main()
{
	int l{}, u{};
	std::random_device rd;
	std::mt19937 gen(rd());

	std::cout << "what is the lower limit: ";
	std::cin >> l;
	std::cout << "what is the upper limit: ";
	std::cin >> u;

	std::uniform_int_distribution<int> dist(l, u);

	int num{ dist(gen) };

	std::cout << "the number has been chosen" << std::endl;

	int g{}, ng{ 0 };

	//std::cout << num << std::endl;

	do
	{
		std::cout << "guess the number: ";
		std::cin >> g;

		int close{g - num};
		double hint{};

		if (close < 0)
			hint = static_cast<double>(g - l) / (num - l);
		else if (close > 0)
		{
			//std::cout << static_cast<double>(g - num) / (u - num) << std::endl;
			hint = 1 - static_cast<double>(g - num) / (u - num);
		}

		if (g > u || g < l) hint = -696969;
		else if (g == num) hint = 696969;

		give_hint(hint);

		ng++;
	} while (g != num);

	std::cout << "you guessed the number!" << std::endl << "twas " << num << std::endl;
	std::cout << "you took " << ng << " tries.";

	return 0;
}
