#pragma once

struct Piece
{
	int Team = -1;//1 is white, 0 is black
	char type = ' ';//pawn,knight,bishop,rook,queen,king
	//           p     n      b      r    q    k
};

class legalMoves
{
public:
	static bool isLegalMove(int orig, int dest, Piece board[64]);
};