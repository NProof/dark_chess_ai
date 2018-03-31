#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <map>
#include "Move.h"
#include "Check.h"

class Move;
class Check;
enum class Path;

enum class Type
{
	Soldier, Cannon, Horse, Chariot, Elephant, Advisor, General, Unknown
};

class Chess // 暗棋
{
    public:
        Chess(char);
        virtual ~Chess();

        void init(char);
        friend std::ostream& operator<<(std::ostream& os, const Chess& chess);
        bool atcCan(Type, Type);
        void pickon();
        void pickoff();

        bool color;
        Type type;
        Check * check;
        std::map<Path, Move *> mapOfMoves;

    protected:

    private:
};

#endif // CHESS_H
