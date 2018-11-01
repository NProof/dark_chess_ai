#include "Player.h"

Player::Player()
{
    this->board = new Board();
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
    std::map<Score, std::vector<Board::Move> > mapRank;
    for(Board::Move * ptrMove : next(*board))
        mapRank[score(ptrMove)].push_back(*ptrMove);
    std::vector<Board::Move> moves = mapRank.begin()->second;
    strcpy(move, (moves.empty()) ? "NAN" : moves[rand()%moves.size()].getStringMove().c_str());
//    printf("%s\n", moves.begin()->getStringMove().c_str());
}

void Player::makeMove(char *move)
{
    this->board->makeMove(std::string(move));
}

bool Player::getColor()
{
    return color;
}

std::set<Board::Move *> Player::next(Board board)
{
    if(B2MS.find(board)==B2MS.end())
    {
        std::set<Board::Move *> temp;
        std::set<std::pair<std::string, std::string>> mValid = board.getMoveValid();
        std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
        for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
        {
            temp.insert(new Board::Move(board, pairmoveIt->first+'-'+pairmoveIt->second));
        }
        std::map<char, int> mapChessesDark = board.getDarkPieces();
        std::map<char, int>::iterator mapChessesDarkIt;
        int all = 0;
        for(mapChessesDarkIt=mapChessesDark.begin(); mapChessesDarkIt!=mapChessesDark.end(); mapChessesDarkIt++)
        {
            all += mapChessesDarkIt->second;
        }
        std::set<std::string> setCheckDark = board.getSetCheckDark();
        std::set<std::string>::iterator setCheckDarkIt;
        for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
        {
            temp.insert(new Board::Move(board, *setCheckDarkIt, all, mapChessesDark));
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

Score Player::score(Board * board)
{
    Score bestScore = Score::minScore;
    for(auto mov : next(*board))
    {
        Score temp = score(mov);
        if(temp > bestScore)
            bestScore = temp;
    }
    return bestScore;
}

//Score Player::score(Board::Move * mov)
//{
//	std::map<Board, int> nextBoards = next(*mov);
//	std::map<Board, int>::iterator it = nextBoards.begin();
////	Score mean = score(it->first);
//	for(; it != nextBoards.end(); it++)
//    {
////        score(&(it->first)) * it->second;
//    }
////    return Score(n_method, n_powers, mov->GetiDark());
//    return ;
//}

Score Player::score(Board::Move * mov)
{
	int n_method = 0;
	int n_powers = 0;
	for(auto it : next(*mov))
    {
        Board temp = it.first;
//        Score score(Score::method(temp), Score::powers(temp), 1);
//        score * 3;
        n_method += Score::method(temp)*it.second;
        n_powers += Score::powers(temp)*it.second;
    }
    return Score(n_method, n_powers, mov->GetiDark());
}
