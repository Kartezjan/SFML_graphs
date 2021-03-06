#include "engine.h"


engine::engine(int x, int y) : window(sf::VideoMode(x,y), "graphs"), mouse_mode_info("INSERT MODE", *font::get_font(),12)
{
	mode = mouse_mode::insert;
	current_letter = 'A';
	current_id = 0;
	mouse_mode_info.setPosition(0, 0);
	mouse_mode_info.setFillColor(sf::Color::Red);
	visuals.push_back(std::unique_ptr<sf::Drawable>(&mouse_mode_info) );
	step_by_step = false;
	dfs_time = 0;
}

bool engine::is_vertex_in_area(sf::Vector2f pos)
{
	for(const auto& vertex : vertices)
	{
		auto vertex_pos = vertex->get_position();
		if (distance(pos, vertex_pos) < SIZE*2)
			return true;
	}
	return false;
}

int engine::get_nearest_vertex_index(sf::Vector2f pos)
{
	for(size_t i = 0; i < vertices.size(); ++i)
	{
		const auto current_pos = vertices[i]->get_position();
		const auto current_distance = distance(pos, current_pos);
		if (current_distance < SIZE)
			return i;
	}
	return -1;
}


int engine::get_nearest_edge_index(sf::Vector2f pos)
{
	for(size_t i = 0; i < edges.size(); ++i)
	{
		const auto current_distance =  distance_beetwen_line(pos, edges[i].get_first()->get_position(), edges[i].get_second()->get_position());
		if (current_distance < 15) //ARBITRARY MAGIC NUMBER
			return i;
	}
	return -1;
}


