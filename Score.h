#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include "Board.h"

class Score
{
	public:
		Score(int, int, int);
		~Score();

		bool operator <(const Score) const;

		static int powers(Board);
		static int method(Board);

		int Getn_Method() { return n_method; }
		void Setn_Method(int val) { n_method = val; }
		int Getn_Powers() { return n_powers; }
		void Setn_Powers(int val) { n_powers = val; }
		int Getdenominator() { return denominator; }
		void Setdenominator(int val) { denominator = (val > 0) ? val : 1 ; }

	protected:

	private:
		int n_method;
		int n_powers;
		int denominator;
};

#endif // SCORE_H
