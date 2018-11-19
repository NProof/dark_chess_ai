#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"

class Board::SetBoard
{
	public:
		SetBoard(Board, std::string);
		SetBoard(Board, std::string, int, std::map<char, int>);
		virtual ~SetBoard();

		bool operator<(const SetBoard& other) const;

		Board GetOringinB();
		std::string getStringMove();
		int GetiDark();
		std::map<char, int> GetpossibleKinds();
		std::map<Board, int> GetpossibleBoards();
	protected:

	private:
		Board originB;
		std::string strMove;
		int iDark;
		std::map<char, int> possibleKinds;
		std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
