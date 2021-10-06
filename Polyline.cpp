#include <iostream>
#include "Polyline.h"

Polyline::Polyline() : p(nullptr), vertex(0) { }

Polyline::Polyline(int count_vertex)
{
	if (count_vertex < 0) throw "Vertex count error";
	vertex = (size_t)count_vertex;
	p = new Point[count_vertex]();
}

Polyline::~Polyline()
{
	delete[] p;
}

Polyline::Polyline(const Polyline& polyline) : p(new Point[polyline.vertex]), vertex(polyline.vertex)
{
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		p[i] = polyline.p[i];
	}
}

double Polyline::Length() const 
{
	if (p == nullptr) throw "Line is empty";
	double lenght = 0;
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		lenght += sqrt(pow((p[i + 1].x - p[i].x), 2) + pow((p[i + 1].y - p[i].y), 2));
	}
	return lenght;
}

bool Polyline::operator== (const Polyline& rhs) const noexcept
{
	if (vertex != rhs.vertex) return false;
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((p[i].x != rhs.p[i].x) || (p[i].y != rhs.p[i].y)) return false;
	}
	return true;
}

bool Polyline::operator!= (const Polyline& rhs) const noexcept
{
	if (vertex != rhs.vertex) return true;
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((p[i].x != rhs.p[i].x) || (p[i].y != rhs.p[i].y)) return true;
	}
	return false;
}

Polyline Polyline::operator+ (const Polyline& polyline) noexcept
{
	Polyline result(vertex + polyline.vertex);
	for (size_t i = 0; i < vertex; ++i)
	{
		result.p[i] = p[i];
	}
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		result.p[vertex + i] = polyline.p[i];
	}
	return result;
}

Polyline& Polyline::operator = (const Polyline& line) noexcept
{
	if (this == (&line)) return *this;
	if (p) delete[] p;
	if (line.p)
	{
		p = new Point[line.vertex];
		vertex = line.vertex;
		for (size_t i = 0; i < line.vertex; ++i)
		{
			p[i] = line.p[i];
		}
	}
	else
	{
		p = nullptr;
		vertex = 0;
	}
	return *this;
}

Point Polyline::operator[] (const size_t index) const
{
	if (index >= vertex) throw "Invalid index";
	return p[index];
}

Point& Polyline::operator[] (const size_t index)
{
	if (index >= vertex) throw "Invalid index";
	return p[index];
}

void Polyline::AddToEnd(const Point& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((point.x == p[i].x) && (point.y == p[i].y)) throw "Adding an existing point";
	}
	vertex += 1;
	Point* tmp = new Point[vertex];
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		tmp[i] = p[i];
	}
	tmp[vertex - 1] = point;
	if (p != nullptr) delete[] p;
	p = tmp;
}

void Polyline::AddToBegin(const Point& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((point.x == p[i].x) && (point.y == p[i].y)) throw "Adding an existing point";
	}
	vertex += 1;
	Point* tmp = new Point[vertex];
	tmp[0] = point;
	for (size_t i = 1; i < vertex; ++i)
	{
		tmp[i] = p[i - 1];
	}
	if (p != nullptr) delete[] p;
	p = tmp;
}

std::ostream& operator<< (std::ostream& out, const Polyline& polyline)
{
	out << "Polyline(";
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		out << "vertex[" << i << "]: " << "(" << polyline.p[i].x << "," << polyline.p[i].y;
		if (i != polyline.vertex - 1) out << "); ";
		else out << ")";
	}
	out << ")";
	return out;
}
