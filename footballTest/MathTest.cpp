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

   Point2 from(0,0);
   Point2 to(0,1);
   Point2 query(0,0);
   auto relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointInsideLine);

   query = Point2(0,0.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointInsideLine);

   query = Point2(0,1.5);
   relation = get_point_line_relation(query,from,to);
   CPPUNIT_ASSERT(relation == mat::PointOnLine);

   query = Point2(0,-0.5);
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
}