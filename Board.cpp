#include "Board.h"

Board::Board()
{
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
        map_Char[stri] = 'X';

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
        char cho = map_Char[stri];
        if(cho!='X'&&cho!='-')
        {
            std::map<Path, std::string>::iterator it;
            for(it=pathTo[stri].begin(); it!=pathTo[stri].end(); it++)
            {
                char vch = map_Char[it->second];
                if(vch=='-')
                {
                    mValid[(bool)islower(cho)].insert(std::pair<std::string, std::string>(stri, it->second));
                }
                if(cho=='c'||cho=='C')
                {
                    std::string sJump = jumpTo(stri, it->first);
                    if(sJump!="outer"&&momentum(cho, map_Char[sJump]))
                        mValid[(bool)islower(cho)].insert(std::pair<std::string, std::string>(stri, sJump));
                }
                else if(vch!='-')
                {
                    if(momentum(cho, vch))
                        mValid[(bool)islower(cho)].insert(std::pair<std::string, std::string>(stri, it->second));
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
        map_Char[src] = '-';
    }
    else
        map_Char[src] = move[3] ;
}

std::set<std::pair<std::string, std::string>> Board::getMoveValid(bool color)
{
    std::set<std::pair<std::string, std::string>> result = mValid[color];
    for(int i=0; i<32; i++)
    {
        std::string stri = std::string{char('a'+i%4),char('8'-i/4)};
        if(map_Char[stri]=='X')
        {
            result.insert(std::pair<std::string, std::string>(stri, stri));
        }
    }
    return result ;
}

std::string Board::jumpTo(std::string src, Path path)
{
    while(this->pathTo[src].count(path)&&this->map_Char[this->pathTo[src][path]]=='-')
        src = this->pathTo[src][path];
    if(this->pathTo[src].count(path))
    {
        src = this->pathTo[src][path];
        while(this->pathTo[src].count(path)&&this->map_Char[this->pathTo[src][path]]=='-')
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
	return (hig=='X'||low=='X'||islower(hig)==islower(low))
        ? false : low=='-'||hig=='c'||hig=='C'||
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
