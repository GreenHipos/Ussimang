#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{ 10,100,32 },
		{ 10,130,48 },
		{ 18,160,48 },
		{ 10,130,48 }
	};

	for (int i = 0; i < nSegmentsMax; ++i) {
		segments[i].InitBody( bodyColors[i % nBodyColors] );
	}

	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		nSegments++;
	}
}

int Snake::getSegmentA() {
	return nSegments;
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Segment::Reset()
{
	loc.x = 2;
	loc.y = 2;
}

void Snake::ResetSeg() {
	nSegments = 1;
	Snake::segments->Reset();
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileWith(const Location & target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody( Color c_n )
{
	c = c_n;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_location)
{
	assert(abs(delta_location.x) + abs(delta_location.y) == 1);
	loc.Add(delta_location);
}

void Snake::Segment::Draw( Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
