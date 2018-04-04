#include <iostream>

#include "Ai.h"

Ai::Ai()
{

}

/* void Ai::initBoardState(int piece_count[14], char current_position[32])
{
//    std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>> repair = broad.initBroad(piece_count, current_position);
    broadOfAi = new Broad();
//    broadOfAi->initBroad(piece_count, current_position);
} */

bool Ai::generateMove(char *move)
{
    printf("generateMove\n");
    updateMoves();
    std::cout << belongs.size() << ",  " << movesNext.size();
    for(std::set<Move *>::iterator it=movesNext.begin(); it!=movesNext.end(); it++)
    {
        (*it)->generateMove(move);
        printf("%s\t", move);
    }
    for(std::set<Chess *>::iterator it=broadOfAi->setDark.begin(); it!=broadOfAi->setDark.end(); it++)
    {
//        printf("%s\t", (*it)->check->name);
        std::cout << ", " << (*it)->check->name;
    }
    putchar('\n');
    for( std::map<char, int>::iterator it=broadOfAi->chDark.begin(); it!=broadOfAi->chDark.end(); it++)
    {
        std::cout << it->first << it->second << "," ;
    }
    scanf("%s", move);
    printf("%s[\n", move);
    return true;
}

bool Ai::MakeMove(char *move)
{
    printf("MakeMove ..");
    if(broadOfAi->mapOfName[std::string{move[0],move[1]}]->chess->dark)
    {
//        std::cout << broadOfAi << " . ";
        broadOfAi->mapOfName[std::string{move[0],move[1]}]->chess->init(move[3]);
        broadOfAi->setDark.erase(broadOfAi->mapOfName[std::string{move[0],move[1]}]->chess);
        broadOfAi->chDark[move[3]]--;
        this->belongs.insert(broadOfAi->mapOfName[std::string{move[0],move[1]}]->chess);
        return printf("that \n");
    }
    else
    {
        for(std::set<Move *>::iterator it= movesNext.begin(); it!=movesNext.end(); it++)
        {
//            (*it)->chess;
//            (*it)->path;
//            (*it)->check;
            if((*it)->chess->check->name.compare(std::string{move[0],move[1]})
               &&(*it)->check->name.compare(std::string{move[2],move[3]}))
            {
                (*it)->makeMove(move);
                return printf("\n");
            }
        }
    }
//    printf("\n");
    return true;
}

void Ai::updateMoves()
{
    movesNext.clear();
    for(std::set<Chess *>::iterator cit= belongs.begin(); cit!=belongs.end(); cit++)
    {
        Chess * temp = *cit;
        Check * checki = (*cit)->check;
        for(std::map<Path, Check *>::iterator it=checki->pathsTo.begin(); it !=checki->pathsTo.end(); it++)
        {
            if(!it->second->chess)
                movesNext.insert(new Move(temp, it->second));
            if(it->second->chess&&(temp)->type!=Type::Cannon)
            {
                Chess chessi = *it->second->chess;
                if(!chessi.dark&&(temp->color^chessi.color)&&(*cit)->atcCan(chessi.type))
                    movesNext.insert(new Move(temp, it->second));
            }
            if(temp->type==Type::Cannon&&temp->check->jumpTo(it->first))
            {
                Check * checki = temp->check->jumpTo(it->first);
                Chess chessj = *checki->chess;
                if(!chessj.dark&&temp->color^chessj.color)
                    movesNext.insert(new Move(temp, checki));
            }
        }
    }
}
