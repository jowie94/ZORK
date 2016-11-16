#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "utils.h"
#include "world.h"

using namespace std;

void tokenize(const string &str, arglist &tokens)
{
	string buf;
	stringstream ss(str);

	while (ss >> buf)
	{
		tokens.push_back(buf);
	}
}

void read_sentence(string &sentence)
{
	getline(cin, sentence);
}

void print_args(const arglist &tokens)
{
	for (string token : tokens)
		cout << token << " ";
	cout << endl;
}

int main()
{
	string player_input;
	arglist args;

	World world;

	cout << "Welcome to ZORK!" << endl;
	cout << "----------------" << endl;

	// Create world

	args.push_back("look");

	while (true)
	{
		if (!world.Tick(args))
		{
			cout << "Sorry, I didn't understand you" << endl;
		}

		if (world.AllPuzzlesSolved())
		{
			cout << "You escaped!! Now you are alone, in the space, waiting for your saviours..." << endl;
			break;
		}

		if (!world.IsPlayerAlive())
		{
			cout << "You died!!" << endl << "Do you want to play again? (y/n): ";
			
			string answ = "";
			while (answ[0] != 'y' && answ[0] != 'n')
			{
				cin >> answ;
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();

			if (answ[0] == 'y')
			{
				world = World();
				args.clear();
				args.push_back("look");
				continue;
			}
			break;
		}

		// Clean input
		args.clear();
		player_input = "";

		cout << "> ";
		read_sentence(player_input);
		tokenize(player_input, args);
		//print_args(args);

		if (args.size() > 0 && str_equals(args[0], "quit"))
		{
			break;
		}
	}

	cout << endl << "Goodbye!!" << endl;
	getchar();
	return 0;
}
