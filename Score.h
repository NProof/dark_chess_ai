#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <cfloat>

class Score
{
	public:
		Score(double, double, double);
		Score(int, int, int);
		~Score();

		bool operator <(const Score) const;
		bool operator >(const Score) const;
		void operator +=(const Score);
		Score operator *(int) const;
		Score operator /(int) const;

		int GetWin() const { return win; }
		void SetWin(int val) { win = val; }
		int GetDraw() const { return draw; }
		void SetDraw(int val) { draw = val; }
		int GetLose() const { return lose; }
		void SetLose(int val) { lose = val; }
		int Getn_Method() const { return n_method; }
		void Setn_Method(int val) { n_method = val; }
		int Getn_Powers() const { return n_powers; }
		void Setn_Powers(int val) { n_powers = val; }
		int Getdenominator() const { return denominator; }
		void Setdenominator(int val) { denominator = (val > 0) ? val : 1 ; }

        static const Score minScore;

	protected:

	private:
	    double win;
	    double draw;
	    double lose;
		int n_method;
		int n_powers;
		int denominator;
};

#endif // SCORE_H
