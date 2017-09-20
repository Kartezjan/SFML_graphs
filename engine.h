#pragma once

#include "common.h"
#include "edge.h"
#include "vertex.h"
#include <memory>
#

class engine
{
public:
	engine(int x, int y);
	void run();
	void clear();
	void add_vertex(float x, float y, std::string name);
	void remove_vertex(std::string name);
	void remove_vertex(int index);
	vertex* get_vertex(int id);
	void move_vertex(int index,sf::Vector2f pos);
	void add_edge(vertex* first, vertex* second);
	void remove_edge(int index);
// algorithms (implemented in algorithms.cpp)
	void BFS(vertex& entry_vertex);
	void BFS_step();
	void DFS();
	void DFS_step(vertex*);
// save/load
	void save(std::string filename);
	void load(std::string filename);
private:
	void add_vertex(int id, float x, float y, std::string name);
	void render_scene();
	void handle_input();

	bool is_vertex_in_area(sf::Vector2f);
	int get_nearest_vertex_index(sf::Vector2f);
	int get_nearest_edge_index(sf::Vector2f);
	int remove_all_selected();
	void remove_attached_edges(vertex& vertice);

	char current_letter;
	int current_id;

	sf::Clock mouse_timer;
	sf::Text mouse_mode_info;
	mouse_mode mode;

	sf::RenderWindow window;

	std::vector<std::unique_ptr< vertex> > vertices;
	std::vector<edge> edges;

	std::vector<std::unique_ptr< sf::Drawable> > visuals;
// algorithms
	std::queue<vertex*> bfs_queue;
	bool step_by_step;
	int dfs_time;
};

