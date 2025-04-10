#pragma once



/*
    This struct holds general game data that will be used by every game state.
    It provides functionality to persist data across game sessions and reset data after a game session ends.
*/

struct game_data_type
{
	int highest_score; // The highest score achieved across all game sessions.

    int score;         // The current score for the ongoing game session.
	
    int health;        // The player's current health during ongoing game session.

    /*
        The data of this structure is stored in AppData\Local\Astroids_data.bin
        and is automatically loaded and saved using the bb::load_local_appdata
        and bb::store_local_appdata functions.
    */

    /*
        Constructor: Initializes the game data with default values and loads
        persisted data from the file "Astroids_data.bin".
    */
    
    game_data_type() : highest_score(0), score(0), health(MAX_HEALTH)
    {
        /*
            Load saved game data from the local application data directory.
            If the file does not exist or is corrupted, default values are used.
        */
        
        bb::load_local_appdata("Astroids_data.bin", *this);
    }

    /*
        Destructor: Saves the current game data to the file "Astroids_data.bin"
        when the object is destroyed (e.g., when the game exits).
    */
    
    ~game_data_type()
    {
        // Store the current game data in the local application data directory.
        
        bb::store_local_appdata("Astroids_data.bin", *this);
    }

    /*
        Resets the game data after a game session ends.
        - Resets health to the maximum value (MAX_HEALTH).
        - Updates the highest score if the current score exceeds it.
        - Resets the current score to 0.
    */

	void reset()
	{
		health = MAX_HEALTH;

		if (score > highest_score)
		{
            // Update the highest score if the current score is greater.

			highest_score = score;
		}

		score = 0;
	}
};