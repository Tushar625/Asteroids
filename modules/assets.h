#pragma once

/*
	some assets to be used all over the game
*/


// text and fonts

sf::Font lunchds, Delicatus;

sf::Text small_text, medium_text, large_text;


// particle system effects

bb::Exhaust thrust, reverse_thrust;	// spaceship exhaust

bb::SpaceExplosion explosion;	// space explosion


// heart sprites are used to display remaining lives

vector_sprite_class heart_sprite;


// night sky background for entire game

night_sky_class night_sky;


/*
	primary ecs, that holds all the objects like, spaceship, asteroids and bullets
	
	vector_sprite_class keeps track of position, size and rotation of the objects
*/

using ECS_TYPE = bb::ECS<ECS_ENTITY_TYPE, vector_sprite_class, sf::Vector2f>::C8;

ECS_TYPE ecs;


// the state machine

bb::STATE_MACHINE sm;


/*
	constructor of this class loads and initializes all the assets

	this is also the first piece of code executed in this game
*/

class ASSET_LOADER
{
	public:
	
	ASSET_LOADER()
	{
		srand(time(0));


		
		// setting fonts

		if (!lunchds.loadFromFile("font/lunchds.ttf"))
		{
			std::cout << "Failed to load lunchds font :(\n\n";
		}

		if (!Delicatus.loadFromFile("font/Delicatus.ttf"))
		{
			std::cout << "Failed to load Delicatus font :(\n\n";
		}

		lunchds.setSmooth(false);

		Delicatus.setSmooth(false);

		small_text.setFont(Delicatus);
		
		medium_text.setFont(Delicatus);
		
		large_text.setFont(lunchds);

		small_text.setCharacterSize(SMALL_FONT_SIZE);
		
		medium_text.setCharacterSize(MEDIUM_FONT_SIZE);
			
		large_text.setCharacterSize(LARGE_FONT_SIZE);


		
		// setting thrust and reverse thrust

		thrust.setGap(5);

		thrust.setMaxVelocity(300);

		thrust.setAngle(15);


		reverse_thrust.setGap(5);

		reverse_thrust.setMaxVelocity(300);

		reverse_thrust.setAngle(15);



		// creating the heart sprite, which is just a miniature space ship

		float heart_size = SPACESHIP_SIZE / 2;

		heart_sprite.set_local_size_and_points(
			heart_size,
			sf::Vector2f{ heart_size, heart_size / 2 },
			sf::Vector2f{ 0, 0 },
			sf::Vector2f{ heart_size / 4, heart_size / 2 },
			sf::Vector2f{ 0, heart_size },
			sf::Vector2f{ heart_size, heart_size / 2 }
		);

		// make the spaceship point up

		heart_sprite.setRotation(-90);
	}
}asset_loader;