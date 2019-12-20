#pragma once


#include <cmath>



namespace mat
{
   class Vector2
   {
   public:
      Vector2() noexcept
         :_components{0,0}
      {}

      Vector2(double x,double y)
         :_components{x,y}
      {}

      double QLength() const
      {
         return _components[0]*_components[0] + _components[1]*_components[1];
      }
      
      double Length() const
      {
         return std::sqrt(QLength());
      }

      bool IsZero(double tolerance) const
      {
         return QLength() < tolerance * tolerance;
      }

      Vector2 Normalize(double tolerance) const
      {
         if (IsZero(tolerance))
            return *this;
         else
            return *this / Length();
      }

      double operator[](int index) const
      {
         return _components[index];
      }

      Vector2& operator=(const Vector2& that)
      {
         _components[0] = that[0];
         _components[1] = that[1];
         return *this;
      }

      Vector2& operator-(const Vector2& that)
      {
         _components[0] = -that[0];
         _components[1] = -that[1];
         return *this;
      }

      Vector2 operator*(double scalar) const
      {
         return Vector2((*this)[0]*scalar,
                        (*this)[0]*scalar);
      }

      Vector2 operator/(double scalar) const
      {
         return Vector2((*this)[0]/scalar,
                        (*this)[0]/scalar);
      }

      Vector2& operator+=(const Vector2& that)
      {
         _components[0] += that[0];
         _components[1] += that[1];
         return *this;
      }

      Vector2& operator-=(const Vector2& that)
      {
         _components[0] -= that[0];
         _components[1] -= that[1];
         return *this;
      }

      Vector2& operator*=(double scalar)
      {
         _components[0] *= scalar;
         _components[1] *= scalar;
         return *this;
      }

      Vector2& operator/=(double scalar)
      {
         _components[0] /= scalar;
         _components[1] /= scalar;
         return *this;
      }

      static Vector2 X()
      {
         return Vector2(1,0);
      }

      static Vector2 Y()
      {
         return Vector2(0,1);
      }

   private:
      double _components[2];
   };


   inline bool operator==(const Vector2& lhs,const Vector2& rhs)
   {
      return (lhs[0]==rhs[0]) && (lhs[1]==rhs[1]);
   }

   inline bool operator!=(const Vector2& lhs,const Vector2& rhs)
   {
      return !(lhs == rhs);
   }

   inline Vector2 operator*(double scalar, const Vector2& v)
   {
      return v * scalar;
   }

   inline Vector2 operator/(double scalar,const Vector2& v)
   {
      return v / scalar;
   }

   inline Vector2 operator+(const Vector2& v,const Vector2& w)
   {
      return Vector2(v[0] + w[0],
                     v[1] + w[1]);
   }

   inline Vector2 operator-(const Vector2& v,const Vector2& w)
   {
      return Vector2(v[0] - w[0],
                     v[1] - w[1]);
   }

   inline bool equal(const Vector2& v,const Vector2& w,double tolerance)
   {
      return (v - w).IsZero(tolerance);
   }

   //scalar product
   inline double operator*(const Vector2& v,const Vector2& w)
   {
      return v[0] * w[0] + v[1] * w[1];
   }

   //determinant of matrix
   inline double determinant(const Vector2& v,const Vector2& w)
   {
      return v[0] * w[1] - v[1] * w[0];
   }

   //lineare interpolation of 2 vectors
   //
   // Warning
   //   general NOT for all s and v, that affine(v,s,v) == v
   inline Vector2 affine(const Vector2& v,double s,const Vector2& w)
   {
      return Vector2((1.0 - s) * v[0] + s * w[0],
                     (1.0 - s) * v[1] + s * w[1]);
   }
}