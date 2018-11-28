#include "Board.h"

Board::Board()
:n_red(16), n_black(16)
,d_red(16), d_black(16)
,turnPlay(PROTO_CLR::PCLR_UNKNOW)
{
	for(int i=0; i<32; i++)
	{
		std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
		setCheckDark.insert(stri);

		if(i/4>0)
			pathTo[stri][Path::Up] = std::string{char('a'+i%4),char('8'-i/4+1)};
		if(i/4<7)
			pathTo[stri][Path::Down] = std::string{char('a'+i%4),char('8'-i/4-1)};
		if(i%4>0)
			pathTo[stri][Path::Left] = std::string{char('a'+i%4-1),char('8'-i/4)};
		if(i%4<3)
			pathTo[stri][Path::Right] = std::string{char('a'+i%4+1),char('8'-i/4)};
	}
	darkPieces = std::map<char, int> {
		{'k',1},{'g',2},{'m',2},{'r',2},{'n',2},{'c',2},{'p',5}
		,{'K',1},{'G',2},{'M',2},{'R',2},{'N',2},{'C',2},{'P',5}
	};
}

Board::~Board()
{
	if(score)
		delete score;
}

bool Board::operator<(const Board& other) const
{
	if(turnPlay != other.turnPlay)
		return turnPlay < other.turnPlay;
	if(n_red != other.n_red)
		return n_red < other.n_red;
	if(n_black != other.n_black)
		return n_black < other.n_black;
	if(darkPieces != other.darkPieces)
		return darkPieces < other.darkPieces;
	if(setCheckDark != other.setCheckDark)
		return setCheckDark < other.setCheckDark;
	if(map_Char != other.map_Char)
		return map_Char < other.map_Char;
	return false;
}

bool Board::operator==(const Board& other) const
{
	return !this->operator<(other) && !other.operator<(*this);
}

bool Board::operator!=(const Board& other) const
{
	return this->operator<(other) || other.operator<(*this);
}

Score * Board::getScore()
{
	if(score == NULL)
	{
		if(turnPlay == PROTO_CLR::PCLR_RED)
		   score = new Score(n_red, n_black, method(), powers(), 1);
		else
		   score = new Score(n_black, n_red, method(), powers(), 1);
	}
	return score;
}

