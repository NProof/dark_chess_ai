#include "Player.h"

Player::Player(int [14], char current_position[32], History&, int&)
{
    this->board = new Board(current_position);
}

Player::~Player()
{
    //dtor
}

void Player::setColor(PROTO_CLR color)
{
    this->color = color == PROTO_CLR::PCLR_BLACK; // =islower()
}

void Player::generateMove(char *move)
{
    mValid.clear();
    std::map<std::string, char> map_Char = this->board->getMapChar();
    std::map<std::string, std::map<Path, std::string>> pathTo = this->board->getPathTo();
    for(int i=0; i<32; i++)
    {
        std::string pos = std::string{char('a'+i%4),char('8'-i/4)};
        char cho = map_Char[pos];
        if(cho=='X')
        {
            mValid.insert(std::pair<std::string, std::string>(pos, pos));
        }
        else if(cho!='-'&&(bool)islower(cho)==this->color)
        {
            std::map<Path, std::string>::iterator it;
            for(it=pathTo[pos].begin(); it!=pathTo[pos].end(); it++)
            {
                char vch = map_Char[it->second];
                if(vch=='-')
                {
                    mValid.insert(std::pair<std::string, std::string>(pos, it->second));
                }
                if(cho=='c'||cho=='C')
                {
                    std::string sJump = board->jumpTo(pos, it->first);
                    if(sJump!="outer"&&board->momentum(cho, map_Char[sJump]))
                        mValid.insert(std::pair<std::string, std::string>(pos, sJump));
                }
                else if(vch!='-')
                {
                    if(board->momentum(cho, vch))
                        mValid.insert(std::pair<std::string, std::string>(pos, it->second));
                }
            }
        }
    }
    std::set<std::pair<std::string, std::string>>::iterator pairmove;
    pairmove = mValid.begin();
    int times = rand()%mValid.size();
    for(int i=0; i<times; i++) pairmove++;
    strcpy(move, pairmove->first.c_str());
    move[2] = '-';
    strcpy(move+3, pairmove->second.c_str());
}

void Player::makeMove(char *move)
{
    this->board->makeMove(move);
}
