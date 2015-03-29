#ifndef AH_POS_H
#define AH_POS_H

namespace ah {

struct Position {
    int x;
    int y;
	Position(int x, int y) : x(x), y(y) {}
	Position() : x(-1), y(-1) {}

	//friend Position& operator+(const Position& a, const Position& b);

	static Position Right() { return Position(1,  0); }
	static Position Down()	{ return Position(0,  1); }
	static Position Left()	{ return Position(-1, 0); }
	static Position Up()	{ return Position(0, -1); }
};

//Position& operator+(const Position& a, const Position& b) {
//	return Position(a.x + b.x, a.y + b.y);
//}

} // namespace ah

#endif // AH_POS_H
