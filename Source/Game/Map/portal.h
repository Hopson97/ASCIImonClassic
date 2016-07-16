#ifndef PORTAL_H
#define PORTAL_H

#include "../Maths/vector2.h"

class Portal
{
    public:
        Portal          ( const Vector2i& location );

        void setUp      ( const Vector2i& goesTo, const Vector2i& playerStands );

        const Vector2i& getGoesTo       () const;

        const Vector2i& getPlayerStands () const;

        const Vector2i& getLocation     () const;

    private:
        Vector2i m_goesTo;
        Vector2i m_playerStands;
        Vector2i m_location;
};

#endif // PORTAL_H
