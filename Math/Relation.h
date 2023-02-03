#pragma once





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
}