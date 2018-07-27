#include "Board.h"

Board::Board()
{
	for(int i=0; i<32; i++)
	{
		std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
		setCheckDark.insert(stri);
	}
	darkPieces = std::map<char, int> {
		{'k',1},{'g',2},{'m',2},{'r',2},{'n',2},{'c',2},{'p',5}
		,{'K',1},{'G',2},{'M',2},{'R',2},{'N',2},{'C',2},{'P',5}
	};
}

Board::~Board()
{
	//dtor
}

bool Board::operator<(const Board& other) const
{
	if(darkPieces == other.darkPieces)
	{
		if(setCheckDark == other.setCheckDark)
		{
			if(map_Char == other.map_Char)
			{
				return false;
			}
			else return map_Char < other.map_Char;
		}
		else return setCheckDark < other.setCheckDark;
	}
	else return darkPieces < other.darkPieces;
}

Board & Board::makeMove(std::string move)
{
	Board * temp = new Board(*this);
	std::string src, dst;

	src = move.substr(0, 2);
	if(move[2]=='-')
	{
		dst = move.substr(3, 2);;
		temp->map_Char[dst] = temp->map_Char[src];
		temp->map_Char.erase(src);
	}
	else
	{
		temp->doLight(src, move[3]);
	}
	return *temp;
}

std::set<std::pair<std::string, std::string>> Board::getMoveValid(bool trun)
{
	std::set<std::pair<std::string, std::string>> mValid;
	std::map<std::string, char>::iterator light;
	for(light=map_Char.begin(); light!=map_Char.end(); light++)
	{
		std::string stri = light->first;
		char cho = light->second;
		bool color = islower(cho);
		if(trun == color)
		{
			std::map<Path, std::string>::const_iterator it;
			for(it = pathTo.at(stri).begin(); it != pathTo.at(stri).end(); it++)
			{
				std::string strj = it->second;
				if(isEmpty(strj))
				{
					mValid.insert(std::pair<std::string, std::string>(stri, strj));
				}
				if(cho=='c'||cho=='C')
				{
					std::string sJump = jumpTo(stri, it->first);
					if(isLight(sJump)&&momentum(cho, map_Char[sJump]))
						mValid.insert(std::pair<std::string, std::string>(stri, sJump));
				}
				else if(isLight(strj))
				{
					if(momentum(cho, map_Char[strj]))
						mValid.insert(std::pair<std::string, std::string>(stri, strj));
				}
			}
		}
	}
	return mValid;
}

std::map<char, int> Board::getDarkPieces()
{
	return darkPieces;
}

std::set<std::string> Board::getSetCheckDark()
{
	return setCheckDark;
}

std::string Board::jumpTo(std::string src, Path path)
{
	while(pathTo.at(src).count(path)&&isEmpty(pathTo.at(src).at(path)))
		src = pathTo.at(src).at(path);
	if(pathTo.at(src).count(path))
	{
		src = pathTo.at(src).at(path);
		while(pathTo.at(src).count(path)&&isEmpty(pathTo.at(src).at(path)))
			src = pathTo.at(src).at(path);
		if(pathTo.at(src).count(path))
		{
			src = pathTo.at(src).at(path);
			return src ;
		}
		else
			return "outer" ;
	}
	else
		return "outer" ;
}

bool Board::momentum(char hig, char low)
{
	return (islower(hig)==islower(low))
		? false : hig=='c'||hig=='C'||
		(hig=='k'&&low!='P')||
		(hig=='g'&&low!='K')||
		(hig=='m'&&(low!='G'&&low!='K'))||
		(hig=='r'&&(low!='M'&&low!='G'&&low!='K'))||
		(hig=='n'&&(low=='N'||low=='C'||low=='P'))||
		(hig=='p'&&(low=='K'||low=='P'))||
		(hig=='K'&&low!='p')||
		(hig=='G'&&low!='k')||
		(hig=='M'&&(low!='g'&&low!='k'))||
		(hig=='R'&&(low!='m'&&low!='g'&&low!='k'))||
		(hig=='N'&&(low=='n'||low=='c'||low=='p'))||
		(hig=='P'&&(low=='k'||low=='p'));
}

bool Board::isDark(std::string strp)
{
	return setCheckDark.count(strp) ;
}

void Board::doLight(std::string strp, char cchess)
{
	map_Char[strp] = cchess ;
	setCheckDark.erase(strp);
	darkPieces[cchess] = darkPieces[cchess] - 1;
}

bool Board::isLight(std::string strp)
{
	return map_Char.count(strp) ;
}

bool Board::isEmpty(std::string strp)
{
	return !isDark(strp)&&!isLight(strp);
}

const std::map<std::string, std::map<Path, std::string>> Board::pathTo = initPathTo();

const std::map<std::string, std::map<Path, std::string>> Board::initPathTo()
{
	std::map<std::string, std::map<Path, std::string>> ret;
	for(int i=0; i<32; i++)
	{
		std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
		if(i/4>0)
			ret[stri][Path::Up] = std::string{char('a'+i%4),char('8'-i/4+1)};
		if(i/4<7)
			ret[stri][Path::Down] = std::string{char('a'+i%4),char('8'-i/4-1)};
		if(i%4>0)
			ret[stri][Path::Left] = std::string{char('a'+i%4-1),char('8'-i/4)};
		if(i%4<3)
			ret[stri][Path::Right] = std::string{char('a'+i%4+1),char('8'-i/4)};
	}
	return ret;
}
