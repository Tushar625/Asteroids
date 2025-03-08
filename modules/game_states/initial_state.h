
// the initial state of this game home of the game

#pragma once



extern class game_state game;



class initial_state : public bb::BASE_STATE
{
	sf::Text score_text, main_text, input_text;
	
	game_data_type i_data;

	ECS_TYPE bg_ecs;

public:

	initial_state()
	{
		score_text = medium_text;

		score_text.setPosition(10, 10);



		main_text = large_text;
		
		main_text.setString("SPACE\nGAME");

		main_text.setStyle(sf::Text::Bold | sf::Text::Italic);

		main_text.setOrigin(sf::Vector2f(main_text.getLocalBounds().width / 2.0f, LARGE_FONT_SIZE + 7.5));

		main_text.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f);

		main_text.setRotation(3.25);

		main_text.setScale(1, .75);


		input_text = medium_text;

		input_text.setString("--- Press 'Enter' to Start ---");

		input_text.setOrigin(sf::Vector2f(input_text.getLocalBounds().width / 2.0f, MEDIUM_FONT_SIZE / 2.0f));

		input_text.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT - 30);
	}

private:

	//sf::Sound sound;

	//game_data_type i_data;	// created to hold general game data


	void Enter()
	{
		score_text.setString(std::to_string(i_data.highest_score));

		//music.setLoop(true);

		//music.play();

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
			//sound.setBuffer(sound_buffer[CONFIRM]);

			//sound.play();

			sm.change_to(game, &i_data);
		}
		
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			sm.change_to(bb::NULL_STATE);
		}

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

		bb::WINDOW.draw(main_text);

		bb::WINDOW.draw(input_text);
	}


	void Exit()
	{
		bg_ecs.clear();
		//music.stop();
	}

}initial;