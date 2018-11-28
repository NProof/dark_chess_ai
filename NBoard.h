#include <iostream>
#include <cassert>
#include <string>
#include "Board.h"

using namespace std;

enum TypeOfChess
{
	King
	,Guard
	,Minister
	,Rook
	,Knight
	,Cannon
	,Pawn
};

struct Kinds
{
	int k:1, g:2, m:2, r:2, n:2, c:2, p:3;
};

struct Chess
{
	TypeOfChess type:3;
	bool dark:1;
	unsigned __int8 r1:2, r2:2;
	unsigned __int8 l1:2, l2:2;
	unsigned __int8 u1:3, u2:3;
	unsigned __int8 d1:3, d2:3;
};

enum TypeOfAction
{
	Filp
	,Eat
	,Jump
	,Mov
};

struct Action
{
	TypeOfAction type:2;
	unsigned __int8 pos:5;
	unsigned __int8 tmp:1;
	TypeOfChess tChess:3;
	unsigned __int8 dir:2;
	unsigned __int8 len:3;
};

class NBoard : public Board
{
	public:
		NBoard();

		int indexOfStr(string);

		void isomorphism_number();
		void isomorphism_kinds();
		void isomorphism_piece();

		unsigned int own_l:5; //(Light Own)
		unsigned int own_d:5; //(Dark Own)
		unsigned int opp_l:5; // (Light Opp)
		unsigned int opp_d:5; // (Dark Own)
		Kinds ownlk; // (Light Own Kinds)
		Kinds opplk; // (Light Opp Kinds)
		Kinds owndk; // (Dark Own Kinds)
		Kinds oppdk; // (Dark Opp Kinds)
		unsigned __int32 ownlp; // (Light Own Piece)
		unsigned __int32 opplp; // (Light Opp Piece)
		unsigned __int32 darkp; // (Dark Piecese)
		Chess chesses[32]; // (all chess with position)
};
