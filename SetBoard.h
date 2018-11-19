#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"

class SetBoard
{
	public:
		SetBoard(Board, std::string);
		SetBoard(Board, std::string, int, std::map<char, int>);
		virtual ~SetBoard();

		bool operator<(const SetBoard& other) const;

		std::string getStringMove();
		int GetiDark();
		std::map<Board, int> GetpossibleBoards();
	protected:

	private:
		std::string strMove;
		int iDark;
		std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
