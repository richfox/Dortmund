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


//线段相对次序辅助结构
struct SegPos
{
   SegPos(int i,const Point2& from,const Point2& to)
      :i_(i),
      from_(from),
      to_(to)
   {}

   SegPos()
      :i_(0),
      from_(),
      to_()
   {}

   bool operator < (const SegPos& rhs) const
   {
      PointSegRelation r = mat::get_point_segment_relation(from_,to_,rhs.from_);
      if (r == PointSegRelation::LeftSide)
         return true;
      return false;
   }

   int i_; //所属线段序号
   Point2 from_; //左端点
   Point2 to_; //右端点
};

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

   std::set<SegPos> sTree;
   for (const auto& ep : eps)
   {
      if (ep.e_ == 0) //左端点
      {
         auto current = sTree.insert({ep.i_,segments[ep.i_].first,segments[ep.i_].second}).first;
         auto above = sTree.upper_bound(*current);
         auto below = (current==sTree.begin()) ? sTree.end() : prev(current,1);
         if ((above!=sTree.end() && segments_intersect(segments[current->i_].first,segments[current->i_].second,segments[above->i_].first,segments[above->i_].second)) ||
            (below!=sTree.end() && segments_intersect(segments[current->i_].first,segments[current->i_].second,segments[below->i_].first,segments[below->i_].second)))
            return true;
      }
      else if (ep.e_ == 1) //右端点
      {
         auto current = sTree.find({ep.i_,segments[ep.i_].first,segments[ep.i_].second});
         auto above = next(current,1);
         auto below = (current==sTree.begin()) ? sTree.end() : prev(current,1);
         if ((above!=sTree.end() && below!=sTree.end()) &&
            (segments_intersect(segments[above->i_].first,segments[above->i_].second,segments[below->i_].first,segments[below->i_].second)))
            return true;
         sTree.erase({ep.i_,segments[ep.i_].first,segments[ep.i_].second});
      }
   }

   return false;
}

