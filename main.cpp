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

	bb::WINDOW.setTitle("Astroids (Clone) V1.0.0");

	// setting window position

	bb::WINDOW.setPosition(sf::Vector2i(300, 150));

	// setting window size and poxel size

	bb::WINDOW.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

	auto this_view = WINDOW.getView();

	this_view.reset(sf::FloatRect(0, 0, VIRTUAL_WIDTH, VIRTUAL_HEIGHT));

	WINDOW.setView(this_view);

	// other settings

	bb::MY_GAME.set_fps(60);

	// other initializations

	sm.change_to(initial);

	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || sm.null_state())
		return STOP_GAME_LOOP;

	// state machine and night sky background update

	sm.Update(dt);

	night_sky.update(dt);
	
	return !STOP_GAME_LOOP;
}



inline void bb::Game::Render()
{
	// state machine and night sky background render

	bb::WINDOW.draw(night_sky);

	sm.Render();
}