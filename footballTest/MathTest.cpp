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

   const double testtol = 1.E-3;

   //测试点和线段关系
   Point2 from(0,0);
   Point2 to(0,1);
   Point2 query(0,0);
   auto relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSeg);

   query = Point2(0,0.5);
   relation = get_point_segment_relation(from,to,query);
   CPPUNIT_ASSERT(relation == mat::PointOnSeg);

   query = Point2(0,1);
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
   Point2 s;
   CPPUNIT_ASSERT(segments_intersect_point(P1,P2,P3,P4,s)==1);
   CPPUNIT_ASSERT(equal(s, Point2(0.5, 0.5), testtol) == true);

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
   CPPUNIT_ASSERT(segments_intersect_point(P1,P2,P3,P4,s)==1);
   CPPUNIT_ASSERT(equal(s, Point2(0.5, 1), testtol) == true);

   P1 = Point2(0,1);
   P2 = Point2(1,1);
   P3 = Point2(2,1);
   P4 = Point2(2,2);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==false);

   P1 = Point2(0,1);
   P2 = Point2(1,1);
   P3 = Point2(0,2);
   P4 = Point2(2,2);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==false);
   CPPUNIT_ASSERT(segments_intersect_point(P1,P2,P3,P4,s)==0);

   P1 = Point2(0,1);
   P2 = Point2(1,1);
   P3 = Point2(2,1);
   P4 = Point2(3,1);
   CPPUNIT_ASSERT(segments_intersect(P1,P2,P3,P4)==false);
   CPPUNIT_ASSERT(segments_intersect_point(P1,P2,P3,P4,s)==2);

   //测试任意一对线段是否相交
   //类似算法导论图 33-5
   vector<pair<const Point2,const Point2>> segments;
   segments.push_back({{0,6},{3,5}});
   segments.push_back({{1,1},{11,6}});
   segments.push_back({{2,3},{5,4}});
   segments.push_back({{3,6},{13,2}});
   segments.push_back({{6,7},{10,5}});
   segments.push_back({{7,3},{10,0}});
   CPPUNIT_ASSERT(any_segments_intersect(segments)==true);

   //边界情况
   segments.clear();
   segments.push_back({{0,0},{2,0}});
   segments.push_back({{1,0},{2,2}});
   CPPUNIT_ASSERT(any_segments_intersect(segments)==true);

   segments.clear();
   segments.push_back({{0,0},{2,0}});
   segments.push_back({{0,2},{1,0}});
   CPPUNIT_ASSERT(any_segments_intersect(segments)==true);

   segments.clear();
   segments.push_back({{0,0},{2,2}});
   segments.push_back({{0,1},{2,1}});
   segments.push_back({{0,2},{2,0}});
   CPPUNIT_ASSERT(any_segments_intersect(segments)==true);

   segments.clear();
   segments.push_back({{0,1},{2,1}});
   segments.push_back({{1,0},{1,2}});
   CPPUNIT_ASSERT(any_segments_intersect(segments)==true);

   //测试点到线的投影
   Point2 toproject(1, 1);
   Point2 projected = project_point_to_line(toproject, Point2::Origin(), Vector2::X());
   CPPUNIT_ASSERT(equal(projected, Point2(1, 0), testtol) == true);

   projected = project_point_to_line(toproject, Point2::Origin(), Vector2::Y());
   CPPUNIT_ASSERT(equal(projected, Point2(0, 1), testtol) == true);

   projected = project_point_to_line(toproject, Point2(2, 0), Vector2::X());
   CPPUNIT_ASSERT(equal(projected, Point2(1, 0), testtol) == true);
}