#pragma once

class vector_sprite_class : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Vertex> point;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		states.texture = NULL;

		target.draw(&point[0], point.size(), sf::LineStrip, states);
	}

public:

	template<typename... arg_types> requires (std::same_as<sf::Vector2f, arg_types> && ...)

	void set_local_points(const arg_types... args)
	{
		point.resize(sizeof...(args));

		int i = 0;

		((point[i++].position = args), ...);
	}

	const sf::Vector2f& get_local_point(int i) const
	{
		return point[i].position;
	}

	const sf::Vector2f& get_global_point(int i) const
	{
		return getTransform().transformPoint(point[i].position);
	}
};