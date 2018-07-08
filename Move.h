#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"

class Move
{
    public:
        Move(Board *, bool, std::string, std::string);
        virtual ~Move();

        Board * getSrcBoard();
        bool getColor();
        std::string getSrcMove();
        std::string getDstMove();
    protected:

    private:
        Board * srcBoard;
        bool color;
        std::string srcMove;
        std::string dstMove;
};

#endif // MOVE_H
