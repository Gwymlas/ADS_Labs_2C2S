#pragma once
#include <iostream>

struct Point
{
	double x;
	double y;
};

class Polyline
{
	Point* p;
	size_t vertex;

public:
	Polyline();
	Polyline(int count_vertex);
	~Polyline();
	Polyline(const Polyline& polyline);
	double Length() const;
	bool operator== (const Polyline& rhs) const noexcept;
	bool operator!= (const Polyline& rhs) const noexcept;
	Polyline operator+ (const Polyline& polyline) noexcept;
	Polyline& operator = (const Polyline& line) noexcept;
	Point operator[] (const size_t index) const;
	Point& operator[] (const size_t index);
	void AddToEnd(const Point& point);
	void AddToBegin(const Point& point);
	friend std::ostream& operator<< (std::ostream& out, const Polyline& polyline);
};

std::ostream& operator<< (std::ostream& out, const Polyline& polyline);