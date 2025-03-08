#pragma once


/*
	print the hearts at certain position
*/

inline void render_health(int health)
{
	auto heart_width = heart_sprite.get_size();

	// center of heart is at VIRTUAL_WIDTH / 2.0 and it's placed 2 pixels below the top

	int x = VIRTUAL_WIDTH - 10 - health * (heart_width + heart_width / 2) + heart_width / 2;

	// printing empty hearts

	// now printing the hearts

	for (int i = health; i > 0; i--)
	{
		heart_sprite.setPosition(sf::Vector2f(x, 45));

		bb::WINDOW.draw(heart_sprite);

		x += heart_width + heart_width / 2;
	}
}

inline void render_score(int score)
{
	medium_text.setString(std::to_string(score));

	medium_text.setPosition(sf::Vector2f(VIRTUAL_WIDTH - 12 - medium_text.getLocalBounds().width, 10));

	bb::WINDOW.draw(medium_text);
}

inline void render_fps()
{
	medium_text.setString(std::to_string(static_cast<int>(bb::MY_GAME.get_fps() + .5)));

	medium_text.setPosition(10, 10);

	bb::WINDOW.draw(medium_text);
}

// put the origin of a text in the center

sf::Vector2f round(const sf::Vector2f vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

void center_origin(sf::Text& text)
{
	auto center = text.getGlobalBounds().getSize() / 2.f;
	auto localBounds = center + text.getLocalBounds().getPosition();
	auto rounded = round(localBounds);
	text.setOrigin(rounded);
}