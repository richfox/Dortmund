//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include "MathTest.h"
#include "..\Math\Point2.h"
#include "..\Math\Vector2.h"
#include "..\Math\Relation.h"


using namespace std;
using namespace mat;

CPPUNIT_TEST_SUITE_REGISTRATION(MathTest);



void MathTest::test()
{
   cout << "\r\ntest math functions...\r\n" << endl;

   //测试点和线关系
   Point2 from(0,0);
   Point2 to(0,1);
   Point2 query(0,0);
   CPPUNIT_ASSERT(is_point_inside_line(query,from,to) == true);
   auto relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointOnLine);

   query = Point2(0,0.5);
   CPPUNIT_ASSERT(is_point_inside_line(query,from,to) == true);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointOnLine);

   query = Point2(0,1.5);
   CPPUNIT_ASSERT(is_point_inside_line(query,from,to) == false);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointOnLine);

   query = Point2(0,-0.5);
   CPPUNIT_ASSERT(is_point_inside_line(query,from,to) == false);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointOnLine);

   query = Point2(-0.5,0.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::LeftSide);

   query = Point2(-0.5,-0.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::LeftSide);

   query = Point2(0.5,0.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::RightSide);

   query = Point2(0.5,-0.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::RightSide);

   //测试点和三角形关系
   Point2 A(0,0);
   Point2 B(1,0);
   Point2 C(1,1);
   query = Point2(0.5,0.5);
   auto relation2 = is_point_inside_triangle(query,A,B,C);
   CPPUNIT_ASSERT(relation2 == mat::PointOnTri);

   query = Point2(1,1);
   relation2 = is_point_inside_triangle(query,A,B,C);
   CPPUNIT_ASSERT(relation2 == mat::PointOnTri);

   query = Point2(0.5,0.3);
   relation2 = is_point_inside_triangle(query,A,B,C);
   CPPUNIT_ASSERT(relation2 == mat::PointInsideTri);

   query = Point2(0.5,0.7);
   relation2 = is_point_inside_triangle(query,A,B,C);
   CPPUNIT_ASSERT(relation2 == mat::PointOutsideTri);

   query = Point2(-0.5,-0.5);
   relation2 = is_point_inside_triangle(query,A,B,C);
   CPPUNIT_ASSERT(relation2 == mat::PointOutsideTri);
}