
// the message state of this game, displays the victory and defeat message

#pragma once



extern class highest_score_state highest_score;



class game_over_state : public bb::BASE_STATE
{
	public:

	sf::Text main_text_line1, main_text_line2, input_text;

	int score;

	int _highest_score;

	game_over_state()
	{
		main_text_line1 = large_text;

		main_text_line1.setString("GAME");

		main_text_line1.setStyle(sf::Text::Bold);

		center_origin(main_text_line1);

		main_text_line1.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f - 37);


		main_text_line2 = large_text;

		main_text_line2.setString("OVER");

		main_text_line2.setStyle(sf::Text::Bold);

		center_origin(main_text_line2);

		main_text_line2.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f + 37);


		input_text = medium_text;

		input_text.setString("--- Press 'Enter' to Play Again ---");

		center_origin(input_text);

		input_text.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT - 20);
	}

	void init(int score, int highest_score)
	{
		this->score = score;

		this->_highest_score = highest_score;
	}


	private:


	//sf::Sound sound;


	void Enter()
	{
		auto entity = ecs.entity(0);

		auto& sprite = entity.get<SPRITE>();

		auto& velocity = entity.get<VELOCITY>();

		explosion.create(sprite.getPosition(), velocity);
	}


	void Update(double dt)
	{
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			//sound.setBuffer(sound_buffer[SELECT]);

			//sound.play();

			if (_highest_score < score)
			{
				sm.change_to(highest_score, score);
			}
			else
			{
				sm.change_to(initial);
			}

			return;
		}

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

		explosion.update(dt);
	}


	void Render()
	{
		render_fps();

		// render the buttons and the messages

		for (size_t i = 0; i < ecs.entity_count(); i++)
		{
			if(ecs.entity(i).get<ENTITY_TYPE>() == ASTEROID_ENTITY)
			{
				bb::WINDOW.draw(ecs.entity(i).get<SPRITE>());
			}
		}

		bb::WINDOW.draw(explosion);

		bb::WINDOW.draw(main_text_line1);

		bb::WINDOW.draw(main_text_line2);

		bb::WINDOW.draw(input_text);

		render_score(score);
	}


	void Exit()
	{
		ecs.clear();

		explosion.clear();
	}

}game_over;