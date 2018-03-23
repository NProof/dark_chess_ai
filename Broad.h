#ifndef BROAD_H
#define BROAD_H
#include <utility>
#include <set>

#include "Check.h"

#ifndef PROTOCAL
#define PROTOCAL
enum PROTO_CLR{PCLR_RED, PCLR_BLACK, PCLR_UNKNOW};
#endif

class Broad
{
public:
	Broad();
//	std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>> initBroad(int [14], char [32]);
	void initBroad(char [32]);
//	void initBroad(int [14], char [32]);

//	std::set<Check *> unknownChecks;
    std::map<std::string, Check *> mapOfName;

//private:
	Check checks[32];
//	std::multiset<std::pair<bool, Type>> unknownSet;

	static int intOfPosition(char);
	static std::pair<bool, Type> pairOfInt(int);
	static Type typeOfInt(int);
};
#endif // BROAD_H
