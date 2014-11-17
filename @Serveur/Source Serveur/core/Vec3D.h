#ifndef CORE_VEC3D_H
#define CORE_VEC3D_H


#include "CoreBase.h"
#include "Vec2D.h"
#include "Util.h"


BEGIN_NAMESPACE_CORE
{

	template <class T>
	class CVec3D
	{
	public:

		T X;
		T Y;
		T Z;

		CVec3D()
			: X(0)
			, Y(0)
			, Z(0)
		{
		}

		CVec3D(T _x, T _y = 0, T _z = 0)
			: X(_x)
			, Y(_y)
			, Z(_z)
		{
		}

		T length() const
		{
			return sqrtf(lengthSq());
		}

		T lengthSq() const
		{
			return pow2(X) + pow2(Y) + pow2(Z);
		}

		void normalize()
		{
			T t_length = length();

			if (t_length > 0)
			{
				X /= t_length;
				Y /= t_length;
				Z /= t_length;
			}
		}

		bool isInRange(const CVec3D &_vec, T _range) const
		{
			return ((_vec - *this).lengthSq() <= pow2(_range));
		}

		bool isInRangeSq(const CVec3D &_vec, T _rangeSq) const
		{
			return ((_vec - *this).lengthSq() <= _rangeSq);
		}

		CVec2D<T> getXY() const
		{
			return CVec2D<T>(X, Y);
		}

		CVec2D<T> getXZ() const
		{
			return CVec2D<T>(X, Z);
		}

		CVec2D<T> getYZ() const
		{
			return CVec2D<T>(Y, Z);
		}

		bool operator == (const CVec3D &_vector) const
		{
			return (X == _vector.X &&
				Y == _vector.Y &&
				Z == _vector.Z);
		}

		bool operator != (const CVec3D &_vector) const
		{
			return !(*this == _vector);
		}

		bool operator < (const CVec3D &_vector) const
		{
			return (X < _vector.X &&
				Y < _vector.Y &&
				Z < _vector.Z);
		}

		bool operator > (const CVec3D &_vector) const
		{
			return (X > _vector.X &&
				Y > _vector.Y &&
				Z > _vector.Z);
		}

		bool operator <= (const CVec3D &_vector) const
		{
			return (X <= _vector.X &&
				Y <= _vector.Y &&
				Z <= _vector.Z);
		}

		bool operator >= (const CVec3D &_vector) const
		{
			return (X >= _vector.X &&
				Y >= _vector.Y &&
				Z >= _vector.Z);
		}

		CVec3D operator + (const CVec3D &_vector) const
		{
			return CVec3D(X + _vector.X, Y + _vector.Y, Z + _vector.Z);
		}

		CVec3D operator - (const CVec3D &_vector) const
		{
			return CVec3D(X - _vector.X, Y - _vector.Y, Z - _vector.Z);
		}

		CVec3D operator * (const CVec3D &_vector) const
		{
			return CVec3D(X * _vector.X, Y * _vector.Y, Z * _vector.Z);
		}

		CVec3D operator / (const CVec3D &_vector) const
		{
			return CVec3D(X / _vector.X, Y / _vector.Y, Z / _vector.Z);
		}

		CVec3D operator * (T _value) const
		{
			return CVec3D(X * _value, Y * _value, Z *_value);
		}

		CVec3D operator / (T _value) const
		{
			return CVec3D(X / _value, Y / _value, Z / _value);
		}

		CVec3D &operator += (const CVec3D &_vector)
		{
			X += _vector.X;
			Y += _vector.Y;
			Z += _vector.Z;
			return *this;
		}

		CVec3D &operator -= (const CVec3D &_vector)
		{
			X -= _vector.X;
			Y -= _vector.Y;
			Z -= _vector.Z;
			return *this;
		}

		CVec3D &operator *= (const CVec3D &_vector)
		{
			X *= _vector.X;
			Y *= _vector.Y;
			Z *= _vector.Z;
			return *this;
		}

		CVec3D &operator /= (const CVec3D &_vector)
		{
			X /= _vector.X;
			Y /= _vector.Y;
			Z /= _vector.Z;
			return *this;
		}

		CVec3D &operator *= (T _value)
		{
			X *= _value;
			Y *= _value;
			Z *= _value;
			return *this;
		}

		CVec3D &operator /= (T _value)
		{
			X /= _value;
			Y /= _value;
			Z /= _value;
			return *this;
		}

		static CVec3D randomPosition(const CVec3D &_center, T _range)
		{
			return CVec3D(
				_center.X - _range + _range * 2 * randomf(),
				_center.Y,
				_center.Z - _range + _range * 2 * randomf());
		}

	};

};


#endif //CORE_VEC3D_H
