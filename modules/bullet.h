#pragma once



class bullet_class
{
	vector_sprite_class sprite;

	sf::Vector2f velocity;

	float life_time;

	public:

	bullet_class() : life_time(-1)
	{
		sprite.set_local_size_and_points(
			BULLET_SIZE,
			sf::Vector2f(BULLET_HALF_SIZE, 0),
			sf::Vector2f(BULLET_SIZE, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, BULLET_SIZE),
			sf::Vector2f(0, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, 0)
		);
	}

	void update(double dt)
	{
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			// calculating speed

			float angle = space_ship.sprite.getRotation() * std::numbers::pi_v<float> / 180;	// 0 -> 359 degrees but in radians

			velocity.x = cos(angle) * BULLET_VELOCITY;

			velocity.y = sin(angle) * BULLET_VELOCITY;

			// set rotation and position

			sprite.setRotation(space_ship.sprite.getRotation());

			sprite.setPosition(space_ship.sprite.getPosition());

			// setting life time

			life_time = BULLET_LIFE_TIME;
		}

		if (life_time > 0)
		{
			sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));
		}

		life_time -= dt;
	}

	void render()
	{
		if (life_time > 0)
		{
			bb::WINDOW.draw(sprite);
		}
	}
} bullet;