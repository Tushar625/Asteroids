#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"modules/requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int bb::set_antialiashing()
{
	return 0;
}



inline bool bb::Game::Create()
{
	// setting window title

	bb::WINDOW.setTitle("Astroids");

	// setting window size and poxel size

	bb::WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	auto this_view = WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	WINDOW.setView(this_view);

	// other settings

	bb::MY_GAME.set_fps(60);

	// extra

	space_ship::create();

	for(int i = 1; i <= 5; i++)
	{
		asteroid::create();
	}

	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		return STOP_GAME_LOOP;

	// ~~~~ [write your statements here] ~~~~

	for (size_t i = 0; i < ecs.entity_count();)
	{
		auto& entity = ecs.entity(i);

		switch (entity.get<ENTITY_TYPE>())
		{
			case SPACESHIP_ENTITY:

				space_ship::update(entity, dt);

				if (bb::INPUT.isPressed(sf::Keyboard::Scan::Enter))
				{
					// create bullet

					bullet::create(entity.get<SPRITE>());
				}

				break;

			case ASTEROID_ENTITY:

				asteroid::update(entity, dt); break;

			case BULLET_ENTITY:

				if (bullet::update(entity, dt))
				{
					continue;
				}

				break;
		}

		i++;
	}

	//bullet.update(dt);

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Render()
{
	small_text.setString("Fps: " + std::to_string(bb::MY_GAME.get_fps()));

	bb::WINDOW.draw(small_text);

	for (size_t i = 0; i < ecs.entity_count(); i++)
	{
		auto& entity = ecs.entity(i);

		switch (entity.get<ENTITY_TYPE>())
		{
			case SPACESHIP_ENTITY:

				space_ship::render(entity); break;

			case ASTEROID_ENTITY:

				asteroid::render(entity); break;

			case BULLET_ENTITY:

				bullet::render(entity); break;
		}
	}

	//bullet.render();
}