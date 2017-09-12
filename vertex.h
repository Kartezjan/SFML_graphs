#pragma once

#include "common.h"


class vertex : public visual_object
{
public:
	static object_type type;
	vertex(float x, float y, std::string name);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::string get_name() const { return name; }
	sf::Vector2f get_position() const { return position; }
	std::vector<vertex*>& get_adjascents() { return adjascents; }
	int get_distance() const { return distance; }
	vertex* get_parent() const { return parent; }
	void set_position(sf::Vector2f);
	void set_color(vertex_color new_color);
	void set_distance(int dis) { distance = dis; display_distance.setString(std::to_string(dis)); }
	void set_parent(vertex* other) { parent = other; }
	void toggle_distance_display(bool set) { show_distance = set; };
	vertex_color get_color() const { return color; }
	void toggle_select();
	bool is_selected() const { return selected; }
	void add_adjascent(vertex*);
	void set_d(int new_d) { d = new_d; dfs_display(); }
	void set_f(int new_f) { f = new_f; dfs_display(); };
	void dfs_display();
	void reset(); //changes algoritmic variables to default.
	//void update();
private:
	sf::Vector2f position;
	sf::CircleShape circle;
	sf::Text display_name;
	sf::Text display_distance;
	bool show_distance;
	std::string name;
	bool selected;
	std::vector<vertex*> adjascents;
	//for algorithmic purposes
	vertex_color color;
	int distance;
	vertex* parent;
	int d, f;
};
