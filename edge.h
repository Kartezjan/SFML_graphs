#pragma once

#include "common.h"
#include "vertex.h"

class edge : public visual_object
{
public:
	edge(vertex*, vertex*);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	vertex* get_first() const { return first; }
	vertex* get_second() const { return second; }
	void set_first_pos(sf::Vector2f new_pos);
	void set_second_pos(sf::Vector2f new_pos);
private:
	vertex* first;
	vertex* second;
	sf::Vertex line[2];
};
