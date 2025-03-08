
// the initial state of this game home of the game

#pragma once



//extern class game_state game;



//extern class highest_score_state highest_score;

extern class game_over_state game_over;



class game_state : public bb::BASE_STATE
{
	bool pause;

	game_data_type *i_data;

	sf::Text msg;

public:

	game_state() : pause(false), i_data(NULL), msg(medium_text)
	{}


	void init(game_data_type* i_data)
	{
		this->i_data = i_data;
	}

private:


	void Enter()
	{
		if(ecs.empty())
		{
			// initialize the ecs for the first time

			space_ship::create();

			for (int i = 1; i <= 5; i++)
			{
				asteroid::create(ecs);
			}
		}
	}


	void Update(double dt)
	{
		int asteroid_count = 0;

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			sm.change_to(initial);

			return;
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
						explosion.create(sprite.getPosition(), sf::Vector2f(velocity.x * 5, velocity.y * 5));

						ecs.kill_entity(entity);

						if (i_data->health)
						{
							i_data->health--;
						}
						else
						{
							// game over

							sm.change_to(game_over, i_data->score, i_data->highest_score);

							i_data->reset();

							ecs.clear();

							thrust.clear();

							reverse_thrust.clear();

							explosion.clear();

							return;
						}

						continue;
					}

					asteroid_count++;

					break;

				case BULLET_ENTITY:

					if (!bullet::is_alive(dt))
					{
						ecs.kill_entity(entity);

						continue;
					}

					if (bullet::asteroid_collision(sprite.getPosition(), i_data->score))
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

		if (asteroid_count <= 4)
		{
			int new_asteroid_count = rand() % 5 + 1;

			for (int i = 1; i <= new_asteroid_count; i++)
			{
				asteroid::create(ecs);
			}
		}
	}


	void Render()
	{
		medium_text.setString(std::to_string(static_cast<int>(bb::MY_GAME.get_fps() + .5)));

		medium_text.setPosition(10, 10);

		bb::WINDOW.draw(medium_text);

		// draw the ecs

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			bb::WINDOW.draw(ecs.entity(i).get<SPRITE>());
		}

		bb::WINDOW.draw(thrust);

		bb::WINDOW.draw(reverse_thrust);

		bb::WINDOW.draw(explosion);

		msg.setString(std::to_string(i_data->score));

		msg.setPosition(sf::Vector2f(VIRTUAL_WIDTH - 12 - msg.getLocalBounds().width, 10));

		bb::WINDOW.draw(msg);

		render_health(i_data->health);

		// pause text

		if (pause)
		{
			medium_text.setString("Press 'P' to Play");

			medium_text.setPosition(10, VIRTUAL_HEIGHT - MEDIUM_FONT_SIZE - 10);

			bb::WINDOW.draw(medium_text);
		}
	}


	void Exit()
	{
		//music.stop();
	}

}game;