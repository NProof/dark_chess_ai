#include <iostream>

#include "Ai.h"

Ai::Ai()
{

}

void Ai::initBoardState(int piece_count[14], char current_position[32])
{
//    std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>> repair = broad.initBroad(piece_count, current_position);
    broadOfAi = new Broad();
    broadOfAi->initBroad(current_position);
}

bool Ai::generateMove(char *move)
{
    printf("generateMove\n");
    for(int i=0; i<32; i++)
    {
        std::cout << broadOfAi->checks[i].name << " ( " ;
        std::set<Move *> setC = broadOfAi->checks[i].setOfMoves;
        std::map<Path, Move *> mapM = broadOfAi->checks[i].chess->mapOfMoves;
        printf("%2d  %2d ) : ", mapM.size(), setC.size());
        for(std::set<Move *>::iterator it = setC.begin(); it != setC.end(); it++)
        {
            (*it)->generateMove(move);
            printf("%s\t", move);
        }
        for( std::map<Path, Move *>::iterator it = mapM.begin(); it != mapM.end(); it++)
        {
            (it->second)->generateMove(move);
            printf("%s\t", move);
        }
        putchar('\n');
    }
    scanf("%s", move);
    printf("%s[\n", move);
    return true;
}

bool Ai::MakeMove(char *move)
{
    printf("MakeMove\n");
    scanf("%s", move);
    printf("%s[\n", move);
    return true;
}
