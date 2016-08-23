# ASCIImon
Pokemon in ASCII 

With Pokemon Go coming out, I decided to make a Pokemon-like game (eg the handheld games such as Pokemon Ruby) using C++, as well as using SFML for music and sound effects.

It starts off like a regular pokemon game, talking to a "Pokemon Prof." (But a "Asciimon Prof") and then you just get thrown into a world where you can walk around and encouner Asciimon.

#Screenshots:

####Logo

![Logo](http://i.imgur.com/G3qBfeo.png "Logo")

####The introduction

![introduction](http://i.imgur.com/NJMcx5J.png "introduction")

####Roaming

The different characters represent different "tiles" eg green '.' is grass and grey '{' are buildings.

![Roaming](http://i.imgur.com/VvFosbH.png "Roaming")

###Encounter

![Encounter](http://i.imgur.com/S8Yu7w3.png "Encounter")

####Encounter - Battle Scene

![Encounter](http://i.imgur.com/tgLc8oW.png "Encounter")

####Encounter - Move Selector

![Encounter](http://i.imgur.com/DdesqXO.png "Encounter")


####Defeating the Enemy

![Encounter](http://i.imgur.com/S8Yu7w3.png "Encounter")


More images in the album: http://imgur.com/gallery/wwb6F

#Design
The game uses a pretty standard game-state pattern, where the state of the program can change. Eg, it switches from menu state to intro state to roaming state to wild battle state, pops back to roaming state etc

    void Game_Main :: runLoop ()
	{
	   Clock m_clock;
	   double timeFrame = 0.2; //Fixed time between updates, inputs and draws

	    while ( m_isRunning )
	    {
	        m_states.peekState()->input ();
	
	        m_states.peekState()->update();
	
	
	        if ( m_isRedrawNeeded )
	        {
	            Console::clear();
	            m_states.peekState()->draw ();
	            m_isRedrawNeeded = false;
	        }
	
	        while ( m_clock.getCurrentTime() < timeFrame );
	        m_clock.restart();
	    }
	}
	
As can be seen, it only draws the current state when a draw is needed, this is because the console isn't very fast at printing things onto it, and thus without the time check the whole games would just be a strobe.

ASCIImon data, such as base stats and moves, is stored in a "cache", where the ASCIImon is loaded just once and then the data is taken from the cache if that ASCIImon is ever encountered again. Each actual ASCIImon, eg the ones seen in battle, hold a poiter to this data, in a sort of a "flyweight" pattern way. Albiet, it was my first time doing something like that, and thus the implementation is not the greatest.
