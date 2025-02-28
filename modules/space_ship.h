#pragma once

class space_ship_class : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Vertex> point;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		states.texture = NULL;

		target.draw(&point[0], 5, sf::LineStrip, states);
	}

	public:

	space_ship_class() : point{ 5 }
	{
		point[0].position = point[4].position = { 20, 10 };

		point[1].position = { 0, 0 };

		point[2].position = { 5, 10 };

		point[3].position = { 0, 20 };
	}
} space_ship;