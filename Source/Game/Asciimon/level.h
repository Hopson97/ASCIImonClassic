#ifndef LEVEL_H
#define LEVEL_H


class Level
{
    public:
        void giveExp    ( unsigned exp );

        void checkForLevelUp();
        bool canLevelUp     ();

        unsigned getLevel           () const;
        unsigned getCurrentExp      () const;
        unsigned getExpForNextLevel () const;
        unsigned getTotalExp        () const;

        void setLevel   ( unsigned level );

        void levelUp        ();

    private:
        unsigned  getExpOverflow ();

        unsigned m_level = 1;

        unsigned m_currentExp = 0;
        unsigned m_expForNextLevel = 20;
        unsigned m_totalExp = 0;

        double expIncrease = 1.1;

};

#endif // LEVEL_H
