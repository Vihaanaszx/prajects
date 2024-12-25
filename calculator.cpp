#include <iostream>
#include <string>
#include <cctype>
#include <vector>

static bool calculate(std::string& prompt)
{
    if (prompt.empty() ||
        prompt[0] == '+' || prompt[0] == '-' ||
        prompt[0] == '*' || prompt[0] == '/' ||
        prompt.back() == '+' || prompt.back() == '-' ||
        prompt.back() == '*' || prompt.back() == '/')
    {
        return false; // Invalid if the string starts or ends with an operator
    }

    std::vector<int> packet_n;
    std::string packet_o = "";

    int startpoint = 0;
    int i = 0;
    for (const char ch : prompt)
    {
        if (!std::isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/')
            return false; // Invalid character

        if ((ch == '+' || ch == '-' || ch == '*' || ch == '/') &&
            (i > 0 && (prompt[i - 1] == '+' || prompt[i - 1] == '-' || prompt[i - 1] == '*' || prompt[i - 1] == '/')))
        {
            return false; // Consecutive operators
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            packet_n.push_back(std::stoi(prompt.substr(startpoint, i - startpoint)));
            startpoint = i + 1;
            packet_o += ch;
        }

        i++;
    }

    // Push the last number
    if (prompt[startpoint] == '+' || prompt[startpoint] == '-' ||
        prompt[startpoint] == '*' || prompt[startpoint] == '/')
    {
        return false; // Ensure the last character is not an operator
    }

    packet_n.push_back(std::stoi(prompt.substr(startpoint)));

    //for (int n : packet_n)std::cout << n << std::endl;
    //for (char o : packet_o)std::cout << o << std::endl;

    i = 0;
    for (char op : packet_o)
    {
        std::vector<int> ans;

        //std::cout << i << std::endl;

        if (op == '+')ans.push_back(packet_n[0] + packet_n[1]);
        else if (op == '-')ans.push_back(packet_n[0] - packet_n[1]);
        else if (op == '*')ans.push_back(packet_n[0] * packet_n[1]);
        else if (op == '/')ans.push_back(packet_n[0] / packet_n[1]);

        for (int j = 2; j < packet_n.size(); j++)
        {
            ans.push_back(packet_n[j]);
        }

        //for (int n : ans)std::cout << n << std::endl;

        packet_n = ans;

        i++;


    }

    std::cout << packet_n[0] << std::endl;

    return true;
}


int main()
{
	bool continu{ true };
	do
	{
		std::string prompt;
		std::cout << "enter: ";
		std::getline(std::cin, prompt);

		std::cout << prompt << std::endl;

        calculate(prompt);

		std::cout << "continue?: ";
		char c;
		std::cin >> c;

		// Clear the newline character left in the input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        

		if (c == 'n')continu = false;
		
	} while (continu);

	return 0;
}