void engine::handle_input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		mode = mouse_mode::insert;
		mouse_mode_info.setString(strings::insert);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		mode = mouse_mode::remove;
		mouse_mode_info.setString(strings::remove);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		mode = mouse_mode::select;
		mouse_mode_info.setString(strings::select);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		mode = mouse_mode::move;
		mouse_mode_info.setString(strings::move);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mode = mouse_mode::edge;
		mouse_mode_info.setString(strings::edges);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		mode = mouse_mode::bfs;
		mouse_mode_info.setString(strings::bfs);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		for (auto& vertice : vertices)
			if (vertice->is_selected())
				vertice->toggle_select();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (auto& vertice : vertices)
			if (!vertice->is_selected())
				vertice->toggle_select();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
	{
		if (mouse_timer.getElapsedTime().asMilliseconds() > 200)
		{
			save("saved.dat");
			mouse_timer.restart();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
	{
		if (mouse_timer.getElapsedTime().asMilliseconds() > 200)
		{
			load("saved.dat");
			mouse_timer.restart();
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		remove_all_selected();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && mouse_timer.getElapsedTime().asMilliseconds() > 200 )
	{
		BFS_step();
		mouse_timer.restart();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		DFS();
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		const auto mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if(mode == mouse_mode::move)
		{	
			const int index = get_nearest_vertex_index(mouse_pos);
			if(index != -1)
			{
				move_vertex(index, mouse_pos);
			}
		}
		else if (mouse_timer.getElapsedTime().asMilliseconds() > 200)
		{
			if (mode == mouse_mode::insert)
			{
				if (!is_vertex_in_area(mouse_pos))
				{
					std::string label;
					label.push_back(current_letter);
					add_vertex(sf::Mouse::getPosition(window).x - SIZE, sf::Mouse::getPosition(window).y - SIZE, label);
					++current_letter;
					if (current_letter > 'Z')
						current_letter = 'A';
				}
			}
			else
			{
				const int index = get_nearest_vertex_index(mouse_pos);
				if (index != -1)
				{
					if (mode == mouse_mode::remove)
						remove_vertex(index);

					else if (mode == mouse_mode::select)
						vertices[index]->toggle_select();
					else if (mode == mouse_mode::edge)
					{
						vertex* second = vertices[index].get();
						for (auto& vertex : vertices)
						{
							if (second == vertex.get())
								continue;//will be handled later, when directed graphs are implemented.
							if (vertex->is_selected())
							{
								add_edge(vertex.get(), second);
								vertex->toggle_select();
							}
						}
					}
					else if (mode == mouse_mode::bfs)
						BFS(*vertices[index]);
				}
				else if (mode == mouse_mode::remove)
				{
					const int edge_index = get_nearest_edge_index(mouse_pos);
					if (edge_index != -1)
						remove_edge(edge_index);
				}
			}
			mouse_timer.restart();
		}
	}
}

void engine::run()
{
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		handle_input();

		window.clear(sf::Color::White);
		render_scene();
		window.display();
		sf::sleep(sf::milliseconds(30)); //reduces CPU usage
	}
}

void engine::clear()
{
	edges.clear();
	vertices.clear();
}

void engine::render_scene()
{
	for(const auto& object : edges) 
		window.draw(object);

	for (const auto& object : vertices)
		window.draw(*object);
	for (const auto& object : visuals)
		window.draw(*object.get());
}

void engine::add_vertex(float x, float y, std::string name)
{
	vertices.emplace_back(new vertex(current_id, x, y, name));
	++current_id;
}

void engine::add_vertex(int id, float x, float y, std::string name)
{
	vertices.emplace_back(new vertex(id, x, y, name));
	if (id > current_id)
		current_id = id;
}

void engine::remove_vertex(std::string name)
{
	for(size_t i = 0; i < vertices.size(); ++i)
	{
		if (vertices[i].get()->get_name() == name)
		{
			vertices.erase(vertices.begin() + i);
			break;
		}
	}
}

void engine::remove_vertex(int index)
{
	remove_attached_edges(*vertices[index]);
	vertices.erase(vertices.begin() + index);
}

vertex * engine::get_vertex(int id)
{
	auto found = std::find_if(vertices.begin(), vertices.end(), [id](auto& vertex)
	{
		return vertex->get_id() == id;
	});
	if (found != vertices.end())
		return found->get();
	return nullptr;
}

int engine::remove_all_selected()
{
	int count = 0;
	erase_if(vertices, [&count, this](auto& vertice)
	{
		if (vertice->is_selected())
		{
			++count;
			remove_attached_edges(*vertice);
			return true;
		}
			return false;
	});
	return count;
}

void engine::remove_attached_edges(vertex& vertice)
{
	for(auto adjascent : vertice.get_adjacents())
	{
		for(size_t i = 0; i < adjascent->get_adjacents().size(); ++i)
		{
			if(adjascent->get_adjacents()[i] == &vertice)
			{
				adjascent->get_adjacents().erase(adjascent->get_adjacents().begin() + i);
				break;
			}
		}
	}
	erase_if(edges, [&vertice](const auto& edge)
	{
		return (edge.get_first() == &vertice || edge.get_second() == &vertice);
	});
}

void engine::move_vertex(int index, sf::Vector2f pos)
{
	vertices[index]->set_position(pos);
	for(auto& edge : edges)
	{
		if (edge.get_first() == vertices[index].get())
			edge.set_first_pos(pos);
		if (edge.get_second() == vertices[index].get())
			edge.set_second_pos(pos);
	}
}

void engine::add_edge(vertex* first, vertex* second)
{
	if (!second->has_edge(first))
	{
		edges.emplace_back(first, second);
		first->get_adjacents().push_back(second);
		second->get_adjacents().push_back(first);
	}
}

void engine::remove_edge(int index)
{
	for(auto i = 0; i < edges[index].get_first()->get_adjacents().size(); ++i)
	{
		if(edges[index].get_first()->get_adjacents()[i] == edges[index].get_second())
		{
			edges[index].get_first()->get_adjacents().erase(edges[index].get_first()->get_adjacents().begin() + i);
			break;
		}
	}
	for(auto i = 0; i < edges[index].get_second()->get_adjacents().size(); ++i)
	{
		if(edges[index].get_second()->get_adjacents()[i] == edges[index].get_first())
		{
			edges[index].get_second()->get_adjacents().erase(edges[index].get_second()->get_adjacents().begin() + i);
			break;
		}
	}
	edges.erase(edges.begin() + index);
}
