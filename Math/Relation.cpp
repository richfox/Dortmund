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
      return PointLineRelation::PointOnLine;
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

