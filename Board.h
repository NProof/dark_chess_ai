#ifndef BOARD_H
#define BOARD_H

#include <set>
#include <map>

enum class Path{Up, Down, Left, Right};

class Board
{
    public:
        Board();
        virtual ~Board();

        void generateMove();
        void makeMove(char *move);

        std::set<std::pair<std::string, std::string>> getMoveValid(bool);
    protected:

    private:
        std::string jumpTo(std::string, Path);
		bool momentum(char, char);

        std::map<std::string, char> map_Char;
        std::map<std::string, std::map<Path, std::string>> pathTo;
        std::set<std::string> darks;
        std::map<bool, std::set<std::pair<std::string, std::string>>> mValid;
};

#endif // BOARD_H
