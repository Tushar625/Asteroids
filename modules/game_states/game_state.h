
// the main gameplay of this game

#pragma once



extern class game_over_state game_over;



class game_state : public bb::BASE_STATE
{
	// it's used to pause or resume this game

	bool pause;

	game_data_type *i_data;

public:

	
	game_state() : pause(false), i_data(NULL)
	{}


	// receiving pointer to i_data send by initial state

	void init(game_data_type* i_data)
	{
		this->i_data = i_data;
	}


private:


	void Enter()
	{
		/*
			initialize the main ecs only if it's empty, i.e., at the beginning of the game
			
			ecs is cleared only after the game is over
		*/

		if(ecs.empty())
		{
			// space ship is the first element of ecs

			space_ship::create();

			// after that we put 5 big asteroids

			for (int i = 1; i <= 5; i++)
			{
				asteroid::create(ecs);
			}
		}
	}


	void Update(double dt)
	{
		/*
			keep track of the no.of asteroids in the ecs, if it's too small we add
			new asteroids
		*/

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
			return;	// don't update ECS the game is paused
		}

		// updating the ECS

		for (size_t i = 0; i < ecs.entity_count();)
		{
			auto entity = ecs.entity(i);

			auto& sprite = entity.get<SPRITE>();

			auto& velocity = entity.get<VELOCITY>();

			// position update function is same for all entities

			sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));

			switch (entity.get<ENTITY_TYPE>())
			{
				case SPACESHIP_ENTITY:

					// updating spaceship velocity and rotation according to user inputs

					space_ship::input_processing(sprite, velocity, dt);

					if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter) || bb::INPUT.isPressed(sf::Keyboard::Scan::Space))
					{
						// create a bullet

						bullet::create(sprite, velocity);
					}

					// updating the spaceship position for asteroids system

					asteroid::spaceship_pos = sprite.getPosition();

					break;

				case ASTEROID_ENTITY:

					// we rotate the asteroids at a const speed

					sprite.rotate(ASTEROID_ROTATION_SPEED * dt);

					if (asteroid::spaceship_collision(sprite))
					{
						// this asteroid has collided with the spaceship

						// need a nice space explosion at its place
						
						explosion.create(sprite.getPosition(), sf::Vector2f(velocity.x * 5, velocity.y * 5));

						// delete the asteroid

						ecs.kill_entity(entity);

						if (i_data->health)
						{
							i_data->health--;
						}
						else
						{
							// game over

							sm.change_to(game_over, i_data->score, i_data->highest_score);

							// these elements are not needed in the game over state so we reset or clear them here

							i_data->reset();

							thrust.clear();

							reverse_thrust.clear();

							return;
						}

						continue;
					}

					// this asteroid has not been deleted so add to count

					asteroid_count++;

					break;

				case BULLET_ENTITY:

					// is_alive checks and decrements the life span of the bullets

					if (!bullet::is_alive(dt))
					{
						ecs.kill_entity(entity);

						continue;
					}

					if (bullet::asteroid_collision(sprite.getPosition(), i_data->score))
					{
						// this bullet has successfully hit an asteroid

						/*
							in ideal program I should have deleted the bullet, but due to some disadvantages
							of this ECS we can't delete the bullet after deleting the asteroid, instead we
							set the lifetime to zero, you may think, this will destroy all the bullets!, yes
							it will, but we usually have very few bullets in the screen and they are very fast
							so, there won't be any noticable issue in the gameplay but will save me some effort,
							I am lazy :)
						*/

						bullet::life_time = 0;

						// one asteroid has been deleted

						asteroid_count--;

						continue;
					}

					break;
			}

			i++;
		}

		// updating exhaust gases and explosion simulations

		thrust.update(dt);

		reverse_thrust.update(dt);

		explosion.update(dt);

		// adding new big asteroids if 4 or less asteroids are left

		if (asteroid_count <= 4)
		{
			int new_asteroid_count = rand() % 5 + 1;	// 1 - 5

			for (int i = 1; i <= new_asteroid_count; i++)
			{
				asteroid::create(ecs);
			}
		}
	}


	void Render()
	{
		// draw the ecs

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			bb::WINDOW.draw(ecs.entity(i).get<SPRITE>());
		}

		// drawing the particle systems

		bb::WINDOW.draw(thrust);

		bb::WINDOW.draw(reverse_thrust);

		bb::WINDOW.draw(explosion);

		// score and health

		render_score(i_data->score);

		render_health(i_data->health);

		// pause text, to be displayed only if the game is paused

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

		// if the space ship explods while the thrust sound is active, we need to stop it here

		rocket_engine_sound.stop();
	}

}game;