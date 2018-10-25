#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include "Move.h"

class Move;

class Score
{
	public:
		Score(Move);
		~Score();

		bool operator <(const Score) const;

		int powerOfBoard(Board);

		int Getnumerator() { return numerator; }
		void Setnumerator(int val) { numerator = val; }
		int Getdenominator() { return denominator; }
		void Setdenominator(int val) { denominator = val; }

	protected:

	private:
		int numerator;
		int denominator;
		int powerchessman;
};

#endif // SCORE_H
