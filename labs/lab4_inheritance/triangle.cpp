/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 *
 * Please see triangle.h for documentation on the Triangle class
 */

#include "triangle.h"

#include <cstdio>

#include <vector>
#include <memory>

#include "line.h"

Triangle::Triangle(const RGBAPixel& pcolor, const Vector2& vertex1,
		const Vector2& vertex2, const Vector2& vertex3)
	: Shape(Vector2(0, 0), pcolor), vertices_{vertex1, vertex2, vertex3}
{
	this->center_ = (vertex1 + vertex2 + vertex3) / 3;
}

Triangle::Triangle(const Triangle& other)
	: Shape(other.center(), other.color()), vertices_(other.vertices_)
{
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Shape::operator=(rhs);
	this->vertices_ = rhs.vertices_;

	return *this;
}

Vector2 const & Triangle::vertex(int i) const
{
	assert(i >= 0 && i <= 2);
	return this->vertices_[i];
}

void Triangle::set_vertex(int i, const Vector2& value)
{
	assert(i >= 0 && i <= 2);
	this->vertices_[i] = value;
}

int Triangle::area() const
{
	const Vector2 ab(this->vertex(0) - this->vertex(1));
	const Vector2 ac(this->vertex(0) - this->vertex(2));
	const int tarea = static_cast<int>(0.5 * ab.crossProduct(ab));
	return tarea;
}

int Triangle::perimeter() const
{
	const double distance = (this->vertex(0).distanceTo(this->vertex(1)) +
			this->vertex(1).distanceTo(this->vertex(2)) +
			this->vertex(2).distanceTo(this->vertex(0)));
	return static_cast<int>(distance);
}

bool Triangle::contains(const Vector2& p) const
{
	/* Code taken from http://www.blackpawn.com/texts/pointinpoly/default.html */
	const Vector2& a = this->vertex(0);
	const Vector2& b = this->vertex(1);
	const Vector2& c = this->vertex(2);
	const Vector2 v0 = c - a;
	const Vector2 v1 = b - a;
	const Vector2 v2 = p - a;

	const double dot00 = v0.dotProduct(v0);
	const double dot01 = v0.dotProduct(v1);
	const double dot02 = v0.dotProduct(v2);
	const double dot11 = v1.dotProduct(v1);
	const double dot12 = v1.dotProduct(v2);

	const double inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
	const double u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
	const double v = (dot00 * dot12 - dot01 * dot02) * inv_denom;

	return (u > 0) && (v > 0) && (u + v < 1);
}

void Triangle::draw(PNG& canvas) const
{
	/* Code taken from
	 * http://gabrielongraphics.blogspot.com/2005/09/drawing-triangles.html */
	auto a = std::make_shared<Vector2>(this->vertex(0));
	auto b = std::make_shared<Vector2>(this->vertex(1));
	auto c = std::make_shared<Vector2>(this->vertex(2));

	std::shared_ptr<Vector2> small = a;
	std::shared_ptr<Vector2> medium = b;
	std::shared_ptr<Vector2> large = c;
	std::shared_ptr<Vector2> temp;
	
	// Swap small and medium if needed
	(small->isSouthOf(*medium)) ? (temp = small, small = medium, medium = temp) : 0;

	// Swap small and large if needed
	(small->isSouthOf(*large)) ? (temp = small, small = large, large = temp) : 0;

	// Swap medium and large if needed
	(medium->isSouthOf(*large)) ? (temp = medium, medium = large, large = temp) : 0;
 

	std::vector<double> x_small_medium =
		Line::linearInterpolation(Vector2(small->y(), small->x()),
				Vector2(medium->y(), medium->x()));
	std::vector<double> x_medium_large =
		Line::linearInterpolation(Vector2(medium->y(), medium->x()),
				Vector2(large->y(), large->x()));
	std::vector<double> x_small_large =
		Line::linearInterpolation(Vector2(small->y(), small->x()),
				Vector2(large->y(), large->x()));

	for (int y = static_cast<int>(small->y()); y < static_cast<int>(medium->y()); y++)
	{
		const Vector2 p(x_small_medium[static_cast<int>(y - small->y())], static_cast<double>(y));
		const Vector2 q(x_small_large[static_cast<int>(y - small->y())], static_cast<double>(y));
		const Line pq(p, q, this->color());
		pq.draw(canvas);
	}

	for (int y = static_cast<int>(medium->y()); y < static_cast<int>(large->y()); y++)
	{
		const Vector2 p(x_medium_large[static_cast<int>(y - medium->y())], static_cast<double>(y));
		const Vector2 q(x_small_large[static_cast<int>(y - small->y())], static_cast<double>(y));
		const Line pq(p, q, this->color());
		pq.draw(canvas);

	}
}

void Triangle::set_center(const Vector2& pcenter)
{
	const Vector2 delta(pcenter - this->center());
	/* Move the three vertices by the delta from
	   the new center to the old center. */
	this->set_vertex(0, this->vertex(0) + delta);
	this->set_vertex(1, this->vertex(1) + delta);
	this->set_vertex(2, this->vertex(2) + delta);
	Shape::set_center(pcenter);
}

