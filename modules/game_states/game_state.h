
// the initial state of this game home of the game

#pragma once



//extern class game_state game;



//extern class highest_score_state highest_score;



class game_state : public bb::BASE_STATE
{
	bool pause;

public:

	game_state() : pause(false)
	{}

private:

	void Enter()
	{
		if(ecs.empty())
		{
			// initialize the ecs for the first time

			space_ship::create();

			for (int i = 1; i <= 5; i++)
			{
				asteroid::create();
			}
		}
	}


	void Update(double dt)
	{
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			sm.change_to(initial);
		}

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::P))
		{
			pause = !pause;
		}

		if (pause)
		{
			return;
		}

		for (size_t i = 0; i < ecs.entity_count();)
		{
			auto entity = ecs.entity(i);

			auto& sprite = entity.get<SPRITE>();

			auto& velocity = entity.get<VELOCITY>();

			// common position update function

			sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));

			switch (entity.get<ENTITY_TYPE>())
			{
				case SPACESHIP_ENTITY:

					space_ship::input_processing(sprite, velocity, dt);

					if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter) || bb::INPUT.isPressed(sf::Keyboard::Scan::Space))
					{
						// create bullet

						bullet::create(sprite, velocity);
					}

					asteroid::spaceship_pos = sprite.getPosition();

					break;

				case ASTEROID_ENTITY:

					sprite.rotate(ASTEROID_ROTATION_SPEED * dt);

					if (asteroid::spaceship_collision(sprite))
					{
						//std::cout << "collision\n";

						explosion.create(sprite.getPosition(), sf::Vector2f(velocity.x * 5, velocity.y * 5));

						ecs.kill_entity(entity);

						//std::cout << sprite.get_size() << "\n";

						//std::cout << "i: " << i << "\n";

						//std::cout << entity.get<ENTITY_TYPE>() << "\n";

						//std::cout << sprite.getPosition().x << ", " << sprite.getPosition().y << "\n";

						continue;
					}

					break;

				case BULLET_ENTITY:

					if (!bullet::is_alive(dt))
					{
						ecs.kill_entity(entity);

						continue;
					}

					if (bullet::asteroid_collision(sprite.getPosition()))
					{
						bullet::life_time = 0;

						continue;
					}

					break;
			}

			i++;
		}

		// updating exhaust gases

		thrust.update(dt);

		reverse_thrust.update(dt);

		explosion.update(dt);
	}


	void Render()
	{
		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			bb::WINDOW.draw(ecs.entity(i).get<SPRITE>());
		}

		bb::WINDOW.draw(thrust);

		bb::WINDOW.draw(reverse_thrust);

		bb::WINDOW.draw(explosion);
	}


	void Exit()
	{
		//music.stop();
	}

}game;