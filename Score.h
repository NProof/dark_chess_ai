#ifndef SCORE_H
#define SCORE_H

#include <iostream>
//#include <cfloat>

class Score
{
	public:
		Score();
		Score(int, int, int, int, int);
		~Score();

		bool operator< (const Score) const;
		bool operator> (const Score) const;
		Score operator- () const;
		Score & operator+= (const Score &);
		Score & operator*= (const int);
		Score & operator/= (const int);

		int Getn_Method() const { return n_method; }
		void Setn_Method(int val) { n_method = val; }
		int Getn_Powers() const { return n_powers; }
		void Setn_Powers(int val) { n_powers = val; }
		int Getdenominator() const { return denominator; }
		void Setdenominator(int val) { denominator = (val > 0) ? val : 1 ; }

	    int n_own;
	    int n_opp;

		static const Score minScore;
		static const Score maxScore;

	protected:

	private:
		int n_method;
		int n_powers;
		int denominator;
};

#endif // SCORE_H
