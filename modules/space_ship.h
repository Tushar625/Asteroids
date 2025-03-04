#pragma once


/*class space_ship_class
{
	bb::Exhaust thrust, reverse_thrust;

	sf::Vector2f velocity, accn;

	public:

	vector_sprite_class sprite;

	space_ship_class() : velocity{ 0, 0 }, accn{ SPACESHIP_ACCN, 0 }
	{
		sprite.set_local_size_and_points(
			SPACESHIP_SIZE,
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, 0 },
			sf::Vector2f{ SPACESHIP_SIZE / 4, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, SPACESHIP_SIZE },
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE }
		);

		sprite.setPosition(sf::Vector2f(100, 100));


		thrust.setGap(5);

		thrust.setMaxVelocity(300);

		thrust.setAngle(15);


		reverse_thrust.setGap(5);

		reverse_thrust.setMaxVelocity(300);

		reverse_thrust.setAngle(15);
	}

	void update(double dt)
	{
		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Left))
		{
			sprite.rotate(-SPACESHIP_ROTATION_SPEED * dt);

			// updating accn according to new direction

			accn = {
				cos(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN,
				sin(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN
			};
		}

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Right))
		{
			sprite.rotate(SPACESHIP_ROTATION_SPEED * dt);

			// updating accn according to new direction

			accn = {
				cos(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN,
				sin(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN
			};
		}

		// space ship is propelled forward

		thrust.setSource(sprite.getPosition());

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Up))
		{
			thrust.setDirection(sprite.getRotation() + 180);

			thrust.spray();

			// accelerate the spaceship

			velocity.x += accn.x * dt;

			velocity.y += accn.y * dt;
		}

		// space ship is propelled backward

		reverse_thrust.setSource(sprite.getPosition());

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Down))
		{
			reverse_thrust.setDirection(sprite.getRotation() + 45);

			reverse_thrust.spray();

			reverse_thrust.setDirection(sprite.getRotation() - 45);

			reverse_thrust.spray();

			// decelerate the spaceship

			velocity.x -= accn.x * dt;

			velocity.y -= accn.y * dt;
		}

		// updating position of spaceship according to it's velocity

		sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));

		// updating exhaust gases

		thrust.update(dt);

		reverse_thrust.update(dt);
	}

	void render()
	{
		bb::WINDOW.draw(sprite);

		bb::WINDOW.draw(thrust);

		bb::WINDOW.draw(reverse_thrust);
	}

} space_ship;*/


namespace space_ship
{
	sf::Vector2f accn{ SPACESHIP_ACCN, 0 };



	void create()
	{
		auto rocket = ecs.create_entity();

		rocket.get<ENTITY_TYPE>() = SPACESHIP_ENTITY;
		
		auto& sprite = rocket.get<SPRITE>();

		sprite.set_local_size_and_points(
			SPACESHIP_SIZE,
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, 0 },
			sf::Vector2f{ SPACESHIP_SIZE / 4, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, SPACESHIP_SIZE },
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE }
		);

		sprite.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f));
	}



	void input_processing(vector_sprite_class& sprite, sf::Vector2f& velocity, double dt)
	{
		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Left))
		{
			sprite.rotate(-SPACESHIP_ROTATION_SPEED * dt);

			// updating accn according to new direction

			accn = {
				cos(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN,
				sin(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN
			};
		}

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Right))
		{
			sprite.rotate(SPACESHIP_ROTATION_SPEED * dt);

			// updating accn according to new direction

			accn = {
				cos(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN,
				sin(std::numbers::pi_v<float> / 180 * sprite.getRotation()) * SPACESHIP_ACCN
			};
		}

		// space ship is propelled forward

		thrust.setSource(sprite.getPosition());

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Up))
		{
			thrust.setDirection(sprite.getRotation() + 180);

			thrust.spray();

			// accelerate the spaceship

			velocity.x += accn.x * dt;

			velocity.y += accn.y * dt;
		}

		// space ship is propelled backward

		reverse_thrust.setSource(sprite.getPosition());

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Down))
		{
			reverse_thrust.setDirection(sprite.getRotation() + 45);

			reverse_thrust.spray();

			reverse_thrust.setDirection(sprite.getRotation() - 45);

			reverse_thrust.spray();

			// decelerate the spaceship

			velocity.x -= accn.x * dt;

			velocity.y -= accn.y * dt;
		}
	}
}