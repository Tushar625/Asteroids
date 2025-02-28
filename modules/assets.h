#pragma once

sf::Font font;

sf::Text small_text, medium_text, large_text;



class ASSET_LOADER
{
	public:
	
	ASSET_LOADER()
	{
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
	}
}asset_loader;