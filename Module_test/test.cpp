#include <complex>
#include "pch.h"
#include "..\Polyline.h"

TEST(Polyline, Constructor)
{
	Polyline<IntPoint2> p_1;
	Polyline<DoublePoint3> p_2;
	Polyline<std::complex<double>> p_3;
	EXPECT_THROW(p_1.Length(), const char*);
	EXPECT_THROW(p_2.Length(), const char*);
	EXPECT_THROW(p_3.Length(), const char*);
}

TEST(Polyline, Constructor_Param) 
{
	EXPECT_THROW(Polyline<IntPoint2> p_1(-2), const char*);
	EXPECT_THROW(Polyline<DoublePoint3> p_2(-10), const char*);
	EXPECT_THROW(Polyline<std::complex<double>> p_3(-1), const char*);
}

TEST(Polyline, ConstructorCopy) 
{
	Polyline<IntPoint2> p_1(3);
	Polyline<DoublePoint3> p_2(3);
	Polyline<std::complex<double>> p_3(3);
	for (size_t i = 0; i < 2; ++i)
	{
		p_1[i]._x = i;
		p_1[i]._y = i;
		p_2[i]._x = i;
		p_2[i]._y = i;
		p_2[i]._z = i;
		p_3[i] = (i * i - 1,  i );
	}
	
	Polyline<IntPoint2> copy_1(p_1);
	Polyline<DoublePoint3> copy_2(p_2);
	Polyline<std::complex<double>> copy_3(p_3);

	EXPECT_EQ(p_1[0]._x, copy_1[0]._x);
	EXPECT_EQ(p_1[0]._y, copy_1[0]._y);
	EXPECT_EQ(p_1[1]._x, copy_1[1]._x);
	EXPECT_EQ(p_1[1]._y, copy_1[1]._y);
	EXPECT_EQ(p_2[0]._x, copy_2[0]._x);
	EXPECT_EQ(p_2[0]._y, copy_2[0]._y);
	EXPECT_EQ(p_2[0]._z, copy_2[0]._z);
	EXPECT_EQ(p_2[1]._x, copy_2[1]._x);
	EXPECT_EQ(p_2[1]._y, copy_2[1]._y);
	EXPECT_EQ(p_2[1]._z, copy_2[1]._z);
	EXPECT_EQ(p_3[0].real(), copy_3[0].real());
	EXPECT_EQ(p_3[0].imag(), copy_3[0].imag());
	EXPECT_EQ(p_3[1].real(), copy_3[1].real());
	EXPECT_EQ(p_3[1].imag(), copy_3[1].imag());
}

TEST(Polyline, Length) 
{
	Polyline<IntPoint2> p_1(2);
	Polyline<DoublePoint3> p_2(2);
	Polyline<std::complex<double>> p_3(2);
	p_1[0]._x = 0;
	p_1[0]._y = 0;
	p_1[1]._x = 3;
	p_1[1]._y = 4;
	p_2[0]._x = 0;
	p_2[0]._y = 0;
	p_2[0]._z = 0;
	p_2[1]._x = 3;
	p_2[1]._y = 4;
	p_2[1]._z = 5;
	std::complex<double> point_1(2, 3);
	p_3[0] = point_1;
	std::complex<double> point_2(5, 7);
	p_3[1] = point_2;
	EXPECT_EQ(5, p_1.Length());
	EXPECT_EQ(sqrt(50), p_2.Length());
	EXPECT_EQ(5, p_3.Length());
}

TEST(Polyline, AddToEnd) 
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 0;
	p_1[0]._y = 0;
	IntPoint2 a;
	a._x = 10;
	a._y = 0;
	p_1.AddToEnd(a);
	EXPECT_EQ(10, p_1.Length());
	Polyline<DoublePoint3> p_2(1);
	p_2[0]._x = 0;
	p_2[0]._y = 0;
	p_2[0]._z = 0;
	DoublePoint3 b;
	b._x = 3;
	b._y = 4;
	b._z = 5;
	p_2.AddToEnd(b);
	EXPECT_EQ(sqrt(50), p_2.Length());
	Polyline<std::complex<double>> p_3(1);
	std::complex<double> point(1, 1);
	p_3[0] = point;
	std::complex<double> c(4, 5);
	p_3.AddToEnd(c);
	EXPECT_EQ(5, p_3.Length());
}

TEST(Polyline, AddtoEnd_IntPoint2_EXCEPTION)
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 0;
	p_1[0]._y = 0;
	IntPoint2 a;
	a._x = 0;
	a._y = 0;
	EXPECT_THROW(p_1.AddToEnd(a), const char*);
}

TEST(Polyline, AddtoEnd_DoublePoint3_EXCEPTION)
{
	Polyline<DoublePoint3> p(1);
	p[0]._x = 0;
	p[0]._y = 0;
	p[0]._z = 0;
	DoublePoint3 b;
	b._x = 0;
	b._y = 0;
	b._z = 0;
	EXPECT_THROW(p.AddToEnd(b), const char*);
}

