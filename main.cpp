#define SET_ANTIALIASHING	// this macro allows you to set antialiashing

#include"modules/requirements.h"

// the value returned by this function will be set as the value for antialiashing

unsigned int bb::set_antialiashing()
{
	return 0;
}

sf::Vector2f velocity = { 0, 0 }, accn;

float ACCN = 100, daccn = 500;

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

	// extra

	/*auto pt = space_ship.getPosition();

	std::cout << pt.x << ", " << pt.y << "\n\n";

	auto dir = space_ship.getRotation();

	std::cout << dir;*/

	space_ship.setOrigin(sf::Vector2f(10, 10));

	space_ship.setPosition(sf::Vector2f(100, 100));

	
	rocket_exhaust.setGap(5);

	rocket_exhaust.setMaxVelocity(300);

	rocket_exhaust.setAngle(15);


	reverse_thrust.setGap(5);

	reverse_thrust.setMaxVelocity(300);

	reverse_thrust.setAngle(15);

	return SUCCESS;
}



inline bool bb::Game::Update(double dt)
{
	// exit

	if (bb::INPUT.isClosed() || bb::INPUT.isPressed(sf::Keyboard::Scan::Escape))
		return STOP_GAME_LOOP;

	// ~~~~ [write your statements here] ~~~~

	if (bb::INPUT.isHeld(sf::Keyboard::Scan::Left))
	{
		space_ship.rotate(-200 * dt);
	}

	if (bb::INPUT.isHeld(sf::Keyboard::Scan::Right))
	{
		space_ship.rotate(200 * dt);

		//accn = { cos(space_ship.getRotation()) * ACCN, sin(space_ship.getRotation()) * ACCN };
	}

	accn = { cos(std::numbers::pi_v<float> / 180 * space_ship.getRotation()) * ACCN, sin(std::numbers::pi_v<float> / 180 * space_ship.getRotation()) * ACCN };

	rocket_exhaust.setSource(space_ship.getPosition());

	if (bb::INPUT.isHeld(sf::Keyboard::Scan::Up))
	{
		rocket_exhaust.setDirection(space_ship.getRotation() + 180);

		rocket_exhaust.spray();

		// propulsion

		velocity.x += accn.x * dt;

		velocity.y += accn.y * dt;
	}

	reverse_thrust.setSource(space_ship.getPosition());

	if (bb::INPUT.isHeld(sf::Keyboard::Scan::Down))
	{
		reverse_thrust.setDirection(space_ship.getRotation() + 45);

		reverse_thrust.spray();

		reverse_thrust.setDirection(space_ship.getRotation() - 45);

		reverse_thrust.spray();

		// propulsion

		velocity.x -= accn.x * dt;

		velocity.y -= accn.y * dt;
	}

	space_ship.move(sf::Vector2f(velocity.x * dt, velocity.y * dt));

	rocket_exhaust.update(dt);

	reverse_thrust.update(dt);

	// wraping

	auto pos = space_ship.getPosition();

	if (pos.x < -10)
	{
		pos.x = VIRTUAL_WIDTH + 10;
	}
	else if (pos.x > VIRTUAL_WIDTH + 10)
	{
		pos.x = -10;
	}

	if (pos.y < -10)
	{
		pos.y = VIRTUAL_HEIGHT + 10;
	}
	else if (pos.y > VIRTUAL_HEIGHT + 10)
	{
		pos.y = -10;
	}

	if(pos != space_ship.getPosition())
	{
		space_ship.setPosition(pos);
	}

	return !STOP_GAME_LOOP;
}



inline void bb::Game::Render()
{
	small_text.setString("Fps: " + std::to_string(bb::MY_GAME.get_fps()));

	bb::WINDOW.draw(small_text);

	bb::WINDOW.draw(space_ship);

	bb::WINDOW.draw(rocket_exhaust);

	bb::WINDOW.draw(reverse_thrust);
}