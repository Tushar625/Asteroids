#pragma once



namespace asteroid
{
	sf::Vector2f spaceship_pos;



	void type1(vector_sprite_class& sprite);

	void type2(vector_sprite_class& sprite);
		
	void type3(vector_sprite_class& sprite);
		
	void type4(vector_sprite_class& sprite);
	
	
		
	ECS_TYPE::ENTITY create(ECS_TYPE &ecs)
	{
		auto astro = ecs.create_entity();

		astro.get<ENTITY_TYPE>() = ASTEROID_ENTITY;

		auto& sprite = astro.get<SPRITE>();

		auto& velocity = astro.get<VELOCITY>();

		// setting type of asteroid

		switch (rand() % 4)
		{
			case 0: type1(sprite); break;

			case 1: type2(sprite); break;

			case 2: type3(sprite); break;

			case 3: type4(sprite); break;
		}

		// setting random velocity

		int velo = rand() % (ASTEROID_MAX_VELOCITY - ASTEROID_MIN_VELOCITY + 1) + ASTEROID_MIN_VELOCITY;

		float angle = (rand() % 361) * std::numbers::pi_v<float> / 180;	// 0 -> 360 degrees but in radians

		velocity.x = cos(angle) * velo;

		velocity.y = sin(angle) * velo;

		// setting random scale

		sprite.set_scale((rand() % 2001 + 1000) / 1000.0f);

		// setting random location across the border

		if (rand() % 2)
		{
			sprite.setPosition(sf::Vector2f(rand() % VIRTUAL_WIDTH, (rand() % 2) ? (0 - sprite.get_half_size()) : (VIRTUAL_HEIGHT + sprite.get_half_size())));
		}
		else
		{
			sprite.setPosition(sf::Vector2f((rand() % 2) ? (0 - sprite.get_half_size()) : (VIRTUAL_WIDTH + sprite.get_half_size()), rand() % VIRTUAL_HEIGHT));
		}

		return astro;
	}



	void destroy(ECS_TYPE::ENTITY& entity)
	{
		auto& sprite = entity.get<SPRITE>();

		auto& velocity = entity.get<VELOCITY>();

		auto pos = sprite.getPosition();

		auto scale = sprite.get_scale();

		ecs.kill_entity(entity);

		// create an explosion effect in the place of destroyed asteroid using the bullet's velocity

		/*
			something unusual is going on here, the killed entity gets replaced by the
			last entity in the ECS, which usually is the bullet that killed it, now
			"velocity" was a reference to the asteroid's velocity but after "kill_entity"
			call it starts to reference to the velocity of the bullet that hit it

			same goes for the "sprite", so, don't use them after "kill_entity" call
		*/

		explosion.create(pos, velocity);

		if(scale < .9)
		{
			return;
		}

		int new_asteroid_count = rand() % 2 + 1;

		while (new_asteroid_count-- > 0)
		{
			auto&& entity = create(ecs);

			entity.get<SPRITE>().setPosition(pos);

			entity.get<SPRITE>().set_scale(scale * ((rand() % 301 + 500) / 1000.0f));	// .5 - .8

			entity.get<VELOCITY>().x *= (rand() % 801 + 1200) / 1000.0f;	// 1.2 - 2.0

			entity.get<VELOCITY>().y *= (rand() % 801 + 1200) / 1000.0f;	// 1.2 - 2.0
		}
	}



	bool spaceship_collision(const vector_sprite_class& sprite)
	{
		/*
			I noticed some unusual behaviour around here

			my rocket was the first element in ecs so I accessed it as ecs.entity(0)

			it had a peculier effect of setting the loop counter of update loop to 0

			hence I abandon that idea and store the position of spaceship into a seperate variable
		*/
		
		auto& asteroid_position = sprite.getPosition();

		return bb::aabb_collision(spaceship_pos.x - SPACESHIP_HALF_SIZE, spaceship_pos.y - SPACESHIP_HALF_SIZE, SPACESHIP_SIZE, SPACESHIP_SIZE,
			asteroid_position.x - sprite.get_half_size(), asteroid_position.y - sprite.get_half_size(), sprite.get_size(), sprite.get_size()
		);
	}



	void type1(vector_sprite_class& sprite)
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

	void type2(vector_sprite_class& sprite)
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

	void type3(vector_sprite_class& sprite)
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

	void type4(vector_sprite_class& sprite)
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
}