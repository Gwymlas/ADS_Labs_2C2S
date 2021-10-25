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

//TEST(Polyline, Length) 
//{
//	Polyline p(2);
//	p[0].x = 0;
//	p[0].y = 0;
//	p[1].x = 3;
//	p[1].y = 4;
//	EXPECT_EQ(5, p.Length());
//}
//
//TEST(Polyline, AddToEnd) 
//{
//	Polyline p(1);
//	p[0].x = 0;
//	p[0].y = 0;
//	Point a;
//	a.x = 10;
//	a.y = 0;
//	p.AddToEnd(a);
//	EXPECT_EQ(10, p.Length());
//}
//
//TEST(Polyline, AddtoEnd_EXCEPTION)
//{
//	Polyline p(1);
//	p[0].x = 0;
//	p[0].y = 0;
//	Point a;
//	a.x = 0;
//	a.y = 0;
//	EXPECT_THROW(p.AddToEnd(a), const char*);
//}
//
//TEST(Polyline, AddToBegin)
//{
//	Polyline p(1);
//	p[0].x = 0;
//	p[0].y = 0;
//	Point a;
//	a.x = 10;
//	a.y = 0;
//	p.AddToBegin(a);
//	EXPECT_EQ(10, p.Length());
//}
//
//TEST(Polyline, AddToBegin_EXCEPTION)
//{
//	Polyline p(1);
//	p[0].x = 0;
//	p[0].y = 0;
//	Point a;
//	a.x = 0;
//	a.y = 0;
//	EXPECT_THROW(p.AddToBegin(a), const char*);
//}
//
//TEST(Polyline, SquareBrackets) 
//{
//	Polyline p(1);
//	p[0].x = 1;
//	p[0].y = 2;
//	EXPECT_EQ(1, p[0].x);
//	EXPECT_EQ(2, p[0].y);
//}
//
//TEST(Polyline, SquareBrackets_EXCEPTION) 
//{
//	Polyline p(1);
//	p[0].x = 1;
//	p[0].y = 2;
//	EXPECT_THROW(p[5], const char*);
//}
//
//TEST(Polyline, OperatorPlus) 
//{
//	Polyline p1(1);
//	Polyline p2(1);
//	p1[0].x = 1;
//	p1[0].y = 1;
//	p2[0].x = 3;
//	p2[0].y = 2;
//	p1 = p1 + p2;
//	EXPECT_EQ(1, p1[0].x);
//	EXPECT_EQ(1, p1[0].y);
//	EXPECT_EQ(3, p1[1].x);
//	EXPECT_EQ(2, p1[1].y);
//}
//
//TEST(Polyline, OperatorIsEqual)
//{
//	Polyline p1(1);
//	Polyline p2(1);
//	p1[0].x = 1;
//	p1[0].y = 1;
//	p2[0].x = 1;
//	p2[0].y = 1;
//	EXPECT_TRUE(p1 == p2);
//}
//
//TEST(Polyline, OperatorIsNotEqual)
//{
//	Polyline p1(1);
//	Polyline p2(1);
//	p1[0].x = 1;
//	p1[0].y = 1;
//	p2[0].x = 2;
//	p2[0].y = 2;
//	EXPECT_TRUE(p1 != p2);
//}
//
//TEST(Polyline, Operator_Assignment) 
//{
//	Polyline p(2), p_1(1);
//	p[0].x = 1;
//	p[0].y = 1;
//	p_1[0].x = 25;
//	p_1[0].y = 33;
//	p[1].x = p_1[0].x;
//	p[1].y = p_1[0].y;
//	EXPECT_EQ(40, p.Length());
//}
//
//TEST(Polyline, OperaportEqual) 
//{
//	Polyline p1(1);
//	Polyline p2(1);
//	p1[0].x = 1;
//	p1[0].y = 3;
//	p2 = p1;
//	EXPECT_EQ(1, p2[0].x);
//	EXPECT_EQ(3, p2[0].y);
//}