#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iterator>


namespace mat
{
   class Point2;
   class Vector2;

   //辅助函数
   double direction(const Point2& from,const Point2& to,const Point2& query);
   bool on_segment(const Point2& from,const Point2& to,const Point2& query);
   
   //判断点在线段的哪一边
   enum PointSegRelation
   {
      Relation_Unknown = -1,
      PointOnSeg,      //点在线段内
      PointOnSegExt,   //点在线段的延长线上
      LeftSide,        //点在线段左侧
      RightSide        //点在线段右侧
   };
   PointSegRelation get_point_segment_relation(const Point2& from,const Point2& to,const Point2& query);

   //判断点在三角形内
   //*******C/\
   //*******/  \
   //*****A/____\B
   enum PointTriangleRelation
   {
      PointTriangleRelation_Unknown = -1,
      PointOnTri,     //点在三角形边上
      PointInsideTri, //点在三角形内
      PointOutsideTri //点在三角形外
   };
   PointTriangleRelation is_point_inside_triangle(const Point2& A,const Point2& B,const Point2& C,const Point2& query);

   //判断两个线段是否相交
   //******A\  /D
   //********\/
   //********/\ 
   //******C/  \B
   bool segments_intersect(const Point2& A,const Point2& B,const Point2& C,const Point2& D);

   //线段端点辅助结构
   struct EventPoint
   {
      EventPoint(double x,short e,double y,int i)
         :x_(x),
         e_(e),
         y_(y),
         i_(i)
      {}

      EventPoint()
         :x_(0),
         e_(0),
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
      short e_; //e=0表示左端点，e=1表示右端点
      double y_;
      int i_; //所属线段序号
   };

   //判断任意一对线段是否相交
   bool any_segments_intersect(const std::vector<std::pair<const Point2,const Point2>>& segments);
}