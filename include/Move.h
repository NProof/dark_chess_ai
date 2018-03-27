#ifndef MOVE_H
#define MOVE_H
//
#include <Check.h>
#include <Chess.h>
#include <cstring>

class Check;
class Chess;

class Move
{
    public:
        Move(Chess *, Check *);
        virtual ~Move();

        void generateMove(char [6]);
        void makeMove(char [6]);

    protected:

    private:
        Chess * chess;
        Check * check;
};

#endif // MOVE_H
