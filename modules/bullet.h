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
}