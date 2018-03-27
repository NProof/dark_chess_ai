#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <set>
#include <Move.h>
#include <Check.h>

class Move;
class Check;

enum class Type
{
	Soldier, Cannon, Horse, Chariot, Elephant, Advisor, General, Unknown
};

class Chess
{
    public:
        Chess(char);
        virtual ~Chess();

        void init(char);
        friend std::ostream& operator<<(std::ostream& os, const Chess& chess);
        void update();

        bool color;
        Type type;
        Check * check;
        std::set<Move *> setOfMoves;

    protected:

    private:
};

#endif // CHESS_H
