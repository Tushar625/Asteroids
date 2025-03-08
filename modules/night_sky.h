#pragma once

class night_sky_class : public sf::Drawable
{
	std::vector<sf::Vertex> point;

	std::vector<uint8_t> velocity;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = NULL;

		target.draw(&point[0], point.size(), sf::Points, states);
	}

public:

	night_sky_class() : point(STAR_COUNT), velocity(STAR_COUNT)
	{
		for(int i = 0; i < STAR_COUNT; i++)
		{
			point[i].position = sf::Vector2f(rand() % VIRTUAL_WIDTH, rand() % VIRTUAL_HEIGHT);

			velocity[i] = rand() % (STAR_MAX_VELOCITY - STAR_MIN_VELOCITY + 1) + STAR_MIN_VELOCITY;
		}
	}

	void update(double dt)
	{
		for (int i = 0; i < STAR_COUNT; i++)
		{
			point[i].position.y += velocity[i] * dt;

			if (point[i].position.y > VIRTUAL_HEIGHT)
			{
				point[i].position.y = 0;
			}
		}
	}
};