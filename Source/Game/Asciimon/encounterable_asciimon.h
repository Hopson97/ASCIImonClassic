#ifndef ENCOUNTERABLE_ASCIIMON_H
#define ENCOUNTERABLE_ASCIIMON_H

class Encounterable_ASCIImon
{
    public:
        Encounterable_ASCIImon ( const int id, const int weight );

        int getId       () const;

        int getWeight   () const;

    private:
        const int m_id;
        const int m_weight; //Weight refers to how often it can be encountered (ie higher weight of rng)
                            //Higher weight = higher chance of being encountered
};

#endif // ENCOUNTERABLE_ASCIIMON_H
