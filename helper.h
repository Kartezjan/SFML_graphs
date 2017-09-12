#pragma once

#include <algorithm>

template <class Container, class F>
void erase_if(Container& v, F&& l) {
	v.erase(std::remove_if(v.begin(), v.end(), l), v.end());
}

template <class vector>
float distance(vector a, vector b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

template <class vector>
float linear_gradient(vector a, vector b)
{
	return (a.y - b.y) / (a.x - b.x);
}

template <class vector>
float distance_beetwen_line(vector pos, vector line_point1, vector line_point2)
{
	auto a_1 = linear_gradient(line_point1, line_point2);
	auto b_1 = line_point1.y - a_1 * line_point1.x;
	auto a_2 = -1 * a_1;
	auto b_2 = pos.y - a_2 * pos.x;
	auto point_x = (b_2 - b_1) / (2 * a_1);
	auto point = sf::Vector2f(point_x, point_x*a_1 + b_1);
	return distance(point, pos);
}