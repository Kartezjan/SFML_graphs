#include "common.h"

sf::Font* font::default_font = nullptr;

sf::Font* font::get_font() 
{
	if (!default_font)
	{
		default_font = new sf::Font;
		if (!default_font->loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
			std::cout << "Couldn't open Arial.ttf";
	}
	return default_font;
}