#include "stdafx.h"

#include "Relation.h"
#include "Point2.h"
#include "Vector2.h"


using namespace std;
using namespace mat;


static const double tol = 1.E-10;

double mat::direction(const Point2& from,const Point2& to,const Point2& query)
{
   return determinant(query-from,to-from);
}

bool mat::is_point_on_line(const Point2& from,const Point2& to,const Point2& query)
{
   double d = direction(from,to,query);
   if (d > 0)
      return d < tol;
   else
      return -d < tol;
}

PointLineRelation mat::get_point_line_relation(const Point2& from,const Point2& to,const Point2& query)
{
   if (is_point_on_line(from,to,query))
   {
      if ((query[0]>=min(from[0],to[0]) && query[0]<=max(from[0],to[0])) &&
          (query[1]>=min(from[1],to[1]) && query[1]<=max(from[1],to[1])))
      {
         return PointLineRelation::PointOnSeq;
      }
      else
      {
         return PointLineRelation::PointOnSeqExt;
      }
   }
   else
   {
      double det = determinant(query-from,to-from);
      if (det > 0)
      {
         return PointLineRelation::RightSide;
      }
      else
      {
         return PointLineRelation::LeftSide;
      }
   }
}

bool mat::is_point_inside_line(const Point2& from,const Point2& to,const Point2& query)
{
   if (is_point_on_line(from,to,query))
   {
      if ((to-query) * (from-query) <= 0)
      {
         return true;
      }
   }

   return false;
}

PointTriangleRelation mat::is_point_inside_triangle(const Point2& A,const Point2& B,const Point2& C,const Point2& query)
{
   if (is_point_inside_line(A,B,query) ||
      is_point_inside_line(B,C,query) ||
      is_point_inside_line(C,A,query))
   {
      return PointTriangleRelation::PointOnTri;
   }
   else
   {
      if ((get_point_line_relation(A,B,query)==PointLineRelation::LeftSide) &&
         (get_point_line_relation(B,C,query)==PointLineRelation::LeftSide) &&
         (get_point_line_relation(C,A,query)==PointLineRelation::LeftSide))
      {
         return PointTriangleRelation::PointInsideTri;
      }
      else
      {
         return PointTriangleRelation::PointOutsideTri;
      }
   }
}

bool mat::segments_intersect(const Point2& A,const Point2& B,const Point2& C,const Point2& D)
{
   double d1 = direction(C,D,A);
   double d2 = direction(C,D,B);
   double d3 = direction(A,B,C);
   double d4 = direction(A,B,D);

   PointLineRelation r1 = get_point_line_relation(C,D,A);
   PointLineRelation r2 = get_point_line_relation(C,D,B);
   PointLineRelation r3 = get_point_line_relation(A,B,C);
   PointLineRelation r4 = get_point_line_relation(A,B,D);

   if (((r1==PointLineRelation::RightSide && r2==PointLineRelation::LeftSide) || (r1==PointLineRelation::LeftSide && r2==PointLineRelation::RightSide)) && 
       ((r3==PointLineRelation::RightSide && r4==PointLineRelation::LeftSide) || (r3==PointLineRelation::LeftSide && r4==PointLineRelation::RightSide)))
      return true;
   else if (r1 == PointLineRelation::PointOnSeq)
      return true;
   else if (r2 == PointLineRelation::PointOnSeq)
      return true;
   else if (r3 == PointLineRelation::PointOnSeq)
      return true;
   else if (r4 == PointLineRelation::PointOnSeq)
      return true;
   else
      return false;
}

