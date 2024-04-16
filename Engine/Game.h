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
	std::mt19937 rng;
	MainWindow& wnd;
	Graphics gfx;
	//SpriteCodex sprite;
	Board brd;
	Snake snake;
	Goal goal;
	Font font = "Fixedsys16x28.bmp";
	Location delta_loc = {1,0};
	int SnakeMovePeriod = 20;
	int SnakeMoveCounter = 0;
	int SnakeSpeedUpPeriod = 180;
	int SnakeSpeedCounter = 0;
	bool GameIsOver = false;
	bool GameIsStarted = false;
	int finalway = 1;
	int way = 1; //1 = left 2 = right 3 = up 4 = down
	int lastFps = 0;
};