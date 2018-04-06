#include "Board.h"

Board::Board()
{
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
        darks.insert(stri);

		if(i/4>0)
			pathTo[stri][Path::Up] = std::string{char('a'+i%4),char('8'-i/4+1)};
		if(i/4<7)
			pathTo[stri][Path::Down] = std::string{char('a'+i%4),char('8'-i/4-1)};
		if(i%4>0)
			pathTo[stri][Path::Left] = std::string{char('a'+i%4-1),char('8'-i/4)};
		if(i%4<3)
			pathTo[stri][Path::Right] = std::string{char('a'+i%4+1),char('8'-i/4)};
    }
}

Board::~Board()
{
    //dtor
}

void Board::updateMoves()
{
    mValid.clear();
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
		if(isLight(stri))
		{
			char cho = map_Char[stri];
			if(!isDark(stri))
			{
				bool color = islower(cho);
				std::map<Path, std::string>::iterator it;
				for(it=pathTo[stri].begin(); it!=pathTo[stri].end(); it++)
				{
					std::string strj = it->second;
					if(isEmpty(strj))
					{
					    mValid[color].insert(std::pair<std::string, std::string>(stri, strj));
					}
                    if(cho=='c'||cho=='C')
                    {
                        std::string sJump = jumpTo(stri, it->first);
                        if(isLight(sJump)&&momentum(cho, map_Char[sJump]))
                            mValid[color].insert(std::pair<std::string, std::string>(stri, sJump));
                    }
                    else if(isLight(strj))
                    {
                        if(momentum(cho, map_Char[strj]))
                            mValid[color].insert(std::pair<std::string, std::string>(stri, strj));
                    }
				}
			}
		}
    }
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
        map_Char[src] = move[3] ;
		darks.erase(src);
	}
}

std::set<std::pair<std::string, std::string>> Board::getMoveValid(bool color)
{
    std::set<std::pair<std::string, std::string>> result = mValid[color];
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
        if(isDark(stri))
        {
            result.insert(std::pair<std::string, std::string>(stri, stri));
        }
    }
    return result ;
}

std::string Board::jumpTo(std::string src, Path path)
{
    while(this->pathTo[src].count(path)&&isDark(pathTo[src][path]))
        src = this->pathTo[src][path];
    if(this->pathTo[src].count(path))
    {
        src = this->pathTo[src][path];
        while(this->pathTo[src].count(path)&&isDark(pathTo[src][path]))
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
    return darks.count(strp) ;
}

bool Board::isLight(std::string strp)
{
    return map_Char.count(strp) ;
}

bool Board::isEmpty(std::string strp)
{
    return !isDark(strp)&&!isLight(strp); // !map_Char.count(strp)
}
