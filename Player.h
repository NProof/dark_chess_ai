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

		Board * board;
	protected:

	private:
		std::vector<std::pair<SetBoard, std::string> > multi_level(int); //one layer : level is 0

		std::map<Mov *, SetBoard> next(Board);
		Score score(Board, int);
		Score score(SetBoard, int);

		PROTO_CLR color;
};

#endif // PLAYER_H
