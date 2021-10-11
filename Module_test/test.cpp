#include "pch.h"
#include "..\Polyline.h"
#include "..\Polyline.cpp"
TEST(Polyline, Constructor) 
{
	Polyline p;
	EXPECT_THROW(p.Length(), const char*);
}

TEST(Polyline, Constructor_Param) 
{
	EXPECT_THROW(Polyline p(-2), const char*);
}

TEST(Polyline, ConstructorCopy) 
{
	Polyline p(2);
	p[0].x = 0;
	p[0].y = 2;
	p[1].x = 2;
	p[1].y = 4;
	Polyline copy(p);
	EXPECT_EQ(p[0].x, copy[0].x);
	EXPECT_EQ(p[0].y, copy[0].y);
	EXPECT_EQ(p[1].x, copy[1].x);
	EXPECT_EQ(p[1].y, copy[1].y);
}

TEST(Polyline, Length) 
{
	Polyline p(2);
	p[0].x = 0;
	p[0].y = 0;
	p[1].x = 3;
	p[1].y = 4;
	EXPECT_EQ(5, p.Length());
}

TEST(Polyline, AddToEnd) 
{
	Polyline p(1);
	p[0].x = 0;
	p[0].y = 0;
	Point a;
	a.x = 10;
	a.y = 0;
	p.AddToEnd(a);
	EXPECT_EQ(10, p.Length());
}

TEST(Polyline, AddtoEnd_EXCEPTION)
{
	Polyline p(1);
	p[0].x = 0;
	p[0].y = 0;
	Point a;
	a.x = 0;
	a.y = 0;
	EXPECT_THROW(p.AddToEnd(a), const char*);
}

TEST(Polyline, AddToBegin)
{
	Polyline p(1);
	p[0].x = 0;
	p[0].y = 0;
	Point a;
	a.x = 10;
	a.y = 0;
	p.AddToBegin(a);
	EXPECT_EQ(10, p.Length());
}

TEST(Polyline, AddToBegin_EXCEPTION)
{
	Polyline p(1);
	p[0].x = 0;
	p[0].y = 0;
	Point a;
	a.x = 0;
	a.y = 0;
	EXPECT_THROW(p.AddToBegin(a), const char*);
}

TEST(Polyline, SquareBrackets) 
{
	Polyline p(1);
	p[0].x = 1;
	p[0].y = 2;
	EXPECT_EQ(1, p[0].x);
	EXPECT_EQ(2, p[0].y);
}

TEST(Polyline, SquareBrackets_EXCEPTION) 
{
	Polyline p(1);
	p[0].x = 1;
	p[0].y = 2;
	EXPECT_THROW(p[5], const char*);
}

TEST(Polyline, OperatorPlus) 
{
	Polyline p1(1);
	Polyline p2(1);
	p1[0].x = 1;
	p1[0].y = 1;
	p2[0].x = 3;
	p2[0].y = 2;
	p1 = p1 + p2;
	EXPECT_EQ(1, p1[0].x);
	EXPECT_EQ(1, p1[0].y);
	EXPECT_EQ(3, p1[1].x);
	EXPECT_EQ(2, p1[1].y);
}

TEST(Polyline, OperatorIsEqual)
{
	Polyline p1(1);
	Polyline p2(1);
	p1[0].x = 1;
	p1[0].y = 1;
	p2[0].x = 1;
	p2[0].y = 1;
	EXPECT_TRUE(p1 == p2);
}

TEST(Polyline, OperatorIsNotEqual)
{
	Polyline p1(1);
	Polyline p2(1);
	p1[0].x = 1;
	p1[0].y = 1;
	p2[0].x = 2;
	p2[0].y = 2;
	EXPECT_TRUE(p1 != p2);
}

TEST(Polyline, Operator_Assignment) 
{
	Polyline p(2), p_1(1);
	p[0].x = 1;
	p[0].y = 1;
	p_1[0].x = 25;
	p_1[0].y = 33;
	p[1].x = p_1[0].x;
	p[1].y = p_1[0].y;
	EXPECT_EQ(40, p.Length());
}

TEST(Polyline, OperaportEqual) 
{
	Polyline p1(1);
	Polyline p2(1);
	p1[0].x = 1;
	p1[0].y = 3;
	p2 = p1;
	EXPECT_EQ(1, p2[0].x);
	EXPECT_EQ(3, p2[0].y);
}