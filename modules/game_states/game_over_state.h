
/*
	here we arrive after the game is over, its main purpose
	is to display "game over" and spaceship explosion
*/

#pragma once



extern class highest_score_state highest_score;



class game_over_state : public bb::BASE_STATE
{
	public:


	// to display "game over"

	sf::Text main_text_line1, main_text_line2;

	// score is displayed here
	
	int score;

	// highest score is not displayed here but sent to highest score state

	int _highest_score;

	// how long to wait before we go to highest score state
	
	double duration;


	game_over_state()
	{
		main_text_line1 = large_text;

		main_text_line1.setString("GAME");

		main_text_line1.setStyle(sf::Text::Bold);

		bb::setCenterOrigin(main_text_line1);

		main_text_line1.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f - 37);


		main_text_line2 = large_text;

		main_text_line2.setString("OVER");

		main_text_line2.setStyle(sf::Text::Bold);

		bb::setCenterOrigin(main_text_line2);

		main_text_line2.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f + 37);
	}


	// receiving score and heighest score from game state

	void init(int score, int highest_score)
	{
		this->score = score;

		this->_highest_score = highest_score;
	}


	private:


	void Enter()
	{
		/*
			no need to delete the spaceship, just don't render it in this state
			and create an explosion at its place
		*/

		auto entity = ecs.entity(0);

		auto& sprite = entity.get<SPRITE>();

		auto& velocity = entity.get<VELOCITY>();

		explosion.create(sprite.getPosition(), velocity);

		/*
			this state will display game over for certain duration, after that
			we go to highest score state
		*/
		
		duration = 3;
	}


	void Update(double dt)
	{
		/*
			when duration is 0 or less we go to highest score state

			if user don't like to wait he can press "Enter" or "Escape" to go to highest score state
		*/

		if (duration < 0)
		{
			sm.change_to(highest_score, score, _highest_score);

			return;
		}

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter) || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			click();

			sm.change_to(highest_score, score, _highest_score);

			return;
		}

		// update the asteroids in the ECS

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			auto entity = ecs.entity(i);

			auto& sprite = entity.get<SPRITE>();

			auto& velocity = entity.get<VELOCITY>();

			if (entity.get<ENTITY_TYPE>() == ASTEROID_ENTITY)
			{
				sprite.rotate(ASTEROID_ROTATION_SPEED * dt);

				sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));
			}
		}

		// update the explosions

		explosion.update(dt);

		// when duration is 0 we go to highest score state

		duration -= dt;
	}


	void Render()
	{
		// render the asteroids in the ECS

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			if(ecs.entity(i).get<ENTITY_TYPE>() == ASTEROID_ENTITY)
			{
				bb::WINDOW.draw(ecs.entity(i).get<SPRITE>());
			}
		}

		// we still need to render a asteroid and spaceship explosion

		bb::WINDOW.draw(explosion);

		// rendering "game over"

		bb::WINDOW.draw(main_text_line1);

		bb::WINDOW.draw(main_text_line2);

		// render the score as game state

		render_score(score);
	}


	void Exit()
	{
		/*
			finally at the end of game over state we clean up remaining assets,
			main ECS and explosion
		*/

		ecs.clear();

		explosion.clear();
	}

}game_over;