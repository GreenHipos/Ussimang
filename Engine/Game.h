#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <random>
#include "Font.h"
#include "Vec2.h"

class Game
{
public:
	double getdt();
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void reset();
	void printFPS(Graphics& gfx);
private:
	//HBITMAP map = (HBITMAP)::LoadImage(NULL, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, 0);
	std::mt19937 rng;
	MainWindow& wnd;
	Graphics gfx;
	//SpriteCodex sprite;
	Board brd;
	Snake snake;
	Goal goal;
	Font font = "Fixedsys16x28.bmp";
	Location delta_loc = {1,0};
	double SnakeMovePeriod = 20;
	int SnakeMoveCounter = 0;
	int SnakeSpeedUpPeriod = 180;
	int SnakeSpeedCounter = 0;
	bool GameIsOver = false;
	bool GameIsStarted = false;
	int points = 0;
	int aeg = 0;
	double aegtimer = 0;
	int finalway = 1;
	int way = 1; //1 = left 2 = right 3 = up 4 = down
	int lastFps = 0;
};