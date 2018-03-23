#ifndef CHESS_H
#define CHESS_H
#include <iostream>

enum class Type
{
	Soldier, Cannon, Horse, Chariot, Elephant, Advisor, General, Unknown
};

class Chess
{
public:
//	Chess();
	Chess(char);

private:
	bool color;
	Type type;
};
#endif
