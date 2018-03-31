#ifndef MOVE_H
#define MOVE_H
//
#include "Check.h"
#include "Chess.h"
#include <cstring>

class Check;
class Chess;
enum class Path;

class Move
{
    public:
        Move(Chess *, Path path, Check *);
        virtual ~Move();

        void generateMove(char [6]);
        void makeMove(char [6]);

//    protected:

//    private:
        Chess * chess;
		Path path;
        Check * check;
};

#endif // MOVE_H
