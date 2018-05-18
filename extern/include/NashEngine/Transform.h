#pragma once

#pragma region Internal Includes
#include "Vector3.h"
#include "Vector4.h"
#pragma endregion 

namespace Nash
{
	class Transform
	{
	private:
		FVector3 m_position; 
		FVector3 m_localPosition;
		FVector4 m_rotation;
		FVector3 m_scale; 
	public: 
		Transform() = delete; 
		Transform(const FVector3& position, const FVector4& rotation, const FVector3& scale) :m_position(position), m_rotation(rotation), m_scale(scale), m_localPosition(position) {}
		Transform(const FVector3& position, const FVector3& localPosition, const FVector4& rotation, const FVector3 scale) :m_position(position), m_localPosition(localPosition), m_rotation(rotation), m_scale(scale) {}
		Transform(const Transform& transform) :m_position(transform.m_position), m_rotation(transform.m_rotation), m_scale(transform.m_scale) {}

		FVector3 Position() const { return m_position; }
		FVector4 Rotation() const { return m_rotation; }
		FVector3 Scale() const { return m_scale; }
		FVector3 LocalPos() const { return m_localPosition; }

	};
}