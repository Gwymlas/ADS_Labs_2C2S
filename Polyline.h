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

std::ostream& operator<< (std::ostream& out, const IntPoint2& point)
{
	out << "(" << point._x << "; " << point._y << ")";
	return out;
}

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

std::ostream& operator<< (std::ostream& out, const DoublePoint3& point)
{
	out << "(" << point._x << "; " << point._y << "; " << point._z << ")";
	return out;
}


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
	size_t Vertex() const noexcept;
	auto Length() const;
	bool operator== (const Polyline& rhs) const noexcept;
	bool operator!= (const Polyline& rhs) const noexcept;
	Polyline operator+ (const Polyline& polyline) noexcept;
	Polyline& operator = (const Polyline& line) noexcept;
	T operator[] (const size_t index) const;
	T& operator[] (const size_t index);
	void AddToEnd(const T& point);
	void AddToBegin(const T& point);
};

template <class T>
std::ostream& operator<< (std::ostream& out, const Polyline<T>& polyline)
{
	out << "Polyline[";
	for (size_t i = 0; i < polyline.Vertex(); ++i)
	{
		if (i != polyline.Vertex() - 1) out << polyline[i] << ", ";
		else out << polyline[i];
	}
	out << "]";
	return out;
}

template <class T>
Polyline<T>::Polyline() : p(nullptr), vertex(0) { }

template <class T>
Polyline<T>::Polyline(int count_vertex)
{
	if (count_vertex < 0) throw "Vertex count error";
	vertex = (size_t)count_vertex;
	p = new T[count_vertex]();
}

template <class T>
Polyline<T>::~Polyline()
{
	delete[] p;
}

template <class T>
Polyline<T>::Polyline(const Polyline<T>& polyline) : p(new T[polyline.vertex]), vertex(polyline.vertex)
{
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		p[i] = polyline.p[i];
	}
}

template<class T>
size_t Polyline<T>::Vertex() const noexcept
{
	return vertex;
}

template <class T>
auto Polyline<T>::Length() const
{
	if ((p == nullptr) || (vertex < 2)) throw "Polyline is empty";
	auto lenght = p[0].Distance(p[1]);
	for (size_t i = 1; i < vertex - 1; ++i)
	{
		lenght += p[i].Distance(p[i + 1]);
	}
	return lenght;
}

template <>
auto Polyline<std::complex<double>>::Length() const
{
	if ((p == nullptr) || (vertex < 2)) throw "Polyline is empty";
	double lenght = 0;
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		lenght += std::abs((p[i + 1] - p[i])); //proverit'
	}
	return lenght;
}

template <class T>
bool Polyline<T>::operator== (const Polyline<T>& rhs) const noexcept
{
	if (vertex != rhs.vertex) return false;
	for (size_t i = 0; i < vertex; ++i)
	{
		if (!(p[i] == rhs.p[i])) return false;
	}
	return true;
}

template <class T>
bool Polyline<T>::operator!= (const Polyline<T>& rhs) const noexcept
{
	if (vertex != rhs.vertex) return true;
	for (size_t i = 0; i < vertex; ++i)
	{
		if (!(p[i] == rhs.p[i])) return true;
	}
	return false;
}

template <class T>
Polyline<T> Polyline<T>::operator+ (const Polyline<T>& polyline) noexcept
{
	Polyline<T> result(vertex + polyline.vertex);
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

template <class T>
Polyline<T>& Polyline<T>::operator = (const Polyline<T>& line) noexcept
{
	if (this == (&line)) return *this;
	if (p) delete[] p;
	if (line.p)
	{
		p = new T[line.vertex];
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

template <class T>
T Polyline<T>::operator[] (const size_t index) const
{
	if (index >= vertex) throw "Invalid index";
	return p[index];
}

template <class T>
T& Polyline<T>::operator[] (const size_t index)
{
	if (index >= vertex) throw "Invalid index";
	return p[index];
}

template <class T>
void Polyline<T>::AddToEnd(const T& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if (p[i] == point) throw "Adding an existing point";
	}
	vertex += 1;
	T* tmp = new T[vertex];
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		tmp[i] = p[i];
	}
	tmp[vertex - 1] = point;
	if (p != nullptr) delete[] p;
	p = tmp;
}

template <class T>
void Polyline<T>::AddToBegin(const T& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if (p[i] == point) throw "Adding an existing point";
	}
	vertex += 1;
	T* tmp = new T[vertex];
	tmp[0] = point;
	for (size_t i = 1; i < vertex; ++i)
	{
		tmp[i] = p[i - 1];
	}
	if (p != nullptr) delete[] p;
	p = tmp;
}

//template <class T>
//std::ostream& operator<< (std::ostream& out, const Polyline<T>& polyline) // ispravit'
//{
//	out << "Polyline(";
//	for (size_t i = 0; i < polyline.vertex; ++i)
//	{
//		out << "vertex[" << i << "]: " << "(" << polyline.p[i].x << "," << polyline.p[i].y;
//		if (i != polyline.vertex - 1) out << "); ";
//		else out << ")";
//	}
//	out << ")";
//	return out;
//}