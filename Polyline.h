#pragma once
#include <complex>
#include <iostream>

struct IntPoint2
{
	int _x;
	int _y;

	bool operator== (const IntPoint2& rhs) const noexcept
	{
		if ((_x == rhs._x) && (_y == rhs._y)) return true;
		else return false;
	}

	float Distance(const IntPoint2& rhs) const noexcept
	{
		return static_cast<float>(sqrt(pow((_x - rhs._x), 2) + pow((_y - rhs._y), 2)));
	}
};

struct DoublePoint3
{
	double _x;
	double _y;
	double _z;

	bool operator== (const DoublePoint3& rhs) const noexcept
	{
		if ((_x == rhs._x) && (_y == rhs._y) && (_z == rhs._z)) return true;
		else return false;
	}

	double Distance(const DoublePoint3& rhs) const noexcept
	{
		return sqrt(pow((_x - rhs._x), 2) + pow((_y - rhs._y), 2) + pow((_z - rhs._z), 2));
	}
};


template <class T>
class Polyline
{
	T* p;
	size_t vertex;

public:
	Polyline();
	Polyline(int count_vertex);
	~Polyline();
	Polyline(const Polyline& polyline);
	auto Length() const;
	bool operator== (const Polyline& rhs) const noexcept;
	bool operator!= (const Polyline& rhs) const noexcept;
	Polyline operator+ (const Polyline& polyline) noexcept;
	Polyline& operator = (const Polyline& line) noexcept;
	T operator[] (const size_t index) const;
	T& operator[] (const size_t index);
	void AddToEnd(const T& point);
	void AddToBegin(const T& point);
	friend std::ostream& operator<< (std::ostream& out, const Polyline& polyline);
};

template <class T>
std::ostream& operator<< (std::ostream& out, const Polyline<T>& polyline);