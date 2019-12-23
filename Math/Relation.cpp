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
      if ((to-query) * (from-query) <= 0)
      {
         return PointLineRelation::PointInsideLine;
      }
      else
      {
         return PointLineRelation::PointOnLine;
      }
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