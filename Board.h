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

        bool operator<(const Board&) const;

        void makeMove(std::string);
        std::set<std::pair<std::string, std::string>> getMoveValid(bool);
        std::map<char, int> getDarkPieces();
        std::set<std::string> getSetCheckDark();
    protected:

    private:
        std::string jumpTo(std::string, Path);
		bool momentum(char, char);
		bool isDark(std::string);
		void doLight(std::string, char);
		bool isLight(std::string);
		bool isEmpty(std::string);

		std::map<char, int> darkPieces;
        std::set<std::string> setCheckDark;
        std::map<std::string, char> map_Char;
        std::map<std::string, std::map<Path, std::string>> pathTo;
};

#endif // BOARD_H
