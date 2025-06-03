#include "stdafx.h"

#include "Relation.h"
#include "Point2.h"
#include "Vector2.h"


using namespace std;
using namespace mat;


static const double tol = 1.E-10;

double mat::direction(const Point2& from,const Point2& to,const Point2& query)
{
   //叉积等价的行列式
   return determinant(query-from,to-from);
}

bool mat::on_segment(const Point2& from,const Point2& to,const Point2& query)
{
   //叉积为0表示共线
   double d = direction(from,to,query);
   return fabs(d) < tol;
}

PointSegRelation mat::get_point_segment_relation(const Point2& from,const Point2& to,const Point2& query)
{
   if (on_segment(from,to,query))
   {
      //if ((query[0]>=min(from[0],to[0]) && query[0]<=max(from[0],to[0])) &&
      //    (query[1]>=min(from[1],to[1]) && query[1]<=max(from[1],to[1])))
      double scalar = (to - query) * (from - query);
      if (scalar < -tol) //点积为负表示方向基本相反，夹角在90°到180°之间，因为又在线段上，所以表示此点落在线段两个端点之间
      {
         return PointSegRelation::PointOnSeg;
      }
      else if (scalar > tol)//点积为正表示方向基本相同，夹角在0°到90°之间，因为又在线段上，所以表示此点和落在线段一边的延长线上
      {
         return PointSegRelation::PointOnSegExt;
      }
      else //点积为0表示正交，夹角90°，因为又在线段上，所以表示此点和一个线段端点重合
      {
         return PointSegRelation::PointOnSeg;
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


enum SegPointType : unsigned char
{
   Left = 0, //0表示左端点
   Right = 1 //1表示右端点
};

//事件点
struct EventPoint
{
   EventPoint(double x,SegPointType e,double y,int i)
      :x_(x),
      e_(e),
      y_(y),
      i_(i)
   {}

   EventPoint()
      :x_(0),
      e_(Left),
      y_(0),
      i_(0)
   {}

   //(x,e,y)字典排序
   bool operator < (const EventPoint& rhs) const
   {
      if (x_ < rhs.x_)
         return true;
      else if (x_ == rhs.x_)
         if (e_ < rhs.e_)
            return true;
         else if (e_ == rhs.e_)
            if (y_ < rhs.y_)
               return true;
      return false;
   }

   double x_;
   SegPointType e_;
   double y_;
   int i_; //所属线段序号
};

//线段在事件点的相对次序
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
         if ((seg.second[0]-seg.first[0]) < tol) //垂直线段
         {
            if (seg.first[1] < seg.second[1])
            {
               eps.push_back({seg.first[0],Left,seg.first[1],idx});
               eps.push_back({seg.second[0],Right,seg.second[1],idx});
            }
            else
            {
               eps.push_back({seg.first[0],Right,seg.first[1],idx});
               eps.push_back({seg.second[0],Left,seg.second[1],idx});
            }
         }
         else //非垂直线段
         {
            eps.push_back({seg.first[0],Left,seg.first[1],idx});
            eps.push_back({seg.second[0],Right,seg.second[1],idx});
         }
      }
      else
      {
         if ((seg.first[0]-seg.second[0]) < tol) //垂直线段
         {
            if (seg.first[1] < seg.second[1])
            {
               eps.push_back({seg.first[0],Left,seg.first[1],idx});
               eps.push_back({seg.second[0],Right,seg.second[1],idx});
            }
            else
            {
               eps.push_back({seg.first[0],Right,seg.first[1],idx});
               eps.push_back({seg.second[0],Left,seg.second[1],idx});
            }
         }
         else //非垂直线段
         {
            eps.push_back({seg.first[0],Right,seg.first[1],idx});
            eps.push_back({seg.second[0],Left,seg.second[1],idx});
         }
      }
      idx++;
   }

   std::sort(eps.begin(),eps.end());

   std::set<SegPos> sTree;
   for (const auto& ep : eps)
   {
      if (ep.e_ == Left)
      {
         auto current = sTree.insert({ep.i_,segments[ep.i_].first,segments[ep.i_].second}).first;
         auto above = sTree.upper_bound(*current);
         auto below = (current==sTree.begin()) ? sTree.end() : prev(current,1);
         if ((above!=sTree.end() && segments_intersect(segments[current->i_].first,segments[current->i_].second,segments[above->i_].first,segments[above->i_].second)) ||
            (below!=sTree.end() && segments_intersect(segments[current->i_].first,segments[current->i_].second,segments[below->i_].first,segments[below->i_].second)))
            return true;
      }
      else if (ep.e_ == Right)
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


Point2 mat::project_point_to_line(const Point2& p, const Point2& q, const mat::Vector2& n)
{
   Vector2 un = n.Normalize(tol);

   //第一个乘法是两个向量的点积，第二个是标量乘向量
   return q + (un * (p - q)) * un;
}