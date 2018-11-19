#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <set>
#include "Protocol.h"
#include "Board.h"
#include "Score.h"
#include "SetBoard.h"

class Player
{
	public:
		Player();
		virtual ~Player();

		void setColor(PROTO_CLR);
		void generateMove(char *);
		void makeMove(char *);

		bool getColor();

	protected:

	private:
		std::vector<Board::SetBoard> multi_level(int); //one layer : level is 0

		std::set<Board::SetBoard> next(Board);
		std::map<Board, int> next(Board::SetBoard);
		Score score(Board, int);
		Score score(Board::SetBoard, int);

		PROTO_CLR color;
		Board board;
};

#endif // PLAYER_H
