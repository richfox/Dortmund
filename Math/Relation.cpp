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

bool mat::on_segment(const Point2& from,const Point2& to,const Point2& query)
{
   double d = direction(from,to,query);
   if (d > 0)
      return d < tol;
   else
      return -d < tol;
}

PointSegRelation mat::get_point_segment_relation(const Point2& from,const Point2& to,const Point2& query)
{
   if (on_segment(from,to,query))
   {
      //if ((query[0]>=min(from[0],to[0]) && query[0]<=max(from[0],to[0])) &&
      //    (query[1]>=min(from[1],to[1]) && query[1]<=max(from[1],to[1])))
      if ((to-query) * (from-query) <= 0)
      {
         return PointSegRelation::PointOnSeg;
      }
      else
      {
         return PointSegRelation::PointOnSegExt;
      }
   }
   else
   {
      double det = direction(from,to,query);
      if (det > 0)
      {
         return PointSegRelation::RightSide;
      }
      else
      {
         return PointSegRelation::LeftSide;
      }
   }
}


PointTriangleRelation mat::is_point_inside_triangle(const Point2& A,const Point2& B,const Point2& C,const Point2& query)
{
   PointSegRelation r1 = get_point_segment_relation(A,B,query);
   PointSegRelation r2 = get_point_segment_relation(B,C,query);
   PointSegRelation r3 = get_point_segment_relation(C,A,query);
   
   if (r1==PointSegRelation::PointOnSeg || r2==PointSegRelation::PointOnSeg || r3==PointSegRelation::PointOnSeg)
   {
      return PointTriangleRelation::PointOnTri;
   }
   else
   {
      if (r1==PointSegRelation::LeftSide && r2==PointSegRelation::LeftSide && r3==PointSegRelation::LeftSide)
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
   PointSegRelation r1 = get_point_segment_relation(C,D,A);
   PointSegRelation r2 = get_point_segment_relation(C,D,B);
   PointSegRelation r3 = get_point_segment_relation(A,B,C);
   PointSegRelation r4 = get_point_segment_relation(A,B,D);

   if (((r1==PointSegRelation::RightSide && r2==PointSegRelation::LeftSide) || (r1==PointSegRelation::LeftSide && r2==PointSegRelation::RightSide)) && 
       ((r3==PointSegRelation::RightSide && r4==PointSegRelation::LeftSide) || (r3==PointSegRelation::LeftSide && r4==PointSegRelation::RightSide)))
      return true;
   else if (r1 == PointSegRelation::PointOnSeg)
      return true;
   else if (r2 == PointSegRelation::PointOnSeg)
      return true;
   else if (r3 == PointSegRelation::PointOnSeg)
      return true;
   else if (r4 == PointSegRelation::PointOnSeg)
      return true;
   else
      return false;
}



bool mat::any_segments_intersect(const std::vector<std::pair<const Point2, const Point2>>& segments)
{
   std::vector<EventPoint> eps;
   eps.reserve(segments.size() * 2);
   int idx = 0;
   for (const auto& seg : segments)
   {
      if (seg.first[0] < seg.second[0])
      {
         EventPoint lp(seg.first[0],0,seg.first[1],idx);
         eps.push_back(lp);
         EventPoint rp(seg.second[0],1,seg.second[1],idx);
         eps.push_back(rp);
      }
      else
      {
         EventPoint rp(seg.first[0],1,seg.first[1],idx);
         eps.push_back(rp);
         EventPoint lp(seg.second[0],0,seg.second[1],idx);
         eps.push_back(lp);
      }
      idx++;
   }

   std::sort(eps.begin(),eps.end());

   std::set<int> segTree;
   for (const auto& ep : eps)
   {
      if (ep.e_ == 0)
      {
         auto current = segTree.insert(ep.i_).first;
         auto above = segTree.lower_bound(*current);
         auto below = --current;
         if ((above!=segTree.end() && segments_intersect(segments[*current].first,segments[*current].second,segments[*above].first,segments[*above].second)) ||
            (below!=segTree.end() && segments_intersect(segments[*current].first,segments[*current].second,segments[*below].first,segments[*below].second)))
            return true;
      }
      else
      {
         auto current = segTree.find(ep.i_);
         auto above = ++current;
         auto below = --current;
         if ((above!=segTree.end() && below!=segTree.end()) &&
            (segments_intersect(segments[*above].first,segments[*above].second,segments[*below].first,segments[*below].second)))
            return true;
         segTree.erase(ep.i_);
      }
   }

   return false;
}

