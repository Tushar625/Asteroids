#pragma once



/*
	print the hearts at certain position

	center of left heart touches { 15, 21 }, this position is chosen to match with
	the score texts
*/

inline void render_health(int health)
{
	auto heart_size = heart_sprite.get_size();

	int x = 15;

	// now printing the hearts

	for (int i = health; i > 0; i--)
	{
		heart_sprite.setPosition(sf::Vector2f(x, 21));

		bb::WINDOW.draw(heart_sprite);

		x += heart_size + heart_size / 2;	// gap between hearts is "heart_size / 2"
	}
}



// top right end of score text touches { VIRTUAL_WIDTH - 10, 10 }

inline void render_score(int score)
{
	medium_text.setString(std::to_string(score));

	medium_text.setPosition(sf::Vector2f(VIRTUAL_WIDTH - 10 - medium_text.getLocalBounds().width, 10));

	bb::WINDOW.draw(medium_text);
}