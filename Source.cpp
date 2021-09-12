#include <iostream>
#include <math.h>

class Polyline
{
	struct Point
	{
		double x;
		double y;
	};
	Point* p;
	size_t vertex;

public:
	Polyline() : p(nullptr), vertex(0) { }

	Polyline(size_t count_vertex) : p(new Point[count_vertex]()), vertex(count_vertex) { }

	~Polyline()
	{
		delete[] p;
	}

	Polyline(const Polyline& polyline) : p(new Point[vertex]), vertex(polyline.vertex)
	{
		for (size_t i = 0; i < vertex; ++i)
		{
			p[i] = polyline.p[i]; //Исправить 
		}
	}

	double Length() const noexcept
	{
		double lenght = 0;
		for (size_t i = 0; i < vertex - 1; ++i)
		{
			lenght += sqrt(pow((p[i + 1].x - p[i].x), 2) + pow((p[i + 1].y - p[i].y), 2));
		}
		return lenght;
	}

	bool operator== (const Polyline& rhs) const noexcept
	{
		if (vertex != rhs.vertex) return false;
		for (size_t i = 0; i < vertex; ++i)
		{
			if ((p[i].x != rhs.p[i].x) || (p[i].y != rhs.p[i].y)) return false;
		}
		return true;
	}

	Polyline& operator+ (const Polyline& polyline) noexcept
	{
		Polyline result(vertex + polyline.vertex);
		for (size_t i = 0; i < vertex; ++i)
		{
			result[i] = p[i];
		}
		for (size_t i = 0; i < polyline.vertex; ++i)
		{
			result[vertex + i] = polyline.p[i];
		}
		return result;
	}

	Point operator[] (const size_t index) const
	{
		if (index >= vertex) throw "Invalid index";
		return p[index];
	}

	Point& operator[] (const size_t index)
	{
		if (index >= vertex) throw "Invalid index";
		return p[index];
	}

	void AddToEnd(Point& point)
	{
		vertex += 1;
		Point* tmp = new Point[vertex];
		for (size_t i = 0; i < vertex - 1; ++i)
		{
			tmp[i] = p[i];
		}
		tmp[vertex - 1] = point;
		delete[] p;
		p = tmp;
	}

	void AddToBegin(Point& point)
	{
		vertex += 1;
		Point* tmp = new Point[vertex];
		tmp[0] = point;
		for (size_t i = 1; i < vertex; ++i)
		{
			tmp[i] = p[i];
		}
		delete[] p;
		p = tmp;
	}

	friend std::ostream& operator<< (std::ostream& out, const Polyline& polyline);
};

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



int main() {
	Polyline test(3);
	for (size_t i = 0; i < 3; ++i)
	{

		test[i].x = i;
		test[i].y = i;
	}

	std::cout << test << std::endl;

	std::cout << test.Length();

	return 0;
}