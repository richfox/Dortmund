#pragma once


#include "Vector2.h"


namespace mat
{
   class Point2
   {
   public:
      Point2() noexcept
         :_components{0,0}
      {}

      Point2(double x,double y)
         :_components{x,y}
      {}

      double operator[](int index) const
      {
         return _components[index];
      }

      Point2& operator=(const Point2& that)
      {
         _components[0] = that._components[0];
         _components[1] = that._components[1];
         return *this;
      }

      Point2 operator+(const Vector2& v) const
      {
         return Point2((*this)[0] + v[0],
                       (*this)[1] + v[1]);
      }

      Point2 operator-(const Vector2& v) const
      {
         return Point2((*this)[0] - v[0],
                       (*this)[1] - v[1]);
      }

      Point2& operator+=(const Vector2& v)
      {
         _components[0] += v[0];
         _components[1] += v[1];
         return *this;
      }

      Point2& operator-=(const Vector2& v)
      {
         _components[0] -= v[0];
         _components[1] -= v[1];
         return *this;
      }

      static Point2 Origin();

   private:
      double _components[2];
   };

   inline Point2 Point2::Origin()
   {
      return Point2();
   }

   inline bool operator==(const Point2& lhs, const Point2& rhs)
   {
      return (lhs[0]==rhs[0]) && (lhs[1]==rhs[1]);
   }

   inline bool operator!=(const Point2& lhs, const Point2& rhs)
   {
      return !(lhs == rhs);
   }

   inline Point2 operator+(const Vector2& v,const Point2& p)
   {
      return p + v;
   }

   inline Vector2 operator-(const Point2& p,const Point2& q)
   {
      return Vector2(p[0] - q[0],
                     p[1] - q[1]);
   }

   inline bool equal(const Point2& p,const Point2& q,double tolerance)
   {
      return (p - q).IsZero(tolerance);
   }

   inline Point2 mid(const Point2& p,const Point2& q)
   {
      return Point2(0.5 * (p[0] + q[0]),
                    0.5 * (p[1] + q[1]));
   }

   //lineare interpolation of 2 points
   //
   // Warning
   //   general NOT for all s and p, that affine(p,s,p) == p
   inline Point2 affine(const Point2& p,double s,const Point2& q)
   {
      return Point2((1.0 - s) * p[0] + s * q[0],
                    (1.0 - s) * p[1] + s * q[1]);
   }
}

