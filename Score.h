#ifndef SCORE_H
#define SCORE_H

class Score
{
	public:
		/** Default constructor */
		Score();
		/** Default destructor */
		virtual ~Score();
		/** Copy constructor
		 *  \param other Object to copy from
		 */
		Score(const Score& other);
		/** Assignment operator
		 *  \param other Object to assign from
		 *  \return A reference to this
		 */
		Score& operator=(const Score& other);

		bool operator<(const Score&) const;

		bool maxScore();
		bool minScore();

//    protected:

//    private:
		double rateWin;
		int myWays;
		double rateDraw;
		int opWays;
		double rateLose;
};

#endif // SCORE_H
