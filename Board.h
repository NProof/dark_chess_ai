#ifndef BOARD_H
#define BOARD_H

#include <cstring>
#include <vector>
#include <set>
#include <map>
#include "Protocol.h"
#include "SetBoard.h"
#include "Score.h"

class SetBoard;

enum class Path{Up, Down, Left, Right};

enum class TYPEOFMOVE{FLIP, EAT, JUMP, MOVE};

struct Mov
{
	std::string str;
	TYPEOFMOVE type;
};

class Board
{
	public:
		Board();
		virtual ~Board();

		bool operator<(const Board&) const;
		bool operator==(const Board&) const;
		bool operator!=(const Board&) const;

		Score * getScore();

		std::map<Mov *, SetBoard> next();
		void makeMove(std::string);
		PROTO_CLR getTrun();
		std::vector<Mov *> SetMoveValid();
		std::map<char, int> getDarkPieces();
		std::set<std::string> getSetCheckDark();
		std::map<char, int> getLightPieces();
		int n_red;
		int n_black;
		int d_red;
		int d_black;
		std::vector<std::string> safePlace();
	protected:

	private:
		std::string jumpTo(std::string, Path);
		bool momentum(char, char);
		bool isDark(std::string);
		void doLight(std::string, char);
		bool isLight(std::string);
		bool isEmpty(std::string);

		int powers();
		int method();

		Score * score = NULL;

		PROTO_CLR trun;
		std::map<char, int> darkPieces;
		std::set<std::string> setCheckDark;
		std::map<std::string, char> map_Char;
		std::vector<Mov *> moveValid;
		std::map<std::string, std::map<Path, std::string> > pathTo;
};

#endif // BOARD_H
