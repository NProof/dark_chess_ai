#ifndef BOARD_H
#define BOARD_H

#include <set>
#include <map>
#include "Protocol.h"
#include "Score.h"

enum class Path{Up, Down, Left, Right};

class Board
{
	public:
		Board();
		virtual ~Board();

		bool operator<(const Board&) const;
		bool operator==(const Board&) const;
		bool operator!=(const Board&) const;

		class SetBoard;

		Score * getScore();

		void makeMove(std::string);
		PROTO_CLR getTrun();
		std::set<std::pair<std::string, std::string>> getMoveValid();
		std::map<char, int> getDarkPieces();
		std::set<std::string> getSetCheckDark();
		std::map<char, int> getLightPieces();
		int n_red;
		int n_black;
		int nD_red;
		int nD_black;
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

		PROTO_CLR trun = PROTO_CLR::PCLR_UNKNOW;
		std::map<char, int> darkPieces;
		std::set<std::string> setCheckDark;
		std::map<std::string, char> map_Char;
		std::set<std::pair<std::string, std::string> > moveValid;
		std::map<std::string, std::map<Path, std::string> > pathTo;
};

#endif // BOARD_H
