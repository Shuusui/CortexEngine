#pragma once
#pragma region Internal Includes
#include "BaseMath.h"
#include "Vector2.h"
#include "Vector3.h"
#pragma endregion 

namespace Nash
{
	class NASHEXPORT FVector4
	{
	public:
		float X; float Y; float Z; float W;
		FVector4() :X(0), Y(0), Z(0), W(0) {};
		FVector4(const float& x, const float& y, const float& z, const float& w) : X(x), Y(y), Z(z), W(w) {};
		FVector4(const FVector2& vec, const float& z, const float& w) : X(vec.X), Y(vec.Y), Z(z), W(w) {};
		FVector4(const FVector3& vec, const float& w) : X(vec.X), Y(vec.Y), Z(vec.Z), W(w) {};
		FVector4(const FVector4& vec) : X(vec.X), Y(vec.Y), Z(vec.Z), W(vec.W) {};

		inline void operator=(const FVector4& vec);
		inline bool operator==(const FVector4& vec) const;
		inline bool operator!=(const FVector4& vec) const;
		inline FVector4 operator+(const FVector4& vec) const;
		inline FVector4 operator-(const FVector4& vec) const;
		inline FVector4 operator*(const FVector4& vec) const;
		inline FVector4 operator/(const FVector4& vec) const;
		inline FVector4 operator+(const float& scalar) const;
		inline FVector4 operator-(const float& scalar) const;
		inline FVector4 operator*(const float& scalar) const;
		inline FVector4 operator/(const float& scalar) const;
		inline void operator+=(const FVector4& vec);
		inline void operator-=(const FVector4& vec);
		inline void operator*=(const FVector4& vec);
		inline void operator/=(const FVector4& vec);
		inline void operator+=(const float& scalar);
		inline void operator-=(const float& scalar);
		inline void operator*=(const float& scalar);
		inline void operator/=(const float& scalar);
	};
}

void Nash::FVector4::operator=(const FVector4 & vec)
{
	X = vec.X; Y = vec.Y; Z = vec.Z; W = vec.W;
}

inline bool Nash::FVector4::operator==(const FVector4 & vec) const
{
	return Nash::AbsF(X - vec.X) < EPSILON && Nash::AbsF(Y - vec.Y) < EPSILON && Nash::AbsF(Z - vec.Z) < EPSILON && Nash::AbsF(W - vec.W) < EPSILON ? true : false;
}

inline bool Nash::FVector4::operator!=(const FVector4 & vec) const
{
	return Nash::AbsF(X - vec.X) > EPSILON || Nash::AbsF(Y - vec.Y) > EPSILON || Nash::AbsF(Z - vec.Z) > EPSILON || Nash::AbsF(W - vec.W) > EPSILON ? true : false;
}

inline Nash::FVector4 Nash::FVector4::operator+(const FVector4 & vec) const
{
	return FVector4(X + vec.X, Y + vec.Y, Z + vec.Z, W + vec.W);
}

inline Nash::FVector4 Nash::FVector4::operator-(const FVector4 & vec) const
{
	return FVector4(X - vec.X, Y - vec.Y, Z - vec.Z, W - vec.W);
}

inline Nash::FVector4 Nash::FVector4::operator*(const FVector4 & vec) const
{
	return FVector4(X * vec.X, Y *vec.Y, Z * vec.Z, W * vec.W);
}

inline Nash::FVector4 Nash::FVector4::operator/(const FVector4 & vec) const
{
	return FVector4(X / vec.X, Y / vec.Y, Z / vec.Z, W / vec.W);
}

inline Nash::FVector4 Nash::FVector4::operator+(const float & scalar) const
{
	return FVector4(X + scalar, Y + scalar, Z + scalar, W + scalar);
}

inline Nash::FVector4 Nash::FVector4::operator-(const float & scalar) const
{
	return FVector4(X - scalar, Y - scalar, Z - scalar, W - scalar);
}

inline Nash::FVector4 Nash::FVector4::operator*(const float & scalar) const
{
	return FVector4(X*scalar, Y*scalar, Z*scalar, W*scalar);
}

inline Nash::FVector4 Nash::FVector4::operator/(const float & scalar) const
{
	return FVector4(X / scalar, Y / scalar, Z / scalar, W / scalar);
}

inline void Nash::FVector4::operator+=(const FVector4 & vec)
{
	X += vec.X; Y += vec.Y; Z += vec.Z; W += vec.W;
}

inline void Nash::FVector4::operator-=(const FVector4 & vec)
{
	X -= vec.X; Y -= vec.Y; Z -= vec.Z; W -= vec.W;
}

inline void Nash::FVector4::operator*=(const FVector4 & vec)
{
	X *= vec.X; Y *= vec.Y; Z *= vec.Z; W *= vec.W;
}

inline void Nash::FVector4::operator/=(const FVector4 & vec)
{
	X /= vec.X; Y /= vec.Y; Z /= vec.Z; W /= vec.W;
}

inline void Nash::FVector4::operator+=(const float & scalar)
{
	X += scalar; Y += scalar; Z += scalar; W += scalar;
}

inline void Nash::FVector4::operator-=(const float & scalar)
{
	X -= scalar; Y -= scalar; Z -= scalar; W -= scalar;
}

inline void Nash::FVector4::operator*=(const float & scalar)
{
	X *= scalar; Y *= scalar; Z *= scalar; W *= scalar;
}

inline void Nash::FVector4::operator/=(const float & scalar)
{
	X /= scalar; Y /= scalar; Z /= scalar; W /= scalar;
}
