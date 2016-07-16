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

    private:
        void levelUp        ();
        unsigned  getExpOverflow ();

    private:
        unsigned m_level = 1;

        unsigned m_currentExp = 0;
        unsigned m_expForNextLevel = 20;
        unsigned m_totalExp = 0;

        double expIncrease = 1.05;

};

#endif // LEVEL_H
