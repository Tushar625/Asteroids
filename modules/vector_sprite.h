#pragma once


/*
	the asteroids, spaceship and bullets are created using this class

	they are created by connecting some points with lines, vector graphics
*/

class vector_sprite_class : public sf::Drawable, public sf::Transformable
{
	std::vector<sf::Vertex> point;

	float size, half_size;	// size of the square representing the object

	
	// we don't want user to change the size of the object once the shape is defined
	
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


	/*
		variadic function, takes the size (height == width) of the bounding square, and coordinates
		of the points representing the shape

		sets the origin of the sprite at the center of the bounding square according to the size and
		the scale of the sprite to 1

		this is helpful as the objects are rotated around their center

		remember that, the last and first point must have same coordinates, to make it a closed shape
	*/

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


	// no. of points in the shape, remember that last and first points have same coordinates

	size_t get_point_count() const
	{
		return point.size();
	}


	// coordinates of the points inside the bounding square

	const sf::Vector2f& get_local_point(int i) const
	{
		return point[i].position;
	}


	// actual coordinates of the points

	const sf::Vector2f& get_global_point(int i) const
	{
		return getTransform().transformPoint(point[i].position);
	}


	// size of the bounding square of the shape

	float get_size() const
	{
		return size;
	}


	// size / 2 of the bounding square of the shape

	float get_half_size() const
	{
		return half_size;
	}


	/*
		this type of classes usually have setScale() and getScale() functions but
		here I define my own set_scale() and get_scale() functions

		reason:

		* we are dealing with squares so no need to set x and y scale seperately

		* set_scale() takes care of the size of the bounding square, proper size
		  info is essential for edge wrapping and collision detection
	*/

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


	/*
		these classes also have move function, that lets you move the objects by a certain offset

		edge wrapping
		-------------
		in this game I want the objects to appear in the opposite edge when it crosses an edge.
		
		to achive this I created this move_wrap() function that not only moves the objects like move()
		but also creates the edge wrapping effect

		so to move objects of this class I am using move_wrap() as an alternative of move()
	*/

	void move_wrap(const sf::Vector2f& offset)
	{
		move(sf::Vector2f(offset.x, offset.y));

		// wraping at the edges

		auto pos = getPosition();

		// half_size is used here as the origin is at the center

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