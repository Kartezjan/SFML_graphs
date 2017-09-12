#include "edge.h"


void edge::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(line,2,sf::Lines,states);
}

edge::edge(vertex* a, vertex* b)
{
	first = a;
	second = b;
	line[0] = a->get_position();
	line[1] = b->get_position();
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Cyan;
}

void edge::set_first_pos(sf::Vector2f new_pos)
{
	line[0].position = new_pos;
}

void edge::set_second_pos(sf::Vector2f new_pos)
{
	line[1].position = new_pos;
}
