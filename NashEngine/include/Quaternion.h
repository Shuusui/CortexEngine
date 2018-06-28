#pragma once
#pragma region Internal Includes
#include "internal\Defines.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix.h"
#include "BaseMath.h"
#pragma endregion 

namespace Nash
{
	class NASHEXPORT FQuaternion
	{
	private:
		FVector4 m_quaternion;
	public: 
		FQuaternion() :m_quaternion(1,1,1,1) {  }
		FQuaternion(const FVector3& euklidRot) :m_quaternion(1, euklidRot.X, euklidRot.Y, euklidRot.Z) {}
		FQuaternion(const FQuaternion& quat) :m_quaternion(quat.m_quaternion.X, quat.m_quaternion.Y, quat.m_quaternion.Z, quat.m_quaternion.W) {}

		inline void operator=(const FQuaternion& quat); 
		inline bool operator==(const FQuaternion& quat) const; 
		inline bool operator!=(const FQuaternion& quat) const;
		inline FQuaternion operator+(const FQuaternion& quat) const;
		inline FQuaternion operator-(const FQuaternion& quat) const; 
		inline FQuaternion operator*(const FQuaternion& quat) const; 
		inline FQuaternion operator/(const FQuaternion& quat) const; 
		inline FQuaternion operator+(const FVector3& vec) const; 
		inline FQuaternion operator-(const FVector3& vec) const; 
		inline FQuaternion operator*(const FVector3& vec) const; 
		inline FQuaternion operator/(const FVector3& vec) const; 
		inline void operator+=(const FQuaternion& quat); 
		inline void operator-=(const FQuaternion& quat); 
		inline void operator*=(const FQuaternion& quat); 
		inline void operator/=(const FQuaternion& quat); 
		inline void operator+=(const FVector3& vec); 
		inline void operator-=(const FVector3& vec); 
		inline void operator*=(const FVector3& vec); 
		inline void operator/=(const FVector3& vec);
	};

	inline void FQuaternion::operator=(const FQuaternion& quat)
	{

	}
	inline bool FQuaternion::operator==(const FQuaternion& quat) const
	{

	}
	inline bool FQuaternion::operator!=(const FQuaternion& quat) const
	{

	}
	inline FQuaternion FQuaternion::operator+(const FQuaternion& quat) const
	{

	}
	inline FQuaternion FQuaternion::operator-(const FQuaternion& quat) const
	{

	}
	inline FQuaternion FQuaternion::operator*(const FQuaternion& quat) const
	{

	}
	inline FQuaternion FQuaternion::operator/(const FQuaternion& quat) const
	{

	}
	inline FQuaternion FQuaternion::operator+(const FVector3& vec) const
	{

	}
	inline FQuaternion FQuaternion::operator-(const FVector3& vec) const
	{

	}
	inline FQuaternion FQuaternion::operator*(const FVector3& vec) const
	{

	}
	inline FQuaternion FQuaternion::operator/(const FVector3& vec) const
	{

	}
	inline void FQuaternion::operator+=(const FQuaternion& quat)
	{

	}
	inline void FQuaternion::operator-=(const FQuaternion& quat)
	{

	}
	inline void FQuaternion::operator*=(const FQuaternion& quat)
	{

	}
	inline void FQuaternion::operator/=(const FQuaternion& quat)
	{

	}
	inline void FQuaternion::operator+=(const FVector3& vec)
	{

	}
	inline void FQuaternion::operator-=(const FVector3& vec)
	{

	}
	inline void FQuaternion::operator*=(const FVector3& vec)
	{

	}
	inline void FQuaternion::operator/=(const FVector3& vec)
	{

	}
}