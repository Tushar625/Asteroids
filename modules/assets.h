#pragma once

sf::Font Orbitron_font, ShareTechMono_font;

sf::Text small_text, medium_text, large_text;

bb::Exhaust thrust, reverse_thrust;

bb::SpaceExplosion explosion;

vector_sprite_class heart_sprite;

night_sky_class night_sky;

using ECS_TYPE = bb::ECS<ECS_ENTITY_TYPE, vector_sprite_class, sf::Vector2f>::C8;

ECS_TYPE ecs;

bb::STATE_MACHINE sm;



class ASSET_LOADER
{
	public:
	
	ASSET_LOADER()
	{
		srand(time(0));

		if (!Orbitron_font.loadFromFile("font/lunchds.ttf"))
		{
			std::cout << "Failed to load Orbitron_font :(\n\n";
		}

		if (!ShareTechMono_font.loadFromFile("font/Delicatus.ttf"))
		{
			std::cout << "Failed to load ShareTechMono_font :(\n\n";
		}

		Orbitron_font.setSmooth(false);

		ShareTechMono_font.setSmooth(false);

		small_text.setFont(ShareTechMono_font);
		
		medium_text.setFont(ShareTechMono_font);
		
		large_text.setFont(Orbitron_font);

		small_text.setCharacterSize(SMALL_FONT_SIZE);
		
		medium_text.setCharacterSize(MEDIUM_FONT_SIZE);
			
		large_text.setCharacterSize(LARGE_FONT_SIZE);


		thrust.setGap(5);

		thrust.setMaxVelocity(300);

		thrust.setAngle(15);


		reverse_thrust.setGap(5);

		reverse_thrust.setMaxVelocity(300);

		reverse_thrust.setAngle(15);

		float heart_size = SPACESHIP_SIZE / 2;

		heart_sprite.set_local_size_and_points(
			heart_size,
			sf::Vector2f{ heart_size, heart_size / 2 },
			sf::Vector2f{ 0, 0 },
			sf::Vector2f{ heart_size / 4, heart_size / 2 },
			sf::Vector2f{ 0, heart_size },
			sf::Vector2f{ heart_size, heart_size / 2 }
		);

		heart_sprite.setRotation(-90);

		heart_sprite.setOrigin(0, 0);
	}
}asset_loader;