std::map<Mov *, SetBoard> Board::next()
{
	std::map<Mov *, SetBoard> temp;
	for(auto mov : SetMoveValid())
	{
		temp.insert(std::pair<Mov *, SetBoard>(
			mov, SetBoard(*this, mov->str))
		);
	}
	for(auto setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
	{
		Mov * mov = new Mov();
		mov->str = *setCheckDarkIt+'-'+*setCheckDarkIt;
		mov->type = TYPEOFMOVE::FLIP;
		temp.insert(std::pair<Mov *, SetBoard>(
			mov, SetBoard(*this, mov->str, setCheckDark.size(), darkPieces))
		);
	}
	return temp;
}

void Board::makeMove(std::string move)
{
	std::string src, dst;

	src = move.substr(0, 2);
	if(move[2]=='-')
	{
		dst = move.substr(3, 2);
		if(map_Char.count(dst))
		{
			if(islower(map_Char[dst]))
				n_black--;
			else n_red--;
		}

		map_Char[dst] = map_Char[src];
		map_Char.erase(src);

		switch(turnPlay){
		case PROTO_CLR::PCLR_RED :
			turnPlay = PROTO_CLR::PCLR_BLACK;
			break;
		case PROTO_CLR::PCLR_BLACK :
			turnPlay = PROTO_CLR::PCLR_RED;
			break;
		case PROTO_CLR::PCLR_UNKNOW :
			exit(9);
		};
	}
	else
	{
	    doLight(src, move[3]);

	    if(islower(move[3]))
			d_black--;
		else d_red--;

	    switch(turnPlay){
		case PROTO_CLR::PCLR_RED :
			turnPlay = PROTO_CLR::PCLR_BLACK;
			break;
		case PROTO_CLR::PCLR_BLACK :
			turnPlay = PROTO_CLR::PCLR_RED;
			break;
		case PROTO_CLR::PCLR_UNKNOW :
			turnPlay = !islower(move[3]) ? PROTO_CLR::PCLR_RED : PROTO_CLR::PCLR_BLACK ;
			break;
		};
	}
	moveValid = SetMoveValid();
}

PROTO_CLR Board::getturnPlay()
{
	return turnPlay;
}

std::vector<Mov *> Board::SetMoveValid()
{
	std::vector<Mov *> mValid;
	std::map<std::string, char>::iterator light;
	for(light=map_Char.begin(); light!=map_Char.end(); light++)
	{
		std::string stri = light->first;
		char cho = light->second;
		bool color = islower(cho);
		if( (turnPlay == PROTO_CLR::PCLR_UNKNOW) ? false : ((turnPlay == PROTO_CLR::PCLR_RED) == color) )
		{
			std::map<Path, std::string>::iterator it;
			for(it=pathTo[stri].begin(); it!=pathTo[stri].end(); it++)
			{
				std::string strj = it->second;
				if(isEmpty(strj))
				{
					Mov * temp = new Mov();
					temp->str = stri + "-" + strj;
					temp->type = TYPEOFMOVE::MOVE;
					mValid.push_back(temp);
				}
				if(cho=='c'||cho=='C')
				{
					std::string sJump = jumpTo(stri, it->first);
					if(isLight(sJump)&&momentum(cho, map_Char[sJump]))
					{
						Mov * temp = new Mov();
						temp->str = stri + "-" + sJump;
						temp->type = TYPEOFMOVE::JUMP;
						mValid.push_back(temp);
					}
				}
				else if(isLight(strj))
				{
					if(momentum(cho, map_Char[strj]))
					{
						Mov * temp = new Mov();
						temp->str = stri + "-" + strj;
						temp->type = TYPEOFMOVE::EAT;
						mValid.push_back(temp);
					}
				}
			}
		}
	}
	return mValid;
}

std::map<char, int> Board::getLightPieces()
{
	std::map<char, int> lightPieces;
	for(auto ch : map_Char)
		lightPieces[ch.second]++;
	return lightPieces;
}

std::vector<std::string> Board::safePlace()
{
	std::vector<std::string> safe;
	for(auto dark : setCheckDark)
	{
		bool isSafe = true;
		for(auto adj : pathTo[dark])
			if(isLight(adj.second))
			{
				isSafe = false;
				break;
			}
		Path allpath[] = {Path::Up, Path::Down, Path::Left, Path::Right};
		for(Path apath : allpath)
		{
			std::string jumpStr = jumpTo(dark, apath);
			if(jumpStr != "outer" && isLight(jumpStr))
			{
				isSafe = false;
				break;
			}
		}
		if(isSafe)
			safe.push_back(dark);
	}
	return safe;
}

std::string Board::jumpTo(std::string src, Path path)
{
	while(this->pathTo[src].count(path)&&isEmpty(pathTo[src][path]))
		src = this->pathTo[src][path];
	if(this->pathTo[src].count(path))
	{
		src = this->pathTo[src][path];
		while(this->pathTo[src].count(path)&&isEmpty(pathTo[src][path]))
			src = this->pathTo[src][path];
		if(this->pathTo[src].count(path))
		{
			src = this->pathTo[src][path];
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

int Board::method()
{
	return moveValid.size() + setCheckDark.size();
}

int Board::powers()
{
	auto light = getLightPieces();
	auto dark = darkPieces;
	for(auto x : dark){
		light[x.first] += x.second;
	}
	int val =
	(
		light['k']*(light['G']+light['M']+light['R']+light['N']+light['C']-light['P'])
		+light['g']*(light['M']+light['R']+light['N']+light['C']+light['P']-light['K'])
		+light['m']*(light['R']+light['N']+light['C']+light['P']-light['K']-light['G'])
		+light['r']*(light['N']+light['C']+light['P']-light['K']-light['G']-light['M'])
		+light['n']*(light['C']+light['P']-light['K']-light['G']-light['M']-light['R'])
		+light['c']*(light['P']) // -light['K']-light['G']-light['M']-light['R']-light['N'])
		+light['p']*(light['K']-light['G']-light['M']-light['R']-light['N']-light['C'])
	);
	switch(getturnPlay()){
	case PROTO_CLR::PCLR_RED:
		return val;
	case PROTO_CLR::PCLR_BLACK:
		return -val;
	default:
		exit(25);
	};
}
