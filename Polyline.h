#pragma once
#include <complex>
#include <iostream>
#include <vector>

struct IntPoint2
{
	int _x;
	int _y;

    //IntPoint2& operator= (const IntPoint2& point) = default;

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

std::istream& operator>> (std::istream& in, IntPoint2& point)
{
   in >> point._x;
   in >> point._y;
   return in;
}

struct DoublePoint3
{
	double _x;
	double _y;
	double _z;

    //DoublePoint3& operator= (const DoublePoint3& point) = default;

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

std::istream& operator>> (std::istream& in, DoublePoint3& point)
{
    in >> point._x;
    in >> point._y;
    in >> point._z;
    return in;
}


template <class T>
class Polyline
{
	std::vector<T> v;

public:
	Polyline() = default;
    Polyline(const Polyline<T>& polyline) = default;
    Polyline& operator = (const Polyline& line) = default;
	size_t Vertex() const;
	auto Length() const;
	bool operator== (const Polyline& rhs) const;
	bool operator!= (const Polyline& rhs) const;
	Polyline operator+ (const Polyline& polyline);
	T operator[] (const size_t index) const;
	T& operator[] (const size_t index);
	void AddToEnd(T& point);
	void AddToBegin(T& point);
    auto begin();
    auto end();
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

template<class T>
size_t Polyline<T>::Vertex() const
{
	return v.size();
}

template <class T>
auto Polyline<T>::Length() const
{
	if ((v.empty()) || (v.size() < 2)) throw std::logic_error("Polyline is empty");
	auto length = v[0].Distance(v[1]);
	for (size_t i = 1; i < v.size() - 1; ++i)
	{
		length += v[i].Distance(v[i + 1]);
	}
	return length;
}

template <>
auto Polyline<std::complex<double>>::Length() const
{
	if ((v.empty()) || (v.size() < 2)) throw std::logic_error("Polyline is empty");
	double length = 0;
	for (size_t i = 0; i < v.size() - 1; ++i)
	{
		length+= std::abs((v[i + 1] - v[i]));
	}
	return length;
}

template <class T>
bool Polyline<T>::operator== (const Polyline<T>& rhs) const
{
	if (v.size() != rhs.v.size()) return false;
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] == rhs[i]) return false;
	}
	return true;
}

template <class T>
bool Polyline<T>::operator!= (const Polyline<T>& rhs) const
{
	if (v.size() != rhs.v.size()) return true;
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] != rhs.v[i]) return true;
	}
	return false;
}

template <class T>
Polyline<T> Polyline<T>::operator+ (const Polyline<T>& polyline)
{
    if (v.empty()) return polyline;
    if (!polyline.Vertex()) return *this;
	Polyline<T> result(*this);
	for (size_t i = 0; i < polyline.v.size(); ++i)
	{
		result.v[v.size() + i] = polyline.v[i];
	}
	return result;
}

template <class T>
T Polyline<T>::operator[] (const size_t index) const
{
	return v.at(index);
}

template <class T>
T& Polyline<T>::operator[] (const size_t index)
{
	return v.at(index);
}

template <class T>
void Polyline<T>::AddToEnd(T& point)
{
	v.push_back(point);
}

template <class T>
void Polyline<T>::AddToBegin(T& point)
{
	v.insert(v.begin(), point);
}

template <class T>
auto Polyline<T>::begin()
{
    return v.begin();
}

template <class T>
auto Polyline<T>::end()
{
    return v.end();
}
