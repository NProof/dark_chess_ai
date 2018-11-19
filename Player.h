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

		bool getColor();

		Board board;
	protected:

	private:
		std::vector<SetBoard> multi_level(int); //one layer : level is 0

		std::map<std::string, SetBoard> next(Board);
		std::map<Board, int> next(SetBoard);
		Score score(Board, int);
		Score score(SetBoard, int);

		PROTO_CLR color;
};

#endif // PLAYER_H
