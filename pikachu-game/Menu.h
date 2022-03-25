#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include "Common.h"
#include "Game.h"

#define EASY 4
#define MEDIUM 6
#define HARD 8

struct Menu
{

	const string _options[5] = { "Easy","Medium","Hard","About","Exit"};
	int _optionsSize;
	int _curOption;
	int _xMenu, _yMenu;			//Tọa độ x y của menu board

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
	static void aboutPage();
	static void exitGame();
};