#ifndef CHECK_H
#define CHECK_H
#include <iostream>
#include <map>

#include "Chess.h"

/* enum class Type
{
//	Space, Soldier, Cannon, Horse, Chariot, Elephant, Advisor, General, Unknown
	Soldier, Cannon, Horse, Chariot, Elephant, Advisor, General, Unknown
}; */

enum class Path
{
	Up, Down, Left, Right
};

class Check
{
public:
	Check();

    std::string name;
//	Type type;
    Chess * chess;
	std::map<Path, Check *> pathsTo;

	Check * jumpTo(Path);
	Check * leavTo(Path);

};
#endif
