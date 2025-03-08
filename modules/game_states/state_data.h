#pragma once



// creating the string buttons

class str_button : public bb::BUTTON
{
	sf::Text button_text;

	void ORDINARY_STATE() override
	{
		button_text.setPosition(sf::Vector2f(get_x(), get_y()));

		/*
			by default ordinary button color is white, "button_color"
			is kept to chenge it if needed, here it is used primarily
			by the menu list pointer to indicate which button is selected
		*/

		button_text.setFillColor(button_color);

		bb::WINDOW.draw(button_text);

		button_color = sf::Color::White;
	}

	void HOVERING_STATE() override
	{
		button_text.setPosition(sf::Vector2f(get_x(), get_y()));

		button_text.setFillColor(sf::Color::Cyan);

		bb::WINDOW.draw(button_text);
	}

public:

	sf::Color button_color;

	str_button(int xin, int yin, std::string button_str, bb::COORD_POSITION pos = bb::TOP_LEFT)
	{
		button_text = medium_text;	// button text will have same eproperties as medium text

		button_text.setString(button_str);

		set_height(MEDIUM_FONT_SIZE);

		set_width(button_text.getLocalBounds().width);

		set_pos(xin, yin, pos);

		button_color = sf::Color::White;	// default ordinary state color is white
	}
};



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