#pragma once

#include "common.h"
#include "edge.h"
#include "vertex.h"

class engine
{
public:
	engine(int x, int y);
	~engine();
	void run();
	void add_vertex(float x, float y, std::string name);
	void remove_vertex(std::string name);
	void remove_vertex(int index);
	void move_vertex(int index,sf::Vector2f pos);
	void add_edge(vertex* first, vertex* second);
	void remove_edge(int index);
//algorithms (implemented in algorithms.cpp)
	void BFS(vertex& entry_vertex);
	void BFS_step();
	void DFS();
	void DFS_step(vertex*);
private:
	void render_scene();
	void handle_input();

	bool is_vertex_in_area(sf::Vector2f);
	int get_nearest_vertex_index(sf::Vector2f);
	int get_nearest_edge_index(sf::Vector2f);
	int remove_all_selected();
	void remove_attached_edges(vertex& vertice);

	char current_letter;

	sf::Clock mouse_timer;
	sf::Text mouse_mode_info;
	mouse_mode mode;

	sf::RenderWindow window;

	std::vector<vertex*> vertices;
	std::vector<edge> edges;

	std::vector<sf::Drawable*> visuals;
//algorithms
	std::queue<vertex*> bfs_queue;
	bool step_by_step;
	int dfs_time;
};

