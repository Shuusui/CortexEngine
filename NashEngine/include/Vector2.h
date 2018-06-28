#pragma once
#pragma region Internal Includes
#include "BaseMath.h"
#include "internal\Defines.h"
#pragma endregion 


namespace Nash
{
	class NASHEXPORT FVector2
	{
	public:
		float X, Y;

		FVector2() :X(0), Y(0) {};
		FVector2(const float& x, const float& y) : X(x), Y(y) {};
		FVector2(const FVector2& vec) : X(vec.X), Y(vec.Y) {};

		inline void operator=(const FVector2& vec);
		inline bool operator==(const FVector2& vec) const;
		inline bool operator!=(const FVector2& vec) const;
		inline FVector2 operator+(const FVector2& vec) const;
		inline FVector2 operator-(const FVector2& vec) const;
		inline FVector2 operator*(const FVector2& vec) const;
		inline FVector2 operator/(const FVector2& vec) const;
		inline FVector2 operator+(const float& scalar) const;
		inline FVector2 operator-(const float& scalar) const;
		inline FVector2 operator*(const float& scalar) const;
		inline FVector2 operator/(const float& scalar) const;

		inline void operator+=(const FVector2& vec);
		inline void operator-=(const FVector2& vec);
		inline void operator*=(const FVector2& vec);
		inline void operator/=(const FVector2& vec);
		inline void operator+=(const float& scalar);
		inline void operator-=(const float& scalar);
		inline void operator*=(const float& scalar);
		inline void operator/=(const float& scalar);

	};
}

void Nash::FVector2::operator=(const FVector2 & vec)
{
	X = vec.X; Y = vec.Y;
}

bool Nash::FVector2::operator==(const FVector2 & vec) const
{
	return Nash::AbsF(X - vec.X) < EPSILON && Nash::AbsF(Y - vec.Y) < EPSILON ? true : false;
}

bool Nash::FVector2::operator!=(const FVector2 & vec) const
{
	return Nash::AbsF(X - vec.X) > EPSILON || Nash::AbsF(Y - vec.Y) > EPSILON ? true : false;
}

Nash::FVector2 Nash::FVector2::operator+(const FVector2 & vec) const
{
	return FVector2(X + vec.X, Y + vec.Y);
}

Nash::FVector2 Nash::FVector2::operator-(const FVector2 & vec) const
{
	return FVector2(X - vec.X, Y - vec.Y);
}

Nash::FVector2 Nash::FVector2::operator*(const FVector2 & vec) const
{
	return FVector2(X*vec.X, Y*vec.Y);
}

Nash::FVector2 Nash::FVector2::operator/(const FVector2 & vec) const
{
	return FVector2(X / vec.X, Y / vec.Y);
}

Nash::FVector2 Nash::FVector2::operator+(const float & scalar) const
{
	return FVector2(X + scalar, Y + scalar);
}

Nash::FVector2 Nash::FVector2::operator-(const float & scalar) const
{
	return FVector2(X - scalar, Y - scalar);
}

Nash::FVector2 Nash::FVector2::operator*(const float & scalar) const
{
	return FVector2(X*scalar, Y*scalar);
}

Nash::FVector2 Nash::FVector2::operator/(const float & scalar) const
{
	return FVector2(X / scalar, Y / scalar);
}

void Nash::FVector2::operator+=(const FVector2 & vec)
{
	X += vec.X; Y += vec.Y;
}

void Nash::FVector2::operator-=(const FVector2 & vec)
{
	X -= vec.X; Y -= vec.Y;
}

void Nash::FVector2::operator*=(const FVector2 & vec)
{
	X *= vec.X; Y *= vec.Y;
}

void Nash::FVector2::operator/=(const FVector2 & vec)
{
	X /= vec.X; Y /= vec.Y;
}

void Nash::FVector2::operator+=(const float & scalar)
{
	X += scalar; Y += scalar;
}

void Nash::FVector2::operator-=(const float & scalar)
{
	X -= scalar; Y -= scalar;
}

void Nash::FVector2::operator*=(const float & scalar)
{
	X *= scalar; Y *= scalar;
}

void Nash::FVector2::operator/=(const float & scalar)
{
	X /= scalar; Y /= scalar;
}
