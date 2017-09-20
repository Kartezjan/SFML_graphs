#include "vertex.h"


vertex::vertex(int id, float x, float y, std::string name) : circle(SIZE), display_name(name, *font::get_font(),30)
{
	selected = false;
	circle.setPosition(x, y);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(2.f);
	this->name = name;
	this->id = id;
	display_name.setPosition(x + SIZE/5*3,y + SIZE/4);
	display_name.setFillColor(sf::Color::Black);


	position = sf::Vector2f(x + SIZE, y + SIZE);
	reset();
	display_distance = sf::Text(std::to_string(distance), *font::get_font(), 15);
	display_distance.setPosition(x + SIZE / 5 * 3, y - SIZE / 5 * 4);
	display_distance.setFillColor(sf::Color::Black);
	d = 0; f = 0;
}


void vertex::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(circle, states);
	target.draw(display_name, states);
	if (show_distance)
		target.draw(display_distance);
}

std::string vertex::get_name() const
{
	return name;
}

sf::Vector2f vertex::get_position() const
{
	return position;
}

std::vector<vertex*>& vertex::get_adjacents()
{
	return adjacents; 
}

int vertex::get_distance() const
{
	 return distance;
}

vertex * vertex::get_parent() const
{
	return parent;
}

void vertex::toggle_select()
{
	if(!selected)
	{
		selected = true;
		circle.setOutlineColor(sf::Color::Red);
	}
	else
	{
		selected = false;
		circle.setOutlineColor(sf::Color::Black);
	}
}

bool vertex::is_selected() const
{
	 return selected;
}

void vertex::set_position(sf::Vector2f pos)
{
	circle.setPosition(sf::Vector2f(pos.x - SIZE, pos.y - SIZE));
	position = pos;
	display_name.setPosition(pos.x - SIZE*2/5, pos.y - SIZE*3/4);
	display_distance.setPosition(pos.x - SIZE*2/5, pos.y - 2*SIZE);
}

void vertex::set_color(vertex_color new_color)
{
	color = new_color;
	switch (color)
	{
	case vertex_color::white:
		circle.setFillColor(sf::Color::White);
		display_name.setFillColor(sf::Color::Black);
		break;
	case vertex_color::gray:
		circle.setFillColor(sf::Color(128,128,128));
		display_name.setFillColor(sf::Color::White);
		break;
	case vertex_color::black:
		circle.setFillColor(sf::Color::Black);
		display_name.setFillColor(sf::Color::White);
		break;
	}
}

void vertex::set_distance(int dis)
{
	distance = dis; 
	display_distance.setString(std::to_string(dis));
}

void vertex::set_parent(vertex * other)
{
	 parent = other;
}

void vertex::toggle_distance_display(bool set)
{
 show_distance = set;
}

vertex_color vertex::get_color() const
{
	return color;
}

void vertex::add_adjacent(vertex* adj)
{
	adjacents.push_back(adj);
}

void vertex::set_d(int new_d)
{
	d = new_d;
	dfs_display(); 
}

void vertex::set_f(int new_f)
{
 f = new_f; 
 dfs_display();
}

void vertex::dfs_display()
{
	std::string to_display = std::to_string(d);
	to_display.append("/");
	to_display.append(std::to_string(f));
	display_distance.setString(to_display);
}

void vertex::reset()
{
	color = vertex_color::white;
	distance = -1;
	parent = nullptr;
	show_distance = false;
	d = -1; f = -1;
	display_distance.setString("INF");
}

bool vertex::has_edge(vertex * vertex)
{
	auto found = std::find(adjacents.begin(), adjacents.end(), vertex);
	if(found == adjacents.end())
		return false;
	return true;
}
