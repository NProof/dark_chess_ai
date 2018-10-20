#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"
#include "Score.h"

class Score;

class Move
{
    public:
        Move(bool, Board, std::string);
        Move(bool, Board, std::string, int, std::map<char, int>);
        virtual ~Move();

        bool operator<(const Move& other) const;

        bool Getcolor() const;
        std::string getStringMove() const;
        int GetiDark() const;
		std::map<Board, int> GetpossibleBoards() const;
		Score * Getscore();
    protected:

    private:
        bool color;
        std::string strMove;
        int iDark;
        std::map<Board, int> possibleBoards;
		Score * score;
};

#endif // MOVE_H
