#pragma once

/*
	some assets to be used all over the game
*/


// text and fonts

sf::Font lunchds, Delicatus;

sf::Text small_text, medium_text, large_text;


// sounds

sf::Music rocket_engine_sound, space_background_music, initial_background_music, score_background_music;

sf::SoundBuffer asteroid_blast_sound, cannon_sound, ship_hit_sound, warning_sound, ship_explosion_sound, firecracker_sound, button_sound, distress_sound;


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



		// loading sounds

		if (!rocket_engine_sound.openFromFile("sound/rocket exhaust.wav"))
		{
			std::cout << "can't load rocket exhaust.wav\n";
		}

		rocket_engine_sound.setLoop(true);

		if (!space_background_music.openFromFile("sound/space bg.mp3"))
		{
			std::cout << "can't load space bg.mp3\n";
		}

		space_background_music.setLoop(true);

		space_background_music.setVolume(25);

		if (!initial_background_music.openFromFile("sound/initial bg.wav"))
		{
			std::cout << "can't load initial bg.wav\n";
		}

		initial_background_music.setLoop(true);

		initial_background_music.setVolume(25);

		if (!score_background_music.openFromFile("sound/score bg.mp3"))
		{
			std::cout << "can't load score bg.mp3\n";
		}

		score_background_music.setLoop(true);

		score_background_music.setVolume(25);


		if (!asteroid_blast_sound.loadFromFile("sound/asteroid blast.mp3"))
		{
			std::cout << "can't load asteroid blast.mp3\n";
		}

		if (!cannon_sound.loadFromFile("sound/cannon sound.mp3"))
		{
			std::cout << "can't load cannon sound.mp3\n";
		}

		if (!ship_hit_sound.loadFromFile("sound/ship hit.mp3"))
		{
			std::cout << "can't load ship hit.mp3\n";
		}

		if (!warning_sound.loadFromFile("sound/warning.wav"))
		{
			std::cout << "can't load warning.wav\n";
		}

		if (!ship_explosion_sound.loadFromFile("sound/ship explosion warning.mp3"))
		{
			std::cout << "can't load ship explosion warning.mp3\n";
		}

		if (!firecracker_sound.loadFromFile("sound/firecracker.wav"))
		{
			std::cout << "can't load firecracker.wav\n";
		}

		if (!button_sound.loadFromFile("sound/button.wav"))
		{
			std::cout << "can't load button.wav\n";
		}

		if (!distress_sound.loadFromFile("sound/distress-signal.mp3"))
		{
			std::cout << "can't load distress-signal.mp3\n";
		}

		
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