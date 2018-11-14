#include "Player.h"

Player::Player()
{
    this->board = Board();
}

Player::~Player()
{
    //dtor
}

void Player::setColor(PROTO_CLR color)
{
    this->color = color ; // =islower()
}

void Player::generateMove(char *move)
{
    std::cout << board.nD_red << " and Black : " << board.nD_black << std::endl;
    if(board.nD_red+board.nD_black>0)
    {
        std::vector<Board::Move> moves = one_level();
        strcpy(move, (moves.empty()) ? "NAN" : moves[rand()%moves.size()].getStringMove().c_str());
    }
    else
    {

    }
//    printf("%s\n", moves.begin()->getStringMove().c_str());
}

void Player::makeMove(char *move)
{
    this->board.makeMove(std::string(move));
}

bool Player::getColor()
{
    return color;
}

std::vector<Board::Move> Player::one_level()
{
    std::map<Score, std::vector<Board::Move> > mapRank;
    for(Board::Move ptrMove : next(board)){
        mapRank[score(ptrMove, 0)].push_back(ptrMove);
    }
    return mapRank.begin()->second;
}

std::set<Board::Move> Player::next(Board board)
{
    if(B2MS.find(board)==B2MS.end())
    {
        std::set<Board::Move> temp;
        std::set<std::pair<std::string, std::string>> mValid = board.getMoveValid();
        for(auto pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end(); pairmoveIt++)
        {
            temp.insert(Board::Move(board, pairmoveIt->first+'-'+pairmoveIt->second));
        }
        std::map<char, int> mapChessesDark = board.getDarkPieces();
        std::set<std::string> setCheckDark = board.getSetCheckDark();
        for(auto setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
        {
            temp.insert(Board::Move(board, *setCheckDarkIt, setCheckDark.size(), mapChessesDark));
        }
        B2MS[board] = temp;
        return temp;
    }
    return B2MS[board];
}

std::map<Board, int> Player::next(Board::Move mov)
{
    if(M2BM.find(mov) == M2BM.end())
    {
        M2BM[mov] = mov.GetpossibleBoards();
    }
    return M2BM[mov];
}

Score Player::score(Board board, int level)
{
    if(level){
        Score bestScore = Score::minScore;
        for(auto mov : next(board))
        {
            Score temp = -score(mov, level-1);
            if(temp > bestScore)
                bestScore = temp;
        }
        return bestScore;
    }
    else{
        return *board.getScore();
    }
}

Score Player::score(Board::Move mov, int level)
{
	std::map<Board, int> nextMov = next(mov);
	std::map<Board, int>::iterator it = nextMov.begin();
	Score mean = (score(it->first, level) *= it->second);
	for(; it != nextMov.end(); it++)
    {
        mean += (score(it->first, level) *= it->second);
    }
    return mean /= mov.GetiDark();
}
