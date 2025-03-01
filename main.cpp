#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"modules/requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int bb::set_antialiashing()
{
	return 0;
}



vector_sprite_class asteroid;

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

	bb::MY_GAME.set_fps(60);

	// extra

	// asteroid 1

	/*asteroid.set_local_points(
		sf::Vector2f(2, 0),
		sf::Vector2f(8, 2),
		sf::Vector2f(13, 0),
		sf::Vector2f(11, 7),
		sf::Vector2f(20, 3),

		sf::Vector2f(17, 11),
		sf::Vector2f(20, 11),
		sf::Vector2f(16, 17),
		sf::Vector2f(17, 18),
		sf::Vector2f(10, 20),

		sf::Vector2f(6, 17),
		sf::Vector2f(0, 20),
		sf::Vector2f(2, 12),
		sf::Vector2f(0, 8),
		sf::Vector2f(3, 5),
		sf::Vector2f(2, 0)
	);*/

	// asteroid 2

	/*asteroid.set_local_points(
		sf::Vector2f(5, 0),
		sf::Vector2f(10, 3),
		sf::Vector2f(15, 0),
		sf::Vector2f(20, 8),
		sf::Vector2f(17, 13),

		sf::Vector2f(20, 15),
		sf::Vector2f(15, 15),
		sf::Vector2f(15, 20),
		sf::Vector2f(10, 20),
		sf::Vector2f(5, 15),

		sf::Vector2f(0, 15),
		sf::Vector2f(5, 10),
		sf::Vector2f(0, 10),
		sf::Vector2f(5, 0)
	);*/

	// asteroid 3

	/*asteroid.set_local_points(
		sf::Vector2f(0, 0),
		sf::Vector2f(5, 2),
		sf::Vector2f(12, 1),
		sf::Vector2f(17, 3),
		sf::Vector2f(15, 5),

		sf::Vector2f(20, 5),
		sf::Vector2f(15, 15),
		sf::Vector2f(20, 10),
		sf::Vector2f(18, 20),
		sf::Vector2f(10, 17),

		sf::Vector2f(2, 20),
		sf::Vector2f(3, 15),
		sf::Vector2f(0, 10),
		sf::Vector2f(3, 5),

		sf::Vector2f(0, 0)
	);*/

	// asteroid 4

	asteroid.set_local_points(
		sf::Vector2f(3, 3),
		sf::Vector2f(10, 0),
		sf::Vector2f(17, 5),
		sf::Vector2f(20, 3),
		sf::Vector2f(19, 8),

		sf::Vector2f(20, 12),
		sf::Vector2f(15, 14),
		sf::Vector2f(18, 17),
		sf::Vector2f(12, 20),
		sf::Vector2f(10, 17),
		
		sf::Vector2f(1, 20),
		sf::Vector2f(10, 10),
		sf::Vector2f(2, 15),
		sf::Vector2f(0, 10),
		sf::Vector2f(3, 3)
	);

	asteroid.setPosition(sf::Vector2f(200, 200));

	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		return STOP_GAME_LOOP;

	// ~~~~ [write your statements here] ~~~~

	space_ship.update(dt);

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Render()
{
	small_text.setString("Fps: " + std::to_string(bb::MY_GAME.get_fps()));

	bb::WINDOW.draw(small_text);

	space_ship.render();

	bb::WINDOW.draw(asteroid);
}