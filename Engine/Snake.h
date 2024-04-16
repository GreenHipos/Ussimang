#pragma once

#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_location);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
		void Reset();
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc );
	void Grow();
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Draw(Board& brd) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileWith(const Location& target) const;
	void ResetSeg();
	int getSegmentA();

private:
	static constexpr Color HeadColor = Colors::Yellow;
	static constexpr int nSegmentsMax = 900;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};