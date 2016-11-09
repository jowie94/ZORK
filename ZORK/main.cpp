﻿#include <iostream>
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
		world.Tick(args);

		// Clean input
		args.clear();
		player_input = "";

		cout << "> ";
		read_sentence(player_input);
		tokenize(player_input, args);
		print_args(args);

		if (args.size() > 0 && str_equals(args[0], "quit"))
		{
			break;
		}
	}

	cout << endl << "Goodbye!!" << endl;
	getchar();
	return 0;
}
