#pragma once





namespace mat
{
   class Point2;
   class Vector2;

   //点在线的哪一边
   enum PointLineRelation
   {
      Relation_Unknown = -1,
      PointOnLine,     //点在线段延长线上
      PointInsideLine, //点在线段内
      LeftSide,        //点在线段左侧
      RightSide        //点在线段右侧
   };

   bool is_point_on_line(const Point2& q,const Point2& from,const Point2& to,double tolerance);
   PointLineRelation get_point_line_relation(const Point2& query,const Point2& from,const Point2& to,double tolerance);
}