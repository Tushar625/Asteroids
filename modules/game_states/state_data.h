#pragma once



// to hold general game data that will be used by every state

struct game_data_type
{
	int highest_score;

	int score;

	int health;

	// data of this structure is stored in AppData\Local\Astroids_data.bin

	game_data_type() : highest_score(0), score(0), health(MAX_HEALTH)
	{
		//bb::load_local_appdata("Astroids_data.bin", *this);
	}

	~game_data_type()
	{
		//bb::store_local_appdata("Astroids_data.bin", *this);
	}

	// after game is over this functon is used to reset the general game data

	void reset()
	{
		health = MAX_HEALTH;

		if (score > highest_score)
		{
			// new highest score

			/*sf::Sound sound;

			sound.setBuffer(sound_buffer[HIGH_SCORE]);

			sound.play();*/

			highest_score = score;
		}

		score = 0;
	}
};