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
#include "GameLinkedList.h"
#include "Board.h"
#include "BoardLinkedList.h"

#define EASY 4
#define MEDIUM 6
#define HARD 8

struct Menu
{
	const string _options[6] = { "Standard Mode (4x4)","Standard Mode (6x6)","Difficult Mode (4x4)","Difficult Mode (6x6)","Leaderboard","Exit"};
	int _optionsSize, _curOption;
	int _xMenu, _yMenu;			
	int _left, _top;

	Menu();
	~Menu();

	void renderMainScreen();
	void renderGameTitle();
	void renderOptionsMenu();
	void renderOptionsText();
	void renderCurrentOption();

	int getCurrentOption();
	void setCurrentOption(int opt);
	void offCurrentOption();
	void changeOption(int direction);

	static void playEasy();
	static void playMedium();
	static void playEasyDifficult();
	static void playMediumDifficult();
	static void showLeaderboard();
	static void aboutPage();		//Haven't done
	static void exitGame();
};