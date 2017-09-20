#include "engine.h"

void engine::load(std::string filename)
{
	std::fstream file;
	file.open(filename, std::fstream::in);
	if (!file.is_open())
	{
		std::cout << "Coudn't open " << filename << std::endl;
		return;
	}
	clear();
	int vertex_count;
	file >> vertex_count;
	for (int i = 0; i < vertex_count; ++i)
	{
		int id;
		float x, y;
		std::string name;
		file >> id >> name >> x >> y;
		add_vertex(id, x, y, name);
	}
	for (int i = 0; i < vertex_count; ++i)
	{
		int id, current;
		std::string line;
		std::getline(file,line);
		std::stringstream ss(line);
		ss >> id;
		while (ss >> current)
		{
			add_edge(get_vertex(current), get_vertex(id));
		}
	}
	file.close();
}

void engine::save(std::string filename)
{
	std::fstream file;
	file.open(filename, std::fstream::out | std::fstream::trunc);
	if (!file.is_open())
	{
		std::cout << "Coudn't open " << filename << std::endl;
		return;
	}
	file << vertices.size() << std::endl;
	for (auto& vertex : vertices)
	{
		file << vertex->get_id() << " "  << vertex->get_name() << " " << vertex->get_position().x << " " << vertex->get_position().y << std::endl;
	}
	for (auto& vertex : vertices)
	{
		file << vertex->get_id() << " ";
		for (auto adj : vertex->get_adjacents())
			file << adj->get_id() << " ";
		file << std::endl;
	}
	file.close();
}