#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std::chrono;

struct Players {

	int _mode = 0;

	std::string _name = "<Unknown>";
	int _score = 0;
	duration<double> _time_played;

	std::string _display_time;

	Players();
	Players(int);
	
	void readPlayersFile(std::vector<Players>&, std::string file);
	void sortPlayers(std::vector<Players>&);
	void writePlayersFile();
	void writePlayersFileLL();

	int calculateScore(duration<double>, int);
	std::string getPlayerName();
};