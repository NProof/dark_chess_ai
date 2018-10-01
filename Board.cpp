#include "Board.h"

int index32[32] = {31,0,1,5,2,16,27,6,3,14,17,19,28,11,7,21,30,4,15,26,13,18,10,20,29,25,12,9,24,8,23,22};

int BitsHash(U32 x)
{
	return (x * 0x08ED2BE6) >> 27;
}

int GetIndex(U32 mask)
{
	return index32[BitsHash(mask)];
}

U32 LS1B(U32 x)
{
	return x & (-x);
}

Board::Board()
:piece({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,__UINT32_MAX__})
,red(0), black(0), occupied(__UINT32_MAX__)
,moves({0})
,nk(1), ng(2), nm(2), nr(2), nn(2), nc(2), np(5)
,nK(1), nG(2), nM(2), nR(2), nN(2), nC(2), nP(5)
{}

Board::~Board()
{
	//dtor
}

bool Board::operator<(const Board& other) const
{
    for(int i=0; i<16; i++)
    {
        if(piece[i] == other.piece[i])
            i++;
        else return piece[i] < other.piece[i];
    }
}

std::string stringOfIndex(int index)
{
    return std::string({'a'+(index%4), '1'+(3-index/4)});
}

int intOfString(std::string str)
{
    return 4 * (str[1]-'1') + (str[0]-'a');
}

void Board::makeMove(std::string move)
{
	std::string src, dst;

	src = move.substr(0, 2);
    int isrc = intOfString(src);
	if(move[2]=='-')
	{
		dst = move.substr(3, 2);
        int psrc = pieceOfIndex(isrc);
		int idst = intOfString(dst);
		int pdst = pieceOfIndex(idst);
//		map_Char[dst] = map_Char[src];
//		map_Char.erase(src);
        piece[pdst] = piece[pdst]^(0x1<<idst);
        piece[psrc] = piece[psrc]^((0x1<<isrc)|(0x1<<idst));
	}
	else
	{
//		doLight(src, move[3]);
        std::string kinds = "-KGMRNCPkgmrncpX";
        piece[(int)strchr(kinds.c_str(), move[3])] ^= 0x1>>isrc;
	}
}

int Board::pieceOfIndex(int index)
{
    for(int i=0; i<16; i++)
        if(piece[i]&(0x1<<index))
            return i;
}

std::set<std::pair<std::string, std::string>> Board::getMoveValid(bool turn)
{
	std::set<std::pair<std::string, std::string>> mValid;
	std::set<std::pair<int,int>> moves = genMove(!turn);
	for(auto it = moves.begin(); it != moves.end(); it++)
    {
        mValid.insert(std::pair<std::string, std::string>(stringOfIndex(it->first), stringOfIndex(it->second)));
    }
	moves = genEat(!turn);
	for(auto it = moves.begin(); it != moves.end(); it++)
    {
        mValid.insert(std::pair<std::string, std::string>(stringOfIndex(it->first), stringOfIndex(it->second)));
    }
	return mValid;
}

std::map<char, int> Board::getDarkPieces()
{
	return std::map<char, int>{{'k',(U32)nk},{'g',(U32)ng},{'m',(U32)nm},{'r',(U32)nr},{'n',(U32)nn},{'c',(U32)nc},{'p',(U32)np}
	,{'K',(U32)nK},{'G',(U32)nG},{'M',(U32)nM},{'R',(U32)nR},{'N',(U32)nN},{'C',(U32)nC},{'P',(U32)nP}};
}

std::set<std::string> Board::getSetCheckDark()
{
	std::set<std::string> ret;
	U32 dark = piece[15];
	while(dark)
    {
        U32 mask = LS1B(dark);
        dark ^= mask;
        int index = GetIndex(mask);
        ret.insert(stringOfIndex(index));
    }
    return ret;
}

U32 MS1B(U32 x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return (x>>1) + 1;
}

U32 Rank[8] = {0xF, 0xF0, 0xF00, 0xF000, 0xF0000, 0xF00000, 0xF000000, 0xF0000000};
U32 file[4] = {0x11111111, 0x22222222, 0x44444444, 0x88888888};

U32 CGenCL(U32 x)
{
	if(x)
	{
		U32 mask = LS1B(x);
		return (x ^= mask)?LS1B(x):0;
	}
	else return 0;
}

U32 CGenCR(U32 x)
{
	if(x)
	{
		U32 mask = MS1B(x);
		return (x ^= mask)?MS1B(x):0;
	}
	else return 0;
}

