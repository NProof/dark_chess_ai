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

    protected:

    private:
};

#endif // SCORE_H
