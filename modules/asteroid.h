#pragma once


/*
	systems for Asteroid Entity in ECS
*/


namespace asteroid
{
	// it's used to track the spaceship, useful for spaceship - asteroid collision detection

	sf::Vector2f spaceship_pos;



	void type1(vector_sprite_class& sprite);

	void type2(vector_sprite_class& sprite);
		
	void type3(vector_sprite_class& sprite);
		
	void type4(vector_sprite_class& sprite);

	void type5(vector_sprite_class& sprite);
	

	
	// create an asteroid entity
		
	ECS_TYPE::ENTITY create(ECS_TYPE &ecs)
	{
		auto astro = ecs.create_entity();

		astro.get<ENTITY_TYPE>() = ASTEROID_ENTITY;

		auto& sprite = astro.get<SPRITE>();

		auto& velocity = astro.get<VELOCITY>();

		// setting random type of asteroid

		switch (rand() % 5)
		{
			case 0: type1(sprite); break;

			case 1: type2(sprite); break;

			case 2: type3(sprite); break;

			case 3: type4(sprite); break;

			case 4: type5(sprite); break;
		}

		// setting random velocity

		int velo = rand() % (ASTEROID_MAX_VELOCITY - ASTEROID_MIN_VELOCITY + 1) + ASTEROID_MIN_VELOCITY;

		float angle = (rand() % 361) * std::numbers::pi_v<float> / 180;	// 0 -> 360 degrees but in radians

		velocity.x = cos(angle) * velo;

		velocity.y = sin(angle) * velo;

		// setting random scale 1.0 - 2.0

		sprite.set_scale((rand() % 2001 + 1000) / 1000.0f);

		// setting random location across the border

		if (rand() % 2)
		{
			// from top or bottom edge

			sprite.setPosition(sf::Vector2f(rand() % VIRTUAL_WIDTH, (rand() % 2) ? (0 - sprite.get_half_size()) : (VIRTUAL_HEIGHT + sprite.get_half_size())));
		}
		else
		{
			// from left or right edge

			sprite.setPosition(sf::Vector2f((rand() % 2) ? (0 - sprite.get_half_size()) : (VIRTUAL_WIDTH + sprite.get_half_size()), rand() % VIRTUAL_HEIGHT));
		}

		return astro;
	}



	// destroy an asteroid "when bullet hits it" and create some new ones in it's place

