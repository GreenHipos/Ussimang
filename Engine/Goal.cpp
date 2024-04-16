#include "Goal.h"

Goal::Goal(std::mt19937 rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937 rng, const Board & brd, const Snake & snake)
{
	//std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 1);
	//std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 1);
	int xDist = 1 + (rand() % brd.GetGridWidth() - 1);
	int yDist = 1 + (rand() % brd.GetGridHeight() - 1);

	Location newLoc;

	do {
		newLoc.x = xDist;
		newLoc.y = yDist;
	} while (snake.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
