
// after game over we come here to display the score, before going to home

#pragma once



class highest_score_state : public bb::BASE_STATE
{
	sf::Text main_text_line1, main_text_line2, main_text_line3, input_text;

	// delay between two explosions, during celebration
	
	double delay;

	// no. of explosions for celebration

	int count;

public:

	/*
		init here initializes the texts according to the arguments
	*/

	void init(int score, int highest_score)
	{
		// three lines in the middle of the screen
		
		// line1 = "score"

		main_text_line1 = medium_text;

		main_text_line1.setString("Score");

		bb::setCenterOrigin(main_text_line1);

		main_text_line1.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f - 6 - MEDIUM_FONT_SIZE);


		// line2 = actual score

		main_text_line2 = medium_text;

		main_text_line2.setString(std::to_string(score));

		bb::setCenterOrigin(main_text_line2);

		main_text_line2.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f);


		// line3 = highest score message

		main_text_line3 = medium_text;

		if(highest_score < score)
		{
			main_text_line3.setString("!! New High Score !!");

			count = 20;	// how many explosions we create to celebrate
		}
		else
		{
			main_text_line3.setString("High Score is " + std::to_string(highest_score));

			count = 0;	// no celebration
		}

		bb::setCenterOrigin(main_text_line3);

		main_text_line3.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f + 6 + MEDIUM_FONT_SIZE);

		
		// how to go to initial state

		input_text = medium_text;

		input_text.setString("--- Press 'Enter' to Play Again ---");

		bb::setCenterOrigin(input_text);

		input_text.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT - 20);
	}

private:

	//sf::Sound sound;


	void Enter()
	{
		// to get the explosions started

		delay = -1;
	}


	void Update(double dt)
	{
		if (count)
		{
			if (delay < 0)
			{
				explosion.create(sf::Vector2f(rand() % VIRTUAL_WIDTH, rand() % VIRTUAL_HEIGHT), sf::Vector2f(0, 0), sf::Color::White, 10000, 80 + rand() % 100, 1 + rand() % 4);

				delay = (rand() % 1000) / 1000.0;	// reset random delay

				--count;
			}
		}

		delay -= dt;

		explosion.update(dt);

		// go to home

		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter) || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		{
			sm.change_to(initial);
		}
	}


	void Render()
	{
		bb::WINDOW.draw(explosion);

		bb::WINDOW.draw(main_text_line1);

		bb::WINDOW.draw(main_text_line2);

		bb::WINDOW.draw(main_text_line3);

		bb::WINDOW.draw(input_text);
	}


	void Exit()
	{
		//music.stop();

		// clearing all the explosions this state creates

		explosion.clear();
	}

}highest_score;