	void destroy(ECS_TYPE::ENTITY& entity)
	{
		auto& sprite = entity.get<SPRITE>();

		auto& velocity = entity.get<VELOCITY>();

		auto pos = sprite.getPosition();

		auto scale = sprite.get_scale();

		ecs.kill_entity(entity);

		{
			static sf::Sound sound;

			// play asteroid explosion sound

			sound.setBuffer(asteroid_blast_sound);

			// 0 < scale < 2 ~ 0 < volume < 100

			sound.setVolume(37.5 * scale);

			// we change pitch to make each explosion sound different

			sound.setPitch(((rand() % 301 + 700) / 1000.0));	// .7 -> 1

			sound.play();
		}

		// create an explosion effect in the place of destroyed asteroid using the bullet's velocity

		/*
			something unusual is going on here, the killed entity gets replaced by the
			last entity in the ECS, which usually is the bullet that killed it, now
			"velocity" was a reference to the asteroid's velocity but after "kill_entity"
			call it starts to reference to the velocity of the bullet that hit it

			same goes for the "sprite", so, don't use them after "kill_entity" call
		*/

		// no. of particles in the explosion is dependent on the scale of the asteroid

		explosion.create(pos, velocity, sf::Color::White, 2000 * scale);

		if(scale < .9)
		{
			// very small asteroid, no need to create new ones

			return;
		}

		// create random number of new asteroids

		int new_asteroid_count = rand() % 2 + 1;	// 1 - 2

		while (new_asteroid_count-- > 0)
		{
			auto&& entity = create(ecs);

			entity.get<SPRITE>().setPosition(pos);

			entity.get<SPRITE>().set_scale(scale * ((rand() % 301 + 500) / 1000.0f));	// .5 - .8

			// new asteroids should have greater velocity than normal

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

			**** I found that, this can be avoided by using a copy of the entity object in the loop
			**** instead of a reference
		*/

		/*
			simple aabb collision, both the spaceship and the asteroid are treated as squares
		*/
		
		auto& asteroid_position = sprite.getPosition();

		return bb::aabb_collision(
			spaceship_pos.x - SPACESHIP_HALF_SIZE, spaceship_pos.y - SPACESHIP_HALF_SIZE, SPACESHIP_SIZE, SPACESHIP_SIZE,
			asteroid_position.x - sprite.get_half_size(), asteroid_position.y - sprite.get_half_size(), sprite.get_size(), sprite.get_size()
		);
	}



	/*
		different asteroid shapes
	*/

	
	
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
			sf::Vector2f(0, 7),
			sf::Vector2f(1, 3),
			sf::Vector2f(6, 0),
			sf::Vector2f(12, 0),
			sf::Vector2f(13, 1),

			sf::Vector2f(14, 4),
			sf::Vector2f(15, 5),
			sf::Vector2f(16, 5),
			sf::Vector2f(17, 4),
			sf::Vector2f(18, 4),

			sf::Vector2f(19, 5),
			sf::Vector2f(19, 9),
			sf::Vector2f(18, 10),
			sf::Vector2f(18, 11),
			sf::Vector2f(19, 12),

			sf::Vector2f(19, 17),
			sf::Vector2f(18, 18),
			sf::Vector2f(16, 18),
			sf::Vector2f(15, 17),
			sf::Vector2f(12, 16),

			sf::Vector2f(12, 17),
			sf::Vector2f(10, 16),
			sf::Vector2f(9, 18),
			sf::Vector2f(8, 19),
			sf::Vector2f(4, 19),

			sf::Vector2f(2, 17),
			sf::Vector2f(2, 15),
			sf::Vector2f(0, 12),
			sf::Vector2f(0, 7)
		);
	}



	void type3(vector_sprite_class& sprite)
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(0, 4),
			sf::Vector2f(2, 2),
			sf::Vector2f(6, 2),
			sf::Vector2f(9, 0),
			sf::Vector2f(13, 0),
			sf::Vector2f(19, 6),
			sf::Vector2f(19, 11),
			sf::Vector2f(18, 12),
			sf::Vector2f(18, 17),
			sf::Vector2f(16, 19),
			sf::Vector2f(12, 19),
			sf::Vector2f(7, 17),
			sf::Vector2f(3, 18),
			sf::Vector2f(1, 17),
			sf::Vector2f(2, 13),
			sf::Vector2f(0, 11),
			sf::Vector2f(0, 4)
		);
	}



	void type4(vector_sprite_class& sprite)
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(0, 7),
			sf::Vector2f(1, 3),
			sf::Vector2f(5, 0),
			sf::Vector2f(7, 0),
			sf::Vector2f(9, 2),
			sf::Vector2f(11, 1),
			sf::Vector2f(13, 0),
			sf::Vector2f(15, 1),
			sf::Vector2f(17, 3),
			sf::Vector2f(17, 4),
			sf::Vector2f(15, 7),
			sf::Vector2f(18, 9),
			sf::Vector2f(19, 11),
			sf::Vector2f(19, 13),
			sf::Vector2f(18, 14),
			sf::Vector2f(16, 17),
			sf::Vector2f(12, 18),
			sf::Vector2f(9, 19),
			sf::Vector2f(4, 17),
			sf::Vector2f(2, 15),
			sf::Vector2f(1, 11),
			sf::Vector2f(0, 9),
			sf::Vector2f(0, 7)
		);
	}



	void type5(vector_sprite_class& sprite)
	{
		sprite.set_local_size_and_points(
			ASTEROID_SIZE,
			sf::Vector2f(1, 7),
			sf::Vector2f(0, 4),
			sf::Vector2f(1, 3),
			sf::Vector2f(4, 0),
			sf::Vector2f(7, 0),

			sf::Vector2f(8, 1),
			sf::Vector2f(11, 1),
			sf::Vector2f(17, 2),
			sf::Vector2f(18, 6),
			sf::Vector2f(19, 8),
			sf::Vector2f(19, 9),
			
			sf::Vector2f(18, 11),
			sf::Vector2f(18, 14),
			sf::Vector2f(17, 19),
			sf::Vector2f(13, 18),
			sf::Vector2f(10, 19),
			
			sf::Vector2f(7, 18),
			sf::Vector2f(4, 19),
			sf::Vector2f(3, 17),
			sf::Vector2f(2, 15),
			sf::Vector2f(2, 11),
			sf::Vector2f(1, 7)
		);
	}
}