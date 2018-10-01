#ifndef BOARD_H
#define BOARD_H

#include <cstring>
#include <set>
#include <map>

typedef __UINT32_TYPE__ U32;

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
    std::set<std::pair<int, int>> genEat(bool);
    std::set<std::pair<int, int>> genMove(bool);
    int pieceOfIndex(int);
    U32 CGen(int);
private:
    U32 piece[16];
    U32 red, black, occupied;
    U32 moves[32];
    U32 nk:1, ng:2, nm:2, nr:2, nn:2, nc:2, np:3;
    U32 nK:1, nG:2, nM:2, nR:2, nN:2, nC:2, nP:3;
};

#endif // BOARD_H
