#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "Protocol.h"
#include "Board.h"
#include "Move.h"
#include "Score.h"

class Move;
class Player
{
public:
	Player();
	virtual ~Player();

	void setColor(PROTO_CLR);
	void generateMove(char *);
	void makeMove(char *);
	void makeMove(const char *, Board *&);

	bool getColor();
protected:

private:
	std::set<Move *> next(Board *, bool);
	std::pair<std::map<Board *, int>, bool> next(Move *);
	Score score(Move *, int);
	Score score(Board *, bool, int);

	bool color;
	Board * board;

	std::map<Board, Board *> theOne;
	std::map<Board *, std::set<Move *>> B2MS;
	std::map<Move *, std::map<Board *, int>> M2BM;
};

#endif // PLAYER_H
