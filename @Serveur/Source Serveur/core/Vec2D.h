#ifndef CORE_VEC2D_H
#define CORE_VEC2D_H


#include "CoreBase.h"


BEGIN_NAMESPACE_CORE
{

	template <class T>
	class CVec2D
	{
	public:

		T X;
		T Y;

		CVec2D()
			: X(0)
			, Y(0)
		{
		}

		CVec2D(T _x, T _y = 0)
			: X(_x)
			, Y(_y)
		{
		}

		T length() const
		{
			return sqrtf(lengthSq());
		}

		T lengthSq() const
		{
			return pow2(X) + pow2(Y);
		}

		bool isInRange(const CVec2D &_vec, T _range) const
		{
			return ((_vec - *this).lengthSq() <= pow2(_range));
		}

		bool isInRangeSq(const CVec2D &_vec, T _rangeSq) const
		{
			return ((_vec - *this).lengthSq() <= _rangeSq);
		}

		void normalize()
		{
			T t_length = length();

			if (t_length > 0)
			{
				X /= t_length;
				Y /= t_length;
			}
		}

		bool operator == (const CVec2D &_vector) const
		{
			return (X == _vector.X &&
				Y == _vector.Y);
		}

		bool operator != (const CVec2D &_vector) const
		{
			return !(*this == _vector);
		}

		bool operator < (const CVec2D &_vector) const
		{
			return (X < _vector.X &&
				Y < _vector.Y);
		}

		bool operator > (const CVec2D &_vector) const
		{
			return (X > _vector.X &&
				Y > _vector.Y);
		}

		bool operator <= (const CVec2D &_vector) const
		{
			return (X <= _vector.X &&
				Y <= _vector.Y);
		}

		bool operator >= (const CVec2D &_vector) const
		{
			return (X >= _vector.X &&
				Y >= _vector.Y);
		}

		CVec2D operator + (const CVec2D &_vector) const
		{
			return CVec2D(X + _vector.X, Y + _vector.Y);
		}

		CVec2D operator - (const CVec2D &_vector) const
		{
			return CVec2D(X - _vector.X, Y - _vector.Y);
		}

		CVec2D operator * (const CVec2D &_vector) const
		{
			return CVec2D(X * _vector.X, Y * _vector.Y);
		}

		CVec2D operator / (const CVec2D &_vector) const
		{
			return CVec2D(X / _vector.X, Y / _vector.Y);
		}

		CVec2D operator * (T _value) const
		{
			return CVec2D(X * _value, Y * _value);
		}

		CVec2D operator / (T _value) const
		{
			return CVec2D(X / _value, Y / _value);
		}

		CVec2D &operator += (const CVec2D &_vector)
		{
			X += _vector.X;
			Y += _vector.Y;
			return *this;
		}

		CVec2D &operator -= (const CVec2D &_vector)
		{
			X -= _vector.X;
			Y -= _vector.Y;
			return *this;
		}

		CVec2D &operator *= (const CVec2D &_vector)
		{
			X *= _vector.X;
			Y *= _vector.Y;
			return *this;
		}

		CVec2D &operator /= (const CVec2D &_vector)
		{
			X /= _vector.X;
			Y /= _vector.Y;
			return *this;
		}

		CVec2D &operator *= (T _value)
		{
			X *= _value;
			Y *= _value;
			return *this;
		}

		CVec2D &operator /= (T _value)
		{
			X /= _value;
			Y /= _value;
			return *this;
		}

	};

};


#endif //CORE_VEC2D_H
