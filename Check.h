#ifndef CHECK_H
#define CHECK_H

#include <map>
#include <set>
#include "Chess.h"
#include "Move.h"

class Chess;
class Move;

enum class Path
{
	Up, Down, Left, Right
};

class Check // 盤面位置
{
    public:
        Check();
        virtual ~Check();

        Check * jumpTo(Path);
//        void pickon();
//        void pickoff(Move *);

        Chess * chess;
        std::map<Path, Check *> pathsTo;
        std::string name;
        std::set<Move *> setOfMoves;

    protected:

    private:
        Check * leavTo(Path);
};

#endif // CHECK_H
