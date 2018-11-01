#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <set>
#include "Protocol.h"
#include "Board.h"
#include "Move.h"
#include "Score.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        void setColor(PROTO_CLR);
        void generateMove(char *);
        void makeMove(char *);

        bool getColor();

    protected:

    private:
        std::set<Board::Move *> next(Board);
        std::map<Board, int> next(Board::Move);
        Score score(Board *);
        Score score(Board::Move *);

        PROTO_CLR color;
        Board *board;
        std::map<Board, std::set<Board::Move *>> B2MS;
        std::map<Board::Move, std::map<Board , int>> M2BM;
};

#endif // PLAYER_H
