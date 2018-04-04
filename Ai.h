#ifndef AI_H
#define AI_H
#include <map>

#include "Broad.h"

#ifndef PROTOCAL
#define PROTOCAL
enum PROTO_CLR{PCLR_RED, PCLR_BLACK, PCLR_UNKNOW};
#endif

class Ai
{
public:
	Ai();

//	void initBoardState(int [14], char [32]);
	void color(PROTO_CLR);
	bool generateMove(char *);
	bool MakeMove(char *);
	void updateMoves();

	std::set<Chess *> belongs;
    std::set<Move *> movesNext;

//private:
	bool turn;
    PROTO_CLR colorOfAi;
    Broad * broadOfAi ;
};
#endif // AI_H
