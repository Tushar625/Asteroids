#pragma once

class vector_sprite_class : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Vertex> point;

	float size, half_size;

	void set_size(float sz)
	{
		size = sz;

		half_size = sz / 2;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();

		states.texture = NULL;

		target.draw(&point[0], point.size(), sf::LineStrip, states);
	}

public:

	// sets the origin at the center according to the size

	template<typename... arg_types> requires (std::same_as<sf::Vector2f, arg_types> && ...)

	void set_local_size_and_points(float sz, const arg_types&... args)
	{
		point.resize(sizeof...(args));

		int i = 0;

		((point[i++].position = args), ...);

		setOrigin(sf::Vector2f(sz / 2, sz / 2));

		set_size(sz);

		setScale(1, 1);
	}

	const sf::Vector2f& get_local_point(int i) const
	{
		return point[i].position;
	}

	const sf::Vector2f& get_global_point(int i) const
	{
		return getTransform().transformPoint(point[i].position);
	}

	size_t get_point_count() const
	{
		return point.size();
	}

	float get_size() const
	{
		return size;
	}

	float get_half_size() const
	{
		return half_size;
	}

	void set_scale(float scl)
	{
		// update actual size

		set_size(size / getScale().x * scl);
		
		setScale(sf::Vector2f(scl, scl));
	}

	float get_scale() const
	{
		return getScale().x;
	}

	void move_wrap(const sf::Vector2f& offset)
	{
		move(sf::Vector2f(offset.x, offset.y));

		// wraping at the edges

		auto pos = getPosition();

		// left and right edges

		if (pos.x < -half_size)
		{
			pos.x = VIRTUAL_WIDTH + half_size;
		}
		else if (pos.x > VIRTUAL_WIDTH + half_size)
		{
			pos.x = -half_size;
		}

		// top and bottom edges

		if (pos.y < -half_size)
		{
			pos.y = VIRTUAL_HEIGHT + half_size;
		}
		else if (pos.y > VIRTUAL_HEIGHT + half_size)
		{
			pos.y = -half_size;
		}

		if (pos != getPosition())
		{
			setPosition(pos);
		}
	}
};