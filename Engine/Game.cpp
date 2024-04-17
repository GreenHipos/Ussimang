#include "MainWindow.h"
#include "Game.h"
#include <chrono>
#include <iostream>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


double Game::getdt() {
	static auto lastTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();

	double delta = std::chrono::duration<double>(currentTime - lastTime).count();
	lastTime = currentTime;
	return delta;
}

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 5, 5 }),
	goal(rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (GameIsStarted) {
		aegtimer += getdt();
		if (aegtimer >= 1) {
			aegtimer = 0;
			aeg++;
		}
		if (!GameIsOver) {
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				if (finalway != 4) {
					way = 3;
					delta_loc = { 0,-1 };
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				if (finalway != 3) {
					way = 4;
					delta_loc = { 0,1 };
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				if (finalway != 1) {
					way = 2;
					delta_loc = { -1,0 };
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				if (finalway != 2) {
					way = 1;
					delta_loc = { 1,0 };
				}
			}
		}
		
		SnakeMoveCounter++;
		if (SnakeMoveCounter >= SnakeMovePeriod) {
			if (snake.getSegmentA() < 3) {
				snake.Grow();
			}
			finalway = way;
			SnakeMoveCounter = 0;
			const Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || snake.IsInTile(next)) {
				GameIsOver = true;
			}
			else {
				const bool eating = next == goal.GetLocation();
				if (eating) {
					points++;
					snake.Grow();
				}
				snake.MoveBy(delta_loc);
				if (eating) {
					goal.Respawn(rng, brd, snake);
				}
			}
		}

		if (SnakeMovePeriod > 7) {
			SnakeMovePeriod -= (1000 + points * 50) * getdt();
			if (SnakeMovePeriod < 7) {
				SnakeMovePeriod = 7;
			}
		}
	}
	else {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			GameIsStarted = true;
		}
	}

	if (GameIsOver == true) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			if (GameIsOver == true) {
				GameIsStarted = true;
				GameIsOver = false;
				SnakeMoveCounter = 0;
				snake.ResetSeg();
				finalway = 1;
				way = 1;
				reset();
				delta_loc = { 1,0 };
			}
		}
	}
}

void Game::reset()
{
	points = 0;
	SnakeMoveCounter = 0;
	SnakeMovePeriod = 20;
	SnakeSpeedCounter = 0;
	aeg = 0;
	aegtimer = 0;
}

void Game::ComposeFrame()
{
	brd.DrawBorder();

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	if (GameIsStarted) {
		int speed = 21 - SnakeMovePeriod;
		//font.DrawText("Kiirus:" + std::to_string(speed), {220, 810}, Colors::White, gfx);
		font.DrawText("Kiirus:" + std::to_string(SnakeMovePeriod), { 220, 810 }, Colors::White, gfx);
		//font.DrawText("Aeg: " + std::to_string(aeg), { 380, 810 }, Colors::White, gfx);
		font.DrawText("Punktid: " + std::to_string(points), { 20, 810 }, Colors::White, gfx);
		brd.DrawBorder();
		snake.Draw(brd);
		goal.Draw(brd);
		if (GameIsOver) {
			gfx.PutPixel(350, 354, Colors::Red);
			gfx.PutPixel(351, 354, Colors::Red);
			gfx.PutPixel(350, 355, Colors::Red);
			gfx.PutPixel(351, 355, Colors::Red);

			gfx.PutPixel(356, 354, Colors::Red);
			gfx.PutPixel(357, 354, Colors::Red);
			gfx.PutPixel(356, 355, Colors::Red);
			gfx.PutPixel(357, 355, Colors::Red);

			gfx.PutPixel(430, 354, Colors::Red);
			gfx.PutPixel(431, 354, Colors::Red);
			gfx.PutPixel(430, 355, Colors::Red);
			gfx.PutPixel(431, 355, Colors::Red);

			gfx.PutPixel(436, 354, Colors::Red);
			gfx.PutPixel(437, 354, Colors::Red);
			gfx.PutPixel(436, 355, Colors::Red);
			gfx.PutPixel(437, 355, Colors::Red);

			font.DrawText("Mang Labi", { 330, 350 }, Colors::Red, gfx);
			font.DrawText("Vajuta Enterit, Et Uuesti Alustada", {120, 378}, Colors::Red, gfx);
		}
	}
	else {
		font.DrawText("Vajuta Enterit", { 310, 350 }, Colors::White, gfx);
	}

}

void Game::printFPS(Graphics& gfx)
{
	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int fps; fps++;

	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
		oldTime = std::chrono::high_resolution_clock::now();
		lastFps = fps;
		fps = 0;
	}
}