
// the message state of this game, displays the victory and defeat message

#pragma once



class game_over_state : public bb::BASE_STATE
{
	public:

	sf::Text main_message_text, score_text, complimentary_message_text, input_text;

	void init(int score, int highest_score)
	{
		// main text

		main_message_text = large_text;

		main_message_text.setString("GAME OVER");

		int xout, yout, boxh = VIRTUAL_HEIGHT / 1.7;

		/*
			imagine a box placed in the center of the screen with height
			boxh and width same as main message

			xout and yout represents the top left point this box
		*/

		bb::to_top_left(
			xout, yout,
			VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2,
			boxh, (int)main_message_text.getLocalBounds().width,
			bb::CENTER
		);

		// place the main message in the box, touching its top border

		main_message_text.setPosition(sf::Vector2f(xout, yout));

		// score

		score_text = medium_text;

		score_text.setFillColor(sf::Color::White);

		score_text.setString(std::to_string(score));

		int tempx, tempy;

		// place the center of score text 10 pixels up the center of the box

		bb::to_top_left(
			tempx, tempy,
			VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 - 10,
			MEDIUM_FONT_SIZE, (int)score_text.getLocalBounds().width,
			bb::CENTER
		);

		score_text.setPosition(sf::Vector2f(tempx, tempy));

		// cmp text

		complimentary_message_text = medium_text;

		complimentary_message_text.setFillColor(sf::Color::White);

		if(score > highest_score)
		{
			complimentary_message_text.setString("NEW HIGHEST SCORE");
		}
		else
		{
			complimentary_message_text.setString("HIGHEST SCORE: " + std::to_string(highest_score));
		}

		// place the center of comp message 10 pixels down the center of the box

		bb::to_top_left(
			tempx, tempy,
			VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 10,
			MEDIUM_FONT_SIZE, (int)complimentary_message_text.getLocalBounds().width,
			bb::CENTER
		);

		complimentary_message_text.setPosition(sf::Vector2f(tempx, tempy));

		// input text

		input_text = medium_text;

		input_text.setString("Press 'Enter' to Return to Home");

		bb::to_top_left(
			xout, yout,
			VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + boxh / 2,
			MEDIUM_FONT_SIZE, (int)input_text.getLocalBounds().width,
			bb::BOTTOM_CENTER
		);

		input_text.setPosition(sf::Vector2f(xout, yout));

		/*
											Screen Width
			|----------------------------------------------------------------------| -
																						|
																						|
								|=========MAIN MESSAGE=========|                     |
								|                              |                     |
								|                              |                     |
								|                              |                     |
								|          SCORE TEXT          |                     |
								|                              |                     | Screen Height
								|         COMP MESSAGE         |                     |
								|                              |                     |
								|                              |                     |
					BUTTON1     |______________________________|     BUTTON2         |
																						|
																						|
																						-
		*/
	}


	private:


	//sf::Sound sound;


	void Enter()
	{
		
	}


	void Update(double dt)
	{
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
		{
			//sound.setBuffer(sound_buffer[SELECT]);

			//sound.play();

			sm.change_to(initial);
		}
	}


	void Render()
	{
		// render the buttons and the messages

		bb::WINDOW.draw(main_message_text);

		bb::WINDOW.draw(score_text);

		bb::WINDOW.draw(complimentary_message_text);

		bb::WINDOW.draw(input_text);
	}


	void Exit()
	{
		
	}

}game_over;