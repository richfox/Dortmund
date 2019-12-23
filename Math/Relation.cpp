#include "stdafx.h"

#include "Relation.h"
#include "Point2.h"
#include "Vector2.h"


using namespace std;
using namespace mat;


static const double tol = 1.E-10;

bool mat::is_point_on_line(const Point2& q,const Point2& from,const Point2& to)
{
   double det = determinant(to-from,q-from);
   if (det > 0)
      return det - 0 < tol;
   else
      return -det < tol;
}

PointLineRelation mat::get_point_line_relation(const Point2& query,const Point2& from,const Point2& to)
{
   if (is_point_on_line(query,from,to))
   {
      return PointLineRelation::PointOnLine;
   }
   else
   {
      double det = determinant(to-from,query-from);
      if (det > 0)
      {
         return PointLineRelation::LeftSide;
      }
      else
      {
         return PointLineRelation::RightSide;
      }
   }
}

bool mat::is_point_inside_line(const Point2& query,const Point2& from,const Point2& to)
{
   if (is_point_on_line(query,from,to))
   {
      if ((to-query) * (from-query) <= 0)
      {
         return true;
      }
   }

   return false;
}

PointTriangleRelation mat::is_point_inside_triangle(const Point2& q,const Point2& A,const Point2& B,const Point2& C)
{
   if (is_point_inside_line(q,A,B) ||
      is_point_inside_line(q,B,C) ||
      is_point_inside_line(q,C,A))
   {
      return PointTriangleRelation::PointOnTri;
   }
   else
   {
      if ((get_point_line_relation(q,A,B)==PointLineRelation::LeftSide) &&
         (get_point_line_relation(q,B,C)==PointLineRelation::LeftSide) &&
         (get_point_line_relation(q,C,A)==PointLineRelation::LeftSide))
      {
         return PointTriangleRelation::PointInsideTri;
      }
      else
      {
         return PointTriangleRelation::PointOutsideTri;
      }
   }
}
