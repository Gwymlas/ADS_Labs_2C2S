#include <iostream>
#include <math.h>

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
	Polyline() : p(nullptr), vertex(0) { }

	Polyline(size_t count_vertex) : p(new Point[count_vertex]()), vertex(count_vertex) { }

	~Polyline()
	{
		delete[] p;
	}

	Polyline(const Polyline& polyline) : p(new Point[polyline.vertex]), vertex(polyline.vertex)
	{
		for (size_t i = 0; i < polyline.vertex; ++i)
		{
			p[i] = polyline.p[i]; 
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

	bool operator!= (const Polyline& rhs) const noexcept
	{
		if (vertex != rhs.vertex) return true;
		for (size_t i = 0; i < vertex; ++i)
		{
			if ((p[i].x != rhs.p[i].x) || (p[i].y != rhs.p[i].y)) return true;
		}
		return false;
	}

	Polyline operator+ (const Polyline& polyline) noexcept
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

	Polyline& operator = (const Polyline& line)
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

	void AddToEnd(const Point& point)
	{
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

	void AddToBegin(const Point& point)
	{
		vertex += 1;
		Point* tmp = new Point[vertex];
		tmp[0] = point;
		for (size_t i = 1; i < vertex; ++i)
		{
			tmp[i] = p[i-1];
		}
		if (p != nullptr) delete[] p;
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

	Polyline test1(1);
	test1 = test;
	std::cout << test1 << std::endl;

	std::cout << test << std::endl;
	std::cout << test.Length() << std::endl;
	try
	{
		//test[35];
		std::cout << test[2].x << std::endl;
	}
	catch (const char* err)
	{
		std::cerr << err << std::endl;
	}

	Polyline test2(1);
	for (size_t i = 0; i < 1; ++i)
	{

		test2[i].x = (double)i + 10;
		test2[i].y = (double)i + 10;
	}
	
	std::cout << test2 << std::endl;
	std::cout << test2.Length() << std::endl;

	Polyline test3 = test + test2;

	std::cout << (test2 == test3) << std::endl;
	std::cout << (test2 != test3) << std::endl;

	Point p;
	p.x = 21;
	p.y = 23;

	test3.AddToBegin(p);
	test3.AddToEnd(p);

	std::cout << test3 << std::endl;

	return 0;
}