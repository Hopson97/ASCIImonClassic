#ifndef ENCOUNTERABLE_ASCIIMON_H
#define ENCOUNTERABLE_ASCIIMON_H

class Encounterable_ASCIImon
{
    public:
        Encounterable_ASCIImon ( const unsigned id, const unsigned weight,
                                 const unsigned lowerLvlBound, const unsigned upperLvlBound );

        unsigned getId       () const;
        unsigned getWeight   () const;
        unsigned getLowLevel () const;
        unsigned getHighLevel() const;

    private:
        const unsigned m_id;
        const unsigned m_weight; //Weight refers to how often it can be encountered (ie higher weight of rng)
                            //Higher weight = higher chance of being encountered
        const unsigned m_lowerLevelRange;
        const unsigned m_upperLevelRange;

};

#endif // ENCOUNTERABLE_ASCIIMON_H
