#include "NBoard.h"

NBoard::NBoard()
:Board()
,trun(PROTO_CLR::PCLR_UNKNOW)
,own_l(0), opp_l(0), own_d(16), opp_d(16)
{
	owndk.k = 1;
	owndk.g = 2;
	owndk.m = 2;
	owndk.r = 2;
	owndk.n = 2;
	owndk.c = 2;
	owndk.p = 5;
	
	oppdk.k = 1;
	oppdk.g = 2;
	oppdk.m = 2;
	oppdk.r = 2;
	oppdk.n = 2;
	oppdk.c = 2;
	oppdk.p = 5;
}

int NBoard::indexOfStr(string str)
{
	return ( 'd' - str[0] ) + 4 * ( '8' - str[1] );
}

bool NBoard::isomorphism_number()
{
	cout << "Board::trun : " << Board::trun << endl;
	cout << "Board::n_red : " << Board::n_red << endl;
	cout << "Board::n_black : " << Board::n_black << endl;
	cout << "Board::d_red : " << Board::d_red << endl;
	cout << "Board::d_black : " << Board::d_black << endl;
	cout << "own_l : " << own_l << endl;
	cout << "own_d : " << own_d << endl;
	cout << "opp_l : " << opp_l << endl;
	cout << "opp_d : " << opp_d << endl;
	cout << " --- " << endl;
	
	if(Board::trun == PROTO_CLR::PCLR_UNKNOW)
	{
		assert(own_d == 16);
		assert(opp_d == 16);
	}
	else if(Board::trun != PROTO_CLR::PCLR_RED)
	{
		assert(own_l + own_d == Board::n_red);
		assert(own_d == Board::d_black);
		assert(opp_l + opp_d == Board::n_black);
		assert(opp_d == Board::d_red);
	}
	else if(Board::trun != PROTO_CLR::PCLR_BLACK)
	{
		assert(own_l + own_d == Board::n_black);
		assert(own_d == Board::d_red);
		assert(opp_l + opp_d == Board::n_red);
		assert(opp_d == Board::d_black);
	}
}


bool NBoard::isomorphism_kinds()
{
	if(Board::trun == PROTO_CLR::PCLR_UNKNOW)
	{}
	else
	{
		Kinds ownTestDKinds, oppTestDKinds;
		for(auto typeInt : Board::darkPieces)
		{
			if(islower(typeInt.first) == (trun == PROTO_CLR::PCLR_RED))
			{
				switch(typeInt.first)
				{
				case 'k' : ownTestDKinds.k = typeInt.second; break;
				case 'g' : ownTestDKinds.g = typeInt.second; break;
				case 'm' : ownTestDKinds.m = typeInt.second; break;
				case 'r' : ownTestDKinds.r = typeInt.second; break;
				case 'n' : ownTestDKinds.n = typeInt.second; break;
				case 'c' : ownTestDKinds.c = typeInt.second; break;
				case 'p' : ownTestDKinds.p = typeInt.second; break;
				};
			}
			else
			{
				switch(typeInt.first)
				{
				case 'k' : oppTestDKinds.k = typeInt.second; break;
				case 'g' : oppTestDKinds.g = typeInt.second; break;
				case 'm' : oppTestDKinds.m = typeInt.second; break;
				case 'r' : oppTestDKinds.r = typeInt.second; break;
				case 'n' : oppTestDKinds.n = typeInt.second; break;
				case 'c' : oppTestDKinds.c = typeInt.second; break;
				case 'p' : oppTestDKinds.p = typeInt.second; break;
				};
			}
		}
		assert(owndk.k == ownTestDKinds.k);
		assert(owndk.g == ownTestDKinds.g);
		assert(owndk.m == ownTestDKinds.m);
		assert(owndk.r == ownTestDKinds.r);
		assert(owndk.n == ownTestDKinds.n);
		assert(owndk.c == ownTestDKinds.c);
		assert(owndk.p == ownTestDKinds.p);
		
		assert(oppdk.k == oppTestDKinds.k);
		assert(oppdk.g == oppTestDKinds.g);
		assert(oppdk.m == oppTestDKinds.m);
		assert(oppdk.r == oppTestDKinds.r);
		assert(oppdk.n == oppTestDKinds.n);
		assert(oppdk.c == oppTestDKinds.c);
		assert(oppdk.p == oppTestDKinds.p);
		
		Kinds ownTestKinds, oppTestKinds;
		for(auto chaU : Board::map_Char)
		{
			if(islower(chaU.second) == (trun == PROTO_CLR::PCLR_RED))
			{
				switch(chaU.second)
				{
				case 'k' : ownTestKinds.k++; break;
				case 'g' : ownTestKinds.g++; break;
				case 'm' : ownTestKinds.m++; break;
				case 'r' : ownTestKinds.r++; break;
				case 'n' : ownTestKinds.n++; break;
				case 'c' : ownTestKinds.c++; break;
				case 'p' : ownTestKinds.p++; break;
				};
			}	
			else
			{
				switch(chaU.second)
				{
				case 'k' : oppTestKinds.k++; break;
				case 'g' : oppTestKinds.g++; break;
				case 'm' : oppTestKinds.m++; break;
				case 'r' : oppTestKinds.r++; break;
				case 'n' : oppTestKinds.n++; break;
				case 'c' : oppTestKinds.c++; break;
				case 'p' : oppTestKinds.p++; break;
				};
			}
		}
		assert(ownlk.k == ownTestKinds.k);
		assert(ownlk.g == ownTestKinds.g);
		assert(ownlk.m == ownTestKinds.m);
		assert(ownlk.r == ownTestKinds.r);
		assert(ownlk.n == ownTestKinds.n);
		assert(ownlk.c == ownTestKinds.c);
		assert(ownlk.p == ownTestKinds.p);
		
		assert(opplk.k == oppTestKinds.k);
		assert(opplk.g == oppTestKinds.g);
		assert(opplk.m == oppTestKinds.m);
		assert(opplk.r == oppTestKinds.r);
		assert(opplk.n == oppTestKinds.n);
		assert(opplk.c == oppTestKinds.c);
		assert(opplk.p == oppTestKinds.p);
	}
}

bool NBoard::isomorphism_piece()
{
	unsigned __int32 ownTest = 0x0;
	unsigned __int32 oppTest = 0x0;
	for(auto chaU : Board::map_Char)
	{
		int index = indexOfStr(chaU.first);
		if(islower(chaU.second) == (trun == PROTO_CLR::PCLR_RED))
		{
			ownTest ^= (1<<index);
		}	
		else
		{
			oppTest ^= (1<<index);
		}
	}
	assert(ownTest == ownlp);
	assert(oppTest == opplp);
	
	unsigned __int32 darTest = 0x0;
	for(auto pos : Board::setCheckDark)
	{
		int index = indexOfStr(pos);
		darTest ^= (1<<index);
	}
	assert(darTest == darkp);
}