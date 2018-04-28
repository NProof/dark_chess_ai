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

        std::set<std::pair<std::string, std::string>> updateMoves(bool);
        void makeMove(char *move);

        std::set<std::pair<std::string, std::string>> getMoveValid(bool);
    protected:

    private:
        std::string jumpTo(std::string, Path);
		bool momentum(char, char);
		bool isDark(std::string);
		void doLight(std::string, char);
		bool isLight(std::string);
		bool isEmpty(std::string);

		std::map<char, int> mapchessesdark;
        std::set<std::string> setcheckdark;
        std::map<std::string, char> map_Char;
        std::map<std::string, std::map<Path, std::string>> pathTo;
};

#endif // BOARD_H
