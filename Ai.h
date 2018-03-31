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

	void initBoardState(int [14], char [32]);
	color(PROTO_CLR);
	generateMove();
	MakeMove();

//	std::map<Type,std::set<Check *>> myChecks;
//	std::map<Type,std::set<Check *>> matchChecks;
//private:
	bool turn;
    PROTO_CLR colorOfAi;
    Broad * broadOfAi ;
};
#endif // AI_H
