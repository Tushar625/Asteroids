#pragma once



namespace bullet
{
	float life_time = -1;

	void create(const vector_sprite_class& space_ship_sprite)
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

		// calculating speed

		float angle = space_ship_sprite.getRotation() * std::numbers::pi_v<float> / 180;	// 0 -> 359 degrees but in radians

		velocity.x = cos(angle) * BULLET_VELOCITY;

		velocity.y = sin(angle) * BULLET_VELOCITY;

		// set rotation and position

		sprite.setRotation(space_ship_sprite.getRotation());

		sprite.setPosition(space_ship_sprite.getPosition());

		// setting life time

		life_time = BULLET_LIFE_TIME;
	}

	bool update(ECS_TYPE::ENTITY& ball, double dt)
	{
		auto& sprite = ball.get<SPRITE>();

		auto& velocity = ball.get<VELOCITY>();

		life_time -= dt;

		if (life_time < 0)
		{
			ecs.kill_entity(ball);

			return true;
		}

		sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));

		return false;
	}

	void render(ECS_TYPE::ENTITY& ball)
	{
		auto& sprite = ball.get<SPRITE>();

		bb::WINDOW.draw(sprite);
	}
}