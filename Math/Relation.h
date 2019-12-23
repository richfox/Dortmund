#pragma once





namespace mat
{
   class Point2;
   class Vector2;

   //判断点在线的哪一边
   enum PointLineRelation
   {
      PointLineRelation_Unknown = -1,
      PointOnLine,     //点在线段上(延长线或线段内不知)
      LeftSide,        //点在线段左侧
      RightSide        //点在线段右侧
   };

   bool is_point_on_line(const Point2& q,const Point2& from,const Point2& to);
   bool is_point_inside_line(const Point2& query,const Point2& from,const Point2& to);
   PointLineRelation get_point_line_relation(const Point2& query,const Point2& from,const Point2& to);

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
   PointTriangleRelation is_point_inside_triangle(const Point2& q,const Point2& A,const Point2& B,const Point2& C);
}