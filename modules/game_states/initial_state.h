
// the initial state of this game or "home" of the game

#pragma once



extern class game_state game;



class initial_state : public bb::BASE_STATE
{
	// all the texts in the home screen

	sf::Text score_text, main_text_line1, main_text_line2, input_text;
	
	// structure to store important game info score, health and highest score

	game_data_type i_data;

	// this ecs is only used to have some moving rocks in the background of home screen

	ECS_TYPE bg_ecs;

public:

	initial_state()
	{
		// score text displayes the highest score

		score_text = medium_text;

		score_text.setPosition(10, 10);


		main_text_line1 = large_text;
		
		main_text_line1.setString("SPACE");

		main_text_line1.setStyle(sf::Text::Bold);
		
		bb::setCenterOrigin(main_text_line1);

		main_text_line1.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f - 37);


		main_text_line2 = large_text;

		main_text_line2.setString("GAME");

		main_text_line2.setStyle(sf::Text::Bold);

		bb::setCenterOrigin(main_text_line2);

		main_text_line2.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f + 37);


		input_text = medium_text;

		input_text.setString("--- Press 'Enter' to Start ---");

		bb::setCenterOrigin(input_text);

		input_text.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT - 20);
	}

private:


	void Enter()
	{
		// display the highest score

		score_text.setString(std::to_string(i_data.highest_score));

		// creating some asteroids for background

		bg_ecs.reserve_extra(7);

		for (int i = 1; i <= 7; i++)
		{
			asteroid::create(bg_ecs);
		}
	}


	void Update(double dt)
	{
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			click();

			// send a pointer to i_data to game state

			sm.change_to(game, &i_data);
		}
		
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			sm.change_to(bb::NULL_STATE);	// stop the game
		}

		// updating the ecs

		for (size_t i = 0; i < bg_ecs.entity_count(); i++)
		{
			auto entity = bg_ecs.entity(i);

			auto& sprite = entity.get<SPRITE>();

			auto& velocity = entity.get<VELOCITY>();

			sprite.rotate(ASTEROID_ROTATION_SPEED * dt);

			sprite.move_wrap(sf::Vector2f(velocity.x * dt, velocity.y * dt));
		}
	}


	void Render()
	{
		for (size_t i = 0; i < bg_ecs.entity_count(); i++)
		{
			bb::WINDOW.draw(bg_ecs.entity(i).get<SPRITE>());
		}

		bb::WINDOW.draw(score_text);

		bb::WINDOW.draw(main_text_line1);

		bb::WINDOW.draw(main_text_line2);

		bb::WINDOW.draw(input_text);
	}


	void Exit()
	{
		// destroy background ecs

		bg_ecs.clear();
	}

}initial;