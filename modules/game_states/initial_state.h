
// the initial state of this game home of the game

#pragma once



//extern class serve_state serve;



//extern class highest_score_state highest_score;



extern class game_state game;



class initial_state : public bb::BASE_STATE
{
	str_button start_game, highest_score, quite;

public:

	initial_state() : 
		start_game(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 70, "START GAME", bb::BOTTOM_CENTER),
		highest_score(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 40, "HIGHEST SCORE", bb::BOTTOM_CENTER),
		quite(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 10, "QUIT", bb::BOTTOM_CENTER)
	{}

private:

	//sf::Sound sound;

	//game_data_type i_data;	// created to hold general game data


	void Enter()
	{
		//music.setLoop(true);

		//music.play();
	}


	void Update(double dt)
	{
		auto pos = bb::INPUT.pointer();

		if (start_game.is_clicked(pos.x, pos.y, bb::INPUT.isPressedM(sf::Mouse::Left), bb::INPUT.isReleasedM(sf::Mouse::Left)))
		{
			//sound.setBuffer(sound_buffer[CONFIRM]);

			//sound.play();

			sm.change_to(game);
		}

		if (highest_score.is_clicked(pos.x, pos.y, bb::INPUT.isPressedM(sf::Mouse::Left), bb::INPUT.isReleasedM(sf::Mouse::Left)))
		{
			//sound.setBuffer(sound_buffer[CONFIRM]);

			//sound.play();

			//sm.change_to(serve, &i_data);
		}
		
		if (bb::INPUT.isPressed(sf::Keyboard::Scan::Escape) || quite.is_clicked(pos.x, pos.y, bb::INPUT.isPressedM(sf::Mouse::Left), bb::INPUT.isReleasedM(sf::Mouse::Left)))
		{
			sm.change_to(bb::NULL_STATE);
		}
	}


	void Render()
	{
		start_game.Render();

		highest_score.Render();

		quite.Render();
	}


	void Exit()
	{
		//music.stop();
	}

}initial;