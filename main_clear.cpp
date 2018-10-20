#include <cstdio>
#include <cstdlib>
#include "Protocol.h"
#include "Player.h"

int main(int argc , char **argv)
{
	Protocol protocol;
	switch(argc){
	case 3:
		if(!protocol.init_protocol(argv[1], atoi(argv[2]))) return 0;
		break;
    case 2:
		if(!protocol.init_protocol(argv[0], atoi(argv[1]))) return 0;
		break;
	}

	char current_position[32], move[6];
	int  piece_count[14];
	PROTO_CLR color;
	History history;
	bool turn;
	int time;
	std::cout<<argc<<std::endl;
	std::cout<<argv[0]<<std::endl;

	if(argc==3||argc==2)
	{
		protocol.init_board(piece_count, current_position, history,time);
        Player player;

		if(history.number_of_moves != 0)
		{
			puts("-----------Record-----------");
			for(int i=0;i<history.number_of_moves;i++)
			{
				printf("%d:%s\n",i,history.move[i]);
			}
		}

		protocol.get_turn(turn, color);
        player.setColor(color);


		if(turn)
		{
			player.generateMove(move);
			protocol.send(move);
			protocol.recv(move,time);
			if( color == PCLR_UNKNOW )
			{
				color = protocol.get_color(move);
				player.setColor(color);
			}
			player.makeMove(move);
			protocol.recv(move,time);
			player.makeMove(move);
		}
		else
		{
			protocol.recv(move,time);
			if( color == PCLR_UNKNOW )
			{
				color = (protocol.get_color(move)==PCLR_BLACK)? PCLR_RED : PCLR_BLACK;
				player.setColor(color);
			}
			player.makeMove(move);
		}

		while(1)
		{
			player.generateMove(move);
			protocol.send(move);
			protocol.recv(move,time);
			player.makeMove(move);
			protocol.recv(move,time);
			player.makeMove(move);
		}
	}
	return 0;
} // end main(int argc , char **argv)

