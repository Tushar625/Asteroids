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