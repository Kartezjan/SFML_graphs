#include "engine.h"

void engine::BFS(vertex& entry)
{
	for (auto& vertex : vertices)
	{
		vertex->reset();
		vertex->toggle_distance_display(true);
	}
	entry.set_color(vertex_color::gray);
	entry.set_distance(0);
	bfs_queue = {};
	bfs_queue.push(&entry);
	if (!step_by_step)
		while (!bfs_queue.empty())
			BFS_step();
}

void engine::BFS_step()
{
	if (bfs_queue.empty())
		return;
	auto u = bfs_queue.front();
	bfs_queue.pop();
	for(auto adj : u->get_adjacents())
	{
		if(adj->get_color() == vertex_color::white)
		{
			adj->set_color(vertex_color::gray);
			adj->set_distance(u->get_distance() + 1);
			adj->set_parent(u);
			bfs_queue.push(adj);
		}
	}
	u->set_color(vertex_color::black);
}

void engine::DFS()
{
	for (auto& vertex : vertices)
	{
		vertex->reset();
		vertex->toggle_distance_display(true);
	}
	dfs_time = 0;
	bfs_queue = {};
	for (auto& vertex : vertices)
		if (vertex->get_color() == vertex_color::white)
			DFS_step(vertex.get());
}

void engine::DFS_step(vertex* a)
{
	a->set_d(++dfs_time);
	a->set_color(vertex_color::gray);
	for(auto vertex : a->get_adjacents())
		if(vertex->get_color() == vertex_color::white)
		{
			vertex->set_parent(a);
			DFS_step(vertex);
		}
	a->set_color(vertex_color::black);
	a->set_f(++dfs_time);

}
