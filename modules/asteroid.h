#pragma once

#define ASTEROID_MIN_VELOCITY 50
#define ASTEROID_MAX_VELOCITY 100
#define ASTEROID_ROTATION_SPEED 20.0f
#define ASTEROID_SIZE 20

class asteroid_class
{
	vector_sprite_class sprite;

	sf::Vector2f velocity;

	public:

	asteroid_class()
	{
		// setting type of asteroid

		type1();
		
		// setting random location

		sprite.setPosition(sf::Vector2f(rand() % VIRTUAL_WIDTH, rand() % VIRTUAL_HEIGHT));

		// setting random velocity

		int velo = rand() % (ASTEROID_MAX_VELOCITY - ASTEROID_MIN_VELOCITY + 1) + ASTEROID_MIN_VELOCITY;

		float angle = (rand() % 360) * std::numbers::pi_v<float> / 180;	// 0 -> 359 degrees but in radians

		velocity.x = cos(angle) * velo;
		
		velocity.y = sin(angle) * velo;

		// setting random scale

		sprite.set_scale((rand() % 2001 + 1000) / 1000.0f);
	}

	void update(double dt)
	{
		// updating position of asteroid according to it's velocity

		sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));

		sprite.rotate(ASTEROID_ROTATION_SPEED * dt);
	}

	void render()
	{
		bb::WINDOW.draw(sprite);
	}

	private:

	void type1()
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(2, 0),
			sf::Vector2f(8, 2),
			sf::Vector2f(13, 0),
			sf::Vector2f(11, 7),
			sf::Vector2f(20, 3),

			sf::Vector2f(17, 11),
			sf::Vector2f(20, 11),
			sf::Vector2f(16, 17),
			sf::Vector2f(17, 18),
			sf::Vector2f(10, 20),

			sf::Vector2f(6, 17),
			sf::Vector2f(0, 20),
			sf::Vector2f(2, 12),
			sf::Vector2f(0, 8),
			sf::Vector2f(3, 5),
			sf::Vector2f(2, 0)
		);
	}

	void type2()
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(5, 0),
			sf::Vector2f(10, 3),
			sf::Vector2f(15, 0),
			sf::Vector2f(20, 8),
			sf::Vector2f(17, 13),

			sf::Vector2f(20, 15),
			sf::Vector2f(15, 15),
			sf::Vector2f(15, 20),
			sf::Vector2f(10, 20),
			sf::Vector2f(5, 15),

			sf::Vector2f(0, 15),
			sf::Vector2f(5, 10),
			sf::Vector2f(0, 10),
			sf::Vector2f(5, 0)
		);
	}

	void type3()
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(0, 0),
			sf::Vector2f(5, 2),
			sf::Vector2f(12, 1),
			sf::Vector2f(17, 3),
			sf::Vector2f(15, 5),

			sf::Vector2f(20, 5),
			sf::Vector2f(15, 15),
			sf::Vector2f(20, 10),
			sf::Vector2f(18, 20),
			sf::Vector2f(10, 17),

			sf::Vector2f(2, 20),
			sf::Vector2f(3, 15),
			sf::Vector2f(0, 10),
			sf::Vector2f(3, 5),

			sf::Vector2f(0, 0)
		);
	}

	void type4()
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(3, 3),
			sf::Vector2f(10, 0),
			sf::Vector2f(17, 5),
			sf::Vector2f(20, 3),
			sf::Vector2f(19, 8),

			sf::Vector2f(20, 12),
			sf::Vector2f(15, 14),
			sf::Vector2f(18, 17),
			sf::Vector2f(12, 20),
			sf::Vector2f(10, 17),

			sf::Vector2f(1, 20),
			sf::Vector2f(10, 10),
			sf::Vector2f(2, 15),
			sf::Vector2f(0, 10),
			sf::Vector2f(3, 3)
		);
	}
} asteroid;