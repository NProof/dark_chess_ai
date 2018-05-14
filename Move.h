#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"
#include "Player.h"

class Player;
class Move
{
    public:
        Move(Player *, Board, std::string);
        Move(Player *, Board, int, std::map<char, int>, std::string);
        virtual ~Move();

        bool operator<(const Move& other) const;

        std::string getStringMove() const;
    protected:

    private:
        Player *player;
        std::string strMove;
        int iDark;
        std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