U32 Board::CGen(int src)
{
	int r = src/4, c = src%4;
	U32 result;
	U32 x = ((Rank[r] & occupied)^(1<<src)) >> (4*r);
	switch(c)
	{
	case 0:
		result = CGenCL(x) << (4*r);
		break;
	case 1:
		result = ((x == 0xc) ? 0x8 : 0x0) << (4*r);
		break;
	case 2:
		result = ((x == 0x3) ? 0x1 : 0x0) << (4*r);
		break;
	case 3:
		result = CGenCR(x) << (4*r);
		break;
	}
	x = ((file[c] & occupied)^(1<<src)) >> c;
	switch(r)
	{
	case 0:
		result |= CGenCL(x) << c;
		break;
	case 1:
		result |= CGenCL(x&0x11111100) << c;
		break;
	case 2:
		result |= (CGenCL(x&0x11111000)|CGenCR(x&0x00000011)) << c;
		break;
	case 3:
		result |= (CGenCL(x&0x11110000)|CGenCR(x&0x00000111)) << c;
		break;
	case 4:
		result |= (CGenCL(x&0x11100000)|CGenCR(x&0x00001111)) << c;
		break;
	case 5:
		result |= (CGenCL(x&0x11000000)|CGenCR(x&0x00011111)) << c;
		break;
	case 6:
		result |= CGenCR(x&0x00111111) << c;
		break;
	case 7:
		result |= CGenCR(x) << c;
		break;
	}
	return result;
}

U32 pMoves[32] = {
	0x00000012, 0x00000025, 0x0000004A, 0x00000084,
	0x00000121, 0x00000252, 0x000004A4, 0x00000848,
	0x00001210, 0x00002520, 0x00004A40, 0x00008480,
	0x00012100, 0x00025200, 0x0004A400, 0x00084800,
	0x00121000, 0x00252000, 0x004A4000, 0x00848000,
	0x01210000, 0x02520000, 0x04A40000, 0x08480000,
	0x12100000, 0x25200000, 0x4A400000, 0x84800000,
	0x21000000, 0x52000000, 0xA4000000, 0x48000000,
};

std::set<std::pair<int, int>> Board::genEat(bool isBlack)
{
	int src;
	U32 dest;
	#ifdef DEBUG
	std::cout << " begin of BitBoard::genMove( " << (isBlack ? "true" : "false") << " )\n";
	#endif // DEBUG
	std::set<std::pair<int, int>> ret;
	for(int i=1; i<8; i++)
	{
		U32 p = piece[i+(isBlack?0:7)];
		while(p)
		{
			U32 mask = LS1B(p);
			p ^= mask;
			src = GetIndex(mask);
			if(i==1)
				dest = pMoves[src] & ((isBlack?black:red) ^ piece[14-(isBlack?0:7)]);
			else if(i==2)
				dest = pMoves[src] & ((isBlack?black:red) ^ piece[8-(isBlack?0:7)]);
			else if(i==3)
				dest = pMoves[src] & ((isBlack?black:red) ^ piece[8-(isBlack?0:7)] ^ piece[9-(isBlack?0:7)]);
			else if(i==4)
				dest = pMoves[src] & (piece[11-(isBlack?0:7)]|piece[12-(isBlack?0:7)]|piece[13-(isBlack?0:7)]|piece[14-(isBlack?0:7)]);
			else if(i==5)
				dest = pMoves[src] & (piece[12-(isBlack?0:7)]|piece[13-(isBlack?0:7)]|piece[14-(isBlack?0:7)]);
			else if(i==6)
				dest = CGen(src) & (isBlack?black:red);
			else if(i==7)
				dest = pMoves[src] & (piece[8-(isBlack?0:7)]|piece[14-(isBlack?0:7)]);
			else
				dest = 0;
			while(dest)
			{
				U32 mask2 = LS1B(dest);
				dest ^= mask2;
				U32 result = GetIndex(mask2);
				ret.insert(std::pair<int, int>(src, result));
				#ifdef DEBUG
				std::cout << std::dec << src << " -> " <<  result << "\n";
				#endif // DEBUG
			}
		}
	}
	#ifdef DEBUG
	std::cout << " end of BitBoard::genEat( " << (isBlack ? "true" : "false") << " )\n";
	#endif // DEBUG
	return ret;
}

std::set<std::pair<int, int>> Board::genMove(bool isBlack)
{
	int src;
	U32 dest;
	#ifdef DEBUG
	std::cout << " begin of BitBoard::genMove( " << (isBlack ? "true" : "false") << " )\n";
	#endif // DEBUG
	std::set<std::pair<int, int>> ret;
	for(int i=1; i<8; i++)
	{
		U32 p = piece[i+(isBlack?0:7)];
		while(p)
		{
			U32 mask = LS1B(p);
			p ^= mask;
			src = GetIndex(mask);
			if(i <= 1 && i <= 7)
				dest = pMoves[src] & piece[0];
			else
				dest = 0;
			while(dest)
			{
				U32 mask2 = LS1B(dest);
				dest ^= mask2;
				U32 result = GetIndex(mask2);
				ret.insert(std::pair<int, int>(src, result));
				#ifdef DEBUG
				std::cout << std::dec << src << " -> " <<  result << "\n";
				#endif // DEBUG
			}
		}
	}
	#ifdef DEBUG
	std::cout << " end of BitBoard::genMove( " << (isBlack ? "true" : "false") << " )\n";
	#endif // DEBUG
	return ret;
}
