#pragma once

sf::Font font;

sf::Text small_text, medium_text, large_text;

bb::Exhaust thrust, reverse_thrust;

bb::SpaceExplosion explosion;

using ECS_TYPE = bb::ECS<ECS_ENTITY_TYPE, vector_sprite_class, sf::Vector2f>::C8;

ECS_TYPE ecs;

bb::STATE_MACHINE sm;



class ASSET_LOADER
{
	public:
	
	ASSET_LOADER()
	{
		srand(time(0));


		if (!font.loadFromFile("font/font.ttf"))
		{
			std::cout << "Failed to load font :(\n\n";
		}

		font.setSmooth(false);

		small_text.setFont(font); 
		
		medium_text.setFont(font);
		
		large_text.setFont(font);

		small_text.setCharacterSize(SMALL_FONT_SIZE);
		
		medium_text.setCharacterSize(MEDIUM_FONT_SIZE);
			
		large_text.setCharacterSize(LARGE_FONT_SIZE);


		thrust.setGap(5);

		thrust.setMaxVelocity(300);

		thrust.setAngle(15);


		reverse_thrust.setGap(5);

		reverse_thrust.setMaxVelocity(300);

		reverse_thrust.setAngle(15);
	}
}asset_loader;