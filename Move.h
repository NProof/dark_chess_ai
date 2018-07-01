#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"
#include "Player.h"

class Player;
class Move
{
    public:
        Move(bool, Board, std::string);
        Move(bool, Board, std::string, int, std::map<char, int>);
        virtual ~Move();

        bool operator<(const Move& other) const;

        std::string getStringMove() const;
    protected:

    private:
        bool color;
        std::string strMove;
        int iDark;
        std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
