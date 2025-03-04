#pragma once



namespace asteroid
{
	void type1(vector_sprite_class& sprite);

	void type2(vector_sprite_class& sprite);
		
	void type3(vector_sprite_class& sprite);
		
	void type4(vector_sprite_class& sprite);
	
	
		
	void create()
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

		// setting random location

		sprite.setPosition(sf::Vector2f(rand() % VIRTUAL_WIDTH, rand() % VIRTUAL_HEIGHT));

		// setting random velocity

		int velo = rand() % (ASTEROID_MAX_VELOCITY - ASTEROID_MIN_VELOCITY + 1) + ASTEROID_MIN_VELOCITY;

		float angle = (rand() % 361) * std::numbers::pi_v<float> / 180;	// 0 -> 360 degrees but in radians

		velocity.x = cos(angle) * velo;

		velocity.y = sin(angle) * velo;

		// setting random scale

		sprite.set_scale((rand() % 2001 + 1000) / 1000.0f);
	}



	void destroy(ECS_TYPE::ENTITY& entity)
	{
		auto& sprite = entity.get<SPRITE>();

		auto pos = sprite.getPosition();

		auto scale = sprite.get_scale();

		ecs.kill_entity(entity);

		if(scale < .8)
		{
			return;
		}

		create();

		create();

		auto id = ecs.entity_count() - 1;

		ecs.entity(id).get<SPRITE>().setPosition(pos);

		ecs.entity(id - 1).get<SPRITE>().setPosition(pos);


		ecs.entity(id).get<SPRITE>().set_scale(scale / 2);

		ecs.entity(id - 1).get<SPRITE>().set_scale(scale / 2);


		ecs.entity(id).get<VELOCITY>().x *= 1.5;

		ecs.entity(id).get<VELOCITY>().y *= 1.5;

		ecs.entity(id - 1).get<VELOCITY>().x *= 1.5;

		ecs.entity(id - 1).get<VELOCITY>().y *= 1.5;
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