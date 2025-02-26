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

	srand(time(0));

	bb::MY_GAME.set_fps(30);

	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		return STOP_GAME_LOOP;

	// ~~~~ [write your statements here] ~~~~

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Render()
{
	small_text.setString("Fps: " + std::to_string(bb::MY_GAME.get_fps()));

	bb::WINDOW.draw(small_text);

	
}