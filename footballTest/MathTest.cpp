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

   //测试点和线段关系
   Point2 from(0,0);
   Point2 to(0,1);
   Point2 query(0,0);
   auto relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSeg);

   query = Point2(0,0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSeg);

   query = Point2(0,1.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSegExt);

   query = Point2(0,-0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSegExt);

   query = Point2(-0.5,0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::LeftSide);

   query = Point2(-0.5,-0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::LeftSide);

   query = Point2(0.5,0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::RightSide);

   query = Point2(0.5,-0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::RightSide);

   //测试点和三角形关系
   Point2 A(0,0);
   Point2 B(1,0);
   Point2 C(1,1);
   query = Point2(0.5,0.5);
   auto relation2 = is_point_inside_triangle(A,B,C,query);
   CPPUNIT_ASSERT(relation2 == mat::PointOnTri);

   query = Point2(1,1);
   relation2 = is_point_inside_triangle(A,B,C,query);
   CPPUNIT_ASSERT(relation2 == mat::PointOnTri);

   query = Point2(0.5,0.3);
   relation2 = is_point_inside_triangle(A,B,C,query);
   CPPUNIT_ASSERT(relation2 == mat::PointInsideTri);

   query = Point2(0.5,0.7);
   relation2 = is_point_inside_triangle(A,B,C,query);
   CPPUNIT_ASSERT(relation2 == mat::PointOutsideTri);

   query = Point2(-0.5,-0.5);
   relation2 = is_point_inside_triangle(A,B,C,query);
   CPPUNIT_ASSERT(relation2 == mat::PointOutsideTri);

   //测试两个线段是否相交
   Point2 P1(0,1);
   Point2 P2(1,0);
   Point2 P3(0,0);
   Point2 P4(1,1);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==true);

   P1 = Point2(0,1);
   P2 = Point2(0.5,1);
   P3 = Point2(0,0);
   P4 = Point2(1,1);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==false);

   P1 = Point2(0,1);
   P2 = Point2(1,1);
   P3 = Point2(0.5,1);
   P4 = Point2(1,2);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==true);

   P1 = Point2(0,1);
   P2 = Point2(1,1);
   P3 = Point2(2,1);
   P4 = Point2(2,2);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==false);
}