TEST(Polyline, AddtoEnd_ComplexPoint_EXCEPTION)
{
	Polyline<std::complex<double>> p_3(1);
	std::complex<double> point(1, 1);
	p_3[0] = point;
	std::complex<double> c(1, 1);
	EXPECT_THROW(p_3.AddToEnd(c), const char*);
}

TEST(Polyline, AddToBegin)
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 0;
	p_1[0]._y = 0;
	IntPoint2 a;
	a._x = 10;
	a._y = 0;
	p_1.AddToBegin(a);
	EXPECT_EQ(10, p_1.Length());
	Polyline<DoublePoint3> p_2(1);
	p_2[0]._x = 0;
	p_2[0]._y = 0;
	p_2[0]._z = 0;
	DoublePoint3 b;
	b._x = 3;
	b._y = 4;
	b._z = 5;
	p_2.AddToBegin(b);
	EXPECT_EQ(sqrt(50), p_2.Length());
	Polyline<std::complex<double>> p_3(1);
	std::complex<double> point(1, 1);
	p_3[0] = point;
	std::complex<double> c(4, 5);
	p_3.AddToBegin(c);
	EXPECT_EQ(5, p_3.Length());
}

TEST(Polyline, AddToBegin_IntPoint2_EXCEPTION)
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 0;
	p_1[0]._y = 0;
	IntPoint2 a;
	a._x = 0;
	a._y = 0;
	EXPECT_THROW(p_1.AddToBegin(a), const char*);
	
}

TEST(Polyline, AddToBegin_DoublePoint3_EXCEPTION)
{
	Polyline<DoublePoint3> p(1);
	p[0]._x = 0;
	p[0]._y = 0;
	p[0]._z = 0;
	DoublePoint3 b;
	b._x = 0;
	b._y = 0;
	b._z = 0;
	EXPECT_THROW(p.AddToBegin(b), const char*);
}

TEST(Polyline, AddToBegin_ComplexPoint_EXCEPTION)
{
	Polyline<std::complex<double>> p(1);
	std::complex<double> point(1, 1);
	p[0] = point;
	std::complex<double> c(1, 1);
	EXPECT_THROW(p.AddToBegin(c), const char*);
}

TEST(Polyline, SquareBrackets) 
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 1;
	p_1[0]._y = 2;
	EXPECT_EQ(1, p_1[0]._x);
	EXPECT_EQ(2, p_1[0]._y);
	Polyline<DoublePoint3> p_2(1);
	p_2[0]._x = 0;
	p_2[0]._y = 1;
	p_2[0]._z = 2;
	EXPECT_EQ(0, p_2[0]._x);
	EXPECT_EQ(1, p_2[0]._y);
	EXPECT_EQ(2, p_2[0]._z);
	Polyline<std::complex<double>> p_3(1);
	std::complex<double> point(1, 1);
	p_3[0] = point;
	EXPECT_EQ(1, p_3[0].real());
	EXPECT_EQ(1, p_3[0].imag());
}

TEST(Polyline, SquareBrackets_EXCEPTION)
{
	Polyline<IntPoint2> p_1(1);
	p_1[0]._x = 1;
	p_1[0]._y = 2;
	EXPECT_THROW(p_1[10], const char*);
	Polyline<DoublePoint3> p_2(1);
	p_2[0]._x = 0;
	p_2[0]._y = 1;
	p_2[0]._z = 2;
	EXPECT_THROW(p_2[10], const char*);
	Polyline<std::complex<double>> p_3(1);
	std::complex<double> point(1, 1);
	p_3[0] = point;
	EXPECT_THROW(p_3[10], const char*);
}

TEST(Polyline, OperatorPlusForIntPoint2) 
{
	Polyline<IntPoint2> p1(1);
	Polyline<IntPoint2> p2(1);
	p1[0]._x = 1;
	p1[0]._y = 1;
	p2[0]._x = 3;
	p2[0]._y = 2;
	p1 = p1 + p2;
	EXPECT_EQ(1, p1[0]._x);
	EXPECT_EQ(1, p1[0]._y);
	EXPECT_EQ(3, p1[1]._x);
	EXPECT_EQ(2, p1[1]._y);
}

TEST(Polyline, OperatorPlusForDoublePoint3)
{
	Polyline<DoublePoint3> p1(1);
	Polyline<DoublePoint3> p2(1);
	p1[0]._x = 1;
	p1[0]._y = 1;
	p1[0]._z = 1;
	p2[0]._x = 3;
	p2[0]._y = 2;
	p2[0]._z = 2;
	p1 = p1 + p2;
	EXPECT_EQ(1, p1[0]._x);
	EXPECT_EQ(1, p1[0]._y);
	EXPECT_EQ(1, p1[0]._z);
	EXPECT_EQ(3, p1[1]._x);
	EXPECT_EQ(2, p1[1]._y);
	EXPECT_EQ(2, p1[1]._z);
}

