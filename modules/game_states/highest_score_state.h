
// the initial state of this game home of the game

#pragma once



class highest_score_state : public bb::BASE_STATE
{
	sf::Text main_text_line1, main_text_line2;

	double delay;

	int count;

public:

	void init(int score)
	{
		main_text_line1 = medium_text;

		main_text_line1.setString(std::to_string(score));

		center_origin(main_text_line1);

		main_text_line1.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f - 12);


		main_text_line2 = medium_text;

		main_text_line2.setString("!! New High Score !!");

		center_origin(main_text_line2);

		main_text_line2.setPosition(VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f + 12);
	}

private:

	//sf::Sound sound;


	void Enter()
	{
		count = 20;

		delay = -1;
	}


	void Update(double dt)
	{
		if (count)
		{
			if (delay < 0)
			{
				explosion.create(sf::Vector2f(rand() % VIRTUAL_WIDTH, rand() % VIRTUAL_HEIGHT), sf::Vector2f(0, 0), sf::Color(rand() % 256, rand() % 256, rand() % 256), 10000, 80 + rand() % 100, 1 + rand() % 5);

				delay = (rand() % 1000) / 1000.0;

				--count;
			}
		}

		delay -= dt;

		explosion.update(dt);

		if (explosion.empty())
		{
			sm.change_to(initial);
		}
	}


	void Render()
	{
		bb::WINDOW.draw(explosion);

		bb::WINDOW.draw(main_text_line1);

		bb::WINDOW.draw(main_text_line2);
	}


	void Exit()
	{
		//music.stop();
	}

}highest_score;