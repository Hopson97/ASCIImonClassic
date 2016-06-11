#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

namespace Keyboard
{
    char
    getKey          ();

    char
    waitForKey      ();

    void
    waitForNoKey    ();
}

#endif // KEYBOARD_H_INCLUDED
