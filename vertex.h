#pragma once

#include "common.h"


class vertex : public visual_object
{
public:
	static object_type type;
	vertex(int id, float x, float y, std::string name);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int get_id() const { return id; }
	std::string get_name() const;
	sf::Vector2f get_position() const;
	std::vector<vertex*>& get_adjacents();
	int get_distance() const;
	vertex* get_parent() const;
	void set_position(sf::Vector2f);
	void set_color(vertex_color new_color);
	void set_distance(int dis);
	void set_parent(vertex* other);
	void toggle_distance_display(bool set);
	vertex_color get_color() const;
	void toggle_select();
	bool is_selected() const;
	void add_adjacent(vertex*);
	void set_d(int new_d);
	void set_f(int new_f);
	void dfs_display();
	void reset(); //changes algoritmic variables to default.
	bool has_edge(vertex* vertex);
	//void update();
private:
	int id;
	sf::Vector2f position;
	sf::CircleShape circle;
	sf::Text display_name;
	sf::Text display_distance;
	bool show_distance;
	std::string name;
	bool selected;
	std::vector<vertex*> adjacents;
	//for algorithmic purposes
	vertex_color color;
	int distance;
	vertex* parent;
	int d, f;
};
