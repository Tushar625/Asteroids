#pragma once



namespace bullet
{
	float life_time = -1;



	void create(const vector_sprite_class& space_ship_sprite, const sf::Vector2f& space_ship_velocity)
	{
		auto ball = ecs.create_entity();

		ball.get<ENTITY_TYPE>() = BULLET_ENTITY;

		auto& sprite = ball.get<SPRITE>();

		auto& velocity = ball.get<VELOCITY>();

		sprite.set_local_size_and_points(
			BULLET_SIZE,
			sf::Vector2f(BULLET_HALF_SIZE, 0),
			sf::Vector2f(BULLET_SIZE, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, BULLET_SIZE),
			sf::Vector2f(0, BULLET_HALF_SIZE),
			sf::Vector2f(BULLET_HALF_SIZE, 0)
		);

		// calculating bullet velocity

		float angle = space_ship_sprite.getRotation() * std::numbers::pi_v<float> / 180;	// 0 -> 359 degrees but in radians

		velocity.x = cos(angle) * BULLET_VELOCITY;

		velocity.y = sin(angle) * BULLET_VELOCITY;

		velocity += space_ship_velocity;	// adding spaceship velocity to bullet velocity

		// setting scale

		sprite.set_scale(1);
		
		// set rotation and position

		sprite.setRotation(space_ship_sprite.getRotation());

		sprite.setPosition(space_ship_sprite.getPosition());

		// setting life time

		life_time = BULLET_LIFE_TIME;
	}



	bool is_alive(double dt)
	{
		life_time -= dt;

		return life_time > 0;
	}



	bool point_polygon_collision(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon)
	{
		uint16_t intersection_count = 0;
		
		sf::Vector2f rey_end{ std::numeric_limits<float>::max(), point.y};

		for (size_t i = 1; i < polygon.size(); i++)
		{
			const sf::Vector2f& p1 = polygon[i - 1];

			const sf::Vector2f& p2 = polygon[i];

			if ((p1.y <= point.y && point.y <= p2.y) || (p2.y <= point.y && point.y <= p1.y))
			{
				float intersect_x = ((p2.x - p1.x) / (p2.y - p1.y)) * (point.y - p1.y) + p1.x;

				if (point.x <= intersect_x && intersect_x <= rey_end.x)
				{
					intersection_count++;
				}
			}
		}

		return intersection_count % 2;	// odd == collision
	}



	bool asteroid_collision(const sf::Vector2f & bullet_position, int &score)
	{
		static std::vector<sf::Vector2f> polygon;

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			auto entity = ecs.entity(i);

			if (entity.get<ENTITY_TYPE>() != ASTEROID_ENTITY)
			{
				continue;
			}

			auto& sprite = entity.get<SPRITE>();

			polygon.clear();

			polygon.resize(sprite.get_point_count());

			size_t j = 0;

			// creating the polygon vector representing the asteroid

			for (auto& p : polygon)
			{
				p = sprite.get_global_point(j++);
			}

			if (point_polygon_collision(bullet_position, polygon))
			{
				// collision detected

				score += MAX_SCORE / sprite.get_scale();

				asteroid::destroy(entity);

				return true;
			}
		}

		return false;
	}
}