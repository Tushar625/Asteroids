#pragma once


/*
	systems for Spaceship Entity in ECS
*/


namespace space_ship
{
	sf::Vector2f accn;	// it's used to simulate the accn caused by thrust


	// create a spaceship entity

	void create()
	{
		auto rocket = ecs.create_entity();

		rocket.get<ENTITY_TYPE>() = SPACESHIP_ENTITY;
		
		auto& sprite = rocket.get<SPRITE>();

		// create the spaceship shape and set its size and origin

		sprite.set_local_size_and_points(
			SPACESHIP_SIZE,
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, 0 },
			sf::Vector2f{ SPACESHIP_SIZE / 4, SPACESHIP_HALF_SIZE },
			sf::Vector2f{ 0, SPACESHIP_SIZE },
			sf::Vector2f{ SPACESHIP_SIZE, SPACESHIP_HALF_SIZE }
		);

		// place the spaceship in the middle of the screen

		sprite.setPosition(sf::Vector2f(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f));

		// make the spaceship point up

		sprite.setRotation(-90);

		/*
			acceleration of the spaceship when thrust is applied

			the spaceship is pointing up, the accn is set accordingly, it will make
			the spaceship move up
		*/

		accn = { 0, -SPACESHIP_ACCN };
	}


	// the input processing system

	void input_processing(vector_sprite_class& sprite, sf::Vector2f& velocity, double dt)
	{
		// rotation and acceleration update according to spaceship direction

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


		/*
			I set the position of exhaust effect at the center of the spaceship, but I set
			some gap between the source point and the point where the exhaust effect will
			appear, this is enough to make the exhaust effect appear on the outside of the
			spaceship.
		*/

		// space ship is propelled forward

		thrust.setSource(sprite.getPosition());	// setting position of exhaust effect

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Up))
		{
			// creating the exhaust effect

			thrust.setDirection(sprite.getRotation() + 180);

			thrust.spray();

			// change velocity according to the acceleration

			velocity.x += accn.x * dt;

			velocity.y += accn.y * dt;
		}

		// space ship is propelled backward

		reverse_thrust.setSource(sprite.getPosition());	// setting position of exhaust effect

		if (bb::INPUT.isHeld(sf::Keyboard::Scan::Down))
		{
			// creating the exhaust effect

			reverse_thrust.setDirection(sprite.getRotation() + 45);

			reverse_thrust.spray();

			reverse_thrust.setDirection(sprite.getRotation() - 45);

			reverse_thrust.spray();

			// change velocity according to the acceleration

			velocity.x -= accn.x * dt;

			velocity.y -= accn.y * dt;
		}
	}
}