TEST(Polyline, OperatorPlusForComplexPoint)
{
	Polyline<std::complex<double>> p1(1);
	Polyline<std::complex<double>> p2(1);
	std::complex<double> a(1, 1);
	std::complex<double> b(2, 2);
	p1[0] = a;
	p2[0] = b;
	p1 = p1 + p2;
	EXPECT_EQ(1, p1[0].real());
	EXPECT_EQ(1, p1[0].imag());
	EXPECT_EQ(2, p1[1].real());
	EXPECT_EQ(2, p1[1].imag());
}

TEST(Polyline, OperatorIsEqual)
{
	Polyline<IntPoint2> p1(1);
	Polyline<IntPoint2> p2(1);
	p1[0]._x = 1;
	p1[0]._y = 1;
	p2[0]._x = 1;
	p2[0]._y = 1;
	EXPECT_TRUE(p1 == p2);
	Polyline<DoublePoint3> p3(1);
	Polyline<DoublePoint3> p4(1);
	p3[0]._x = 1;
	p3[0]._y = 1;
	p3[0]._z = 1;
	p4[0]._x = 1;
	p4[0]._y = 1;
	p4[0]._z = 1;
	EXPECT_TRUE(p3 == p4);
	Polyline<std::complex<double>> p5(1);
	Polyline<std::complex<double>> p6(1);
	std::complex<double> a(1, 1);
	std::complex<double> b(1, 1);
	EXPECT_TRUE(p5 == p6);
}

TEST(Polyline, OperatorIsNotEqual)
{
	Polyline<IntPoint2> p1(1);
	Polyline<IntPoint2> p2(1);
	p1[0]._x = 1;
	p1[0]._y = 1;
	p2[0]._x = 2;
	p2[0]._y = 14;
	EXPECT_TRUE(p1 != p2);
	Polyline<DoublePoint3> p3(1);
	Polyline<DoublePoint3> p4(1);
	p3[0]._x = 1;
	p3[0]._y = 1;
	p3[0]._z = 1;
	p4[0]._x = 21;
	p4[0]._y = 131;
	p4[0]._z = 141;
	EXPECT_TRUE(p3 != p4);
	Polyline<std::complex<double>> p5(1);
	Polyline<std::complex<double>> p6(1);
	std::complex<double> a(1, 1);
	std::complex<double> b(2, 3);
	p5[0] = a;
	p6[0] = b;
	EXPECT_TRUE(p5 != p6);
}

TEST(Polyline, Operator_Assignment) 
{
	Polyline<IntPoint2> p1(2);
	Polyline<IntPoint2> p2(1);
	p1[0]._x = 0;
	p1[0]._y = 0;
	p2[0]._x = 3;
	p2[0]._y = 4;
	p1[1]._x = p2[0]._x;
	p1[1]._y = p2[0]._y;
	EXPECT_EQ(5, p1.Length());
	Polyline<DoublePoint3> p3(2);
	Polyline<DoublePoint3> p4(1);
	p3[0]._x = 0;
	p3[0]._y = 0;
	p3[0]._z = 0;
	p4[0]._x = 10;
	p4[0]._y = 1;
	p4[0]._z = 1;
	p3[1]._x = p4[0]._x;
	p3[1]._y = p4[0]._y;
	p3[1]._z = p4[0]._z;
	EXPECT_EQ(sqrt(102), p3.Length());
	Polyline<std::complex<double>> p5(2);
	Polyline<std::complex<double>> p6(1);
	std::complex<double> a(1, 1);
	std::complex<double> b(4, 5);
	p5[0] = a;
	p6[0] = b;
	p5[1] = p6[0];
	EXPECT_EQ(5, p5.Length());
}

TEST(Polyline, OperaportEqual) 
{
	Polyline<IntPoint2> p1(1);
	Polyline<IntPoint2> p2(1);
	p1[0]._x = 1;
	p1[0]._y = 2;
	p2 = p1;
	EXPECT_EQ(1, p2[0]._x);
	EXPECT_EQ(2, p2[0]._y);
	Polyline<DoublePoint3> p3(1);
	Polyline<DoublePoint3> p4(1);
	p3[0]._x = 1;
	p3[0]._y = 2;
	p3[0]._z = 3;
	p4 = p3;
	EXPECT_EQ(1, p4[0]._x);
	EXPECT_EQ(2, p4[0]._y);
	EXPECT_EQ(3, p4[0]._z);
	Polyline<std::complex<double>> p5(1);
	Polyline<std::complex<double>> p6(1);
	std::complex<double> a(1, 1);
	p5[0] = a;
	p6 = p5;
	EXPECT_EQ(1, p6[0].real());
	EXPECT_EQ(1, p6[0].imag());
}