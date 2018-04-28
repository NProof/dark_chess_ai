#include "Board.h"

Board::Board()
{
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
        setcheckdark.insert(stri);

		if(i/4>0)
			pathTo[stri][Path::Up] = std::string{char('a'+i%4),char('8'-i/4+1)};
		if(i/4<7)
			pathTo[stri][Path::Down] = std::string{char('a'+i%4),char('8'-i/4-1)};
		if(i%4>0)
			pathTo[stri][Path::Left] = std::string{char('a'+i%4-1),char('8'-i/4)};
		if(i%4<3)
			pathTo[stri][Path::Right] = std::string{char('a'+i%4+1),char('8'-i/4)};
    }
    mapchessesdark = std::map<char, int>
        {{'k',1},{'g',2},{'m',2},{'r',2},{'n',2},{'c',2},{'p',5}
        ,{'K',1},{'G',2},{'M',2},{'R',2},{'N',2},{'C',2},{'P',5}};
}

Board::~Board()
{
    //dtor
}

std::set<std::pair<std::string, std::string>> Board::updateMoves(bool trun)
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
            std::map<Path, std::string>::iterator it;
            for(it=pathTo[stri].begin(); it!=pathTo[stri].end(); it++)
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

void Board::makeMove(char *move)
{
    std::string src, dst;

    src = std::string{move[0],move[1]};
    if(move[2]=='-')
    {
        dst = std::string{move[3],move[4]};
        map_Char[dst] = map_Char[src];
        map_Char.erase(src);
    }
    else
	{
	    doLight(src, move[3]);
	}
}

std::set<std::pair<std::string, std::string>> Board::getMoveValid(bool color)
{
    std::set<std::pair<std::string, std::string>> result = updateMoves(color);
    std::string stri;
    std::set<std::string>::iterator setDarkIt;
    for(setDarkIt = setcheckdark.begin(); setDarkIt != setcheckdark.end(); setDarkIt++)
    {
        stri = *setDarkIt;
        result.insert(std::pair<std::string, std::string>(stri, stri));
    }
    return result ;
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
    return setcheckdark.count(strp) ;
}

void Board::doLight(std::string strp, char cchess)
{
    map_Char[strp] = cchess ;
    setcheckdark.erase(strp);
    mapchessesdark[cchess] = mapchessesdark[cchess] - 1;
}

bool Board::isLight(std::string strp)
{
    return map_Char.count(strp) ;
}

bool Board::isEmpty(std::string strp)
{
    return !isDark(strp)&&!isLight(strp);
}
