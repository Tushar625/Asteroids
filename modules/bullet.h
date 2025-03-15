#pragma once


/*
	systems for bullet Entity in ECS
*/


namespace bullet
{
	/*
		we are using single life_time variable to keep track of the lifetime
		of all the bullets

		it's not a good method but works quite well
	*/

	float life_time = -1;



	void create(const vector_sprite_class& space_ship_sprite, const sf::Vector2f& space_ship_velocity)
	{
		auto ball = ecs.create_entity();

		ball.get<ENTITY_TYPE>() = BULLET_ENTITY;

		auto& sprite = ball.get<SPRITE>();

		auto& velocity = ball.get<VELOCITY>();

		// creating the bullet shape

		sprite.set_local_size_and_points(
			BULLET_SIZE,
			sf::Vector2f(BULLET_HALF_SIZE, 0),
			sf::Vector2f(BULLET_SIZE, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, BULLET_SIZE),
			sf::Vector2f(0, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, 0)
		);

		// calculating bullet velocity

		float angle = space_ship_sprite.getRotation() * std::numbers::pi_v<float> / 180;	// direction of spaceship in radians

		velocity.x = cos(angle) * BULLET_VELOCITY;

		velocity.y = sin(angle) * BULLET_VELOCITY;

		velocity += space_ship_velocity;	// adding spaceship velocity to bullet velocity

		// set rotation and position

		sprite.setRotation(space_ship_sprite.getRotation());

		/*
			origin of the spaceship is at its center, and we set the source of the
			bullet at that point,
			
			but the bullet must come out of the front of the spaceship.

			actually the bullet moves so fast that player won't notice that it's coming
			out of the center of the spaceship,
			
			we lazy programmers :)
		*/

		sprite.setPosition(space_ship_sprite.getPosition());

		// setting life time

		life_time = BULLET_LIFE_TIME;
	}



	/*
		this function is supposed to be called from the update loop of ecs
		so it also decreases the life time
	*/
	
	bool is_alive(double dt = 0)
	{
		life_time -= dt;

		return life_time > 0;
	}



	// check if a bullet (treated as a point) collids with any asteroid or not and also update the score

	bool asteroid_collision(const sf::Vector2f &bullet_position, int &score)
	{
		static std::vector<sf::Vector2f> polygon;

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			auto entity = ecs.entity(i);

			if (entity.get<ENTITY_TYPE>() != ASTEROID_ENTITY)
			{
				continue;
			}

			// only asteroid entities are accepted

			auto& sprite = entity.get<SPRITE>();

			// creating the polygon vector representing the asteroid

			polygon.clear();

			polygon.resize(sprite.get_point_count());

			size_t j = 0;

			for (auto& p : polygon)
			{
				p = sprite.get_global_point(j++);
			}

			// checking for collision

			if (bb::point_polygon_collision(bullet_position, polygon))
			{
				// collision detected

				score += MAX_SCORE / sprite.get_scale();	// update the score based on the scale of the polygon

				asteroid::destroy(entity);	// destroy the asteroid

				return true;	// only one asteroid is destroyed
			}
		}

		return false;
	}
}