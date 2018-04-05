#ifndef BOARD_H
#define BOARD_H

#include <set>
#include <map>

enum class Path{Up, Down, Left, Right};

class Board
{
    public:
        Board(char*&);
        virtual ~Board();

        void makeMove(char *move);
        std::string jumpTo(std::string, Path);
		bool momentum(char, char);

        std::map<std::string, char> getMapChar();
        std::map<std::string, std::map<Path, std::string>> getPathTo();
    protected:

    private:
        std::map<std::string, char> map_Char;
        std::map<std::string, std::map<Path, std::string>> pathTo;
};

#endif // BOARD_H
