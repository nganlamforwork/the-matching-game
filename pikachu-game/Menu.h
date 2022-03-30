#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Players.h"
#include "Common.h"
#include "Game.h"
#include "Board.h"

#define EASY 4
#define MEDIUM 6
#define HARD 8

struct Menu
{

	const string _options[5] = { "Easy Mode (4x4)","Easy Mode (6x6)","Difficult Mode (4x4)","Leaderboard","Exit"};
	int _optionsSize;
	int _curOption;
	int _xMenu, _yMenu;					//Tọa độ x y của menu board
	int _left, _top;

	Menu();
	~Menu();
	int getCurrentOption();
	void setCurrentOption(int opt);

	void renderMainScreen();
	void renderGameTitle();
	void renderOptionsMenu();
	void renderOptionsText();
	void renderCurrentOption();
	void offCurrentOption();
	void changeOption(int direction);

	static void playEasy();
	static void playMedium();
	static void playHard();
	static void showLeaderboard();//để làm sau
	static void aboutPage();
	static void exitGame();
};