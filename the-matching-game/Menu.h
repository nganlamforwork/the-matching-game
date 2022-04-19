#pragma once
#include <iostream>
#include <string>
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
	const std::string _options[7] = {
		"Standard Mode  (4x4)","Standard Mode  (6x6)","Difficult Mode (4x4)","Difficult Mode (6x6)","Tutorial","Leaderboard","Exit" };
	int _optionsSize, _curOption;
	int _xMenu, _yMenu;
	int _left, _top;

	Menu();
	~Menu();
	
	void startApp();
	void renderLoadingScreen();
	void renderMainScreen();
	void renderGameTitle();
	void renderOptionsMenu();
	void renderOptionsText();
	void renderCurrentOption();

	void renderFlowers();

	int getCurrentOption();
	void setCurrentOption(int opt);
	void offCurrentOption();
	void changeOption(int direction);

	void playEasy();
	void playMedium();
	void playEasyDifficult();
	void playMediumDifficult();
	void showTutorial();		//Haven't done
	void showLeaderboard();
	void exitGame();
};