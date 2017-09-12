#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>

#include "helper.h"

#define SIZE 25.f

enum class object_type {vertex, edge, none};
enum class mouse_mode {insert, remove, select, move, edge, bfs};
enum class vertex_color {white, gray, black};

namespace strings
{
	const char insert[] = "INSERT MODE";
	const char remove[] = "REMOVE MODE";
	const char select[] = "SELECT MODE";
	const char move[] = "MOVE MODE";
	const char edges[] = "ADD EDGES MODE";
	const char bfs[] = "BREADTH-FIRST SEARCH";
}


class font
{
public:
	static sf::Font* get_font();
private:
	font() {}
	static sf::Font* default_font;
};

class visual_object : public sf::Drawable, public sf::Transformable
{
};