#pragma once

#pragma region Internal Includes
#include "ICollider.h"
#pragma endregion 

namespace Nash
{
	class __declspec(dllexport) CapsuleCollider : public ICollider
	{
	private: 
		float m_radius; 
		float m_height; 
	public: 
		CapsuleCollider() = delete; 
		CapsuleCollider(const FVector3& globalPosition, const FVector3& localPosition, const float& radius = 1.0f, const float& height = 1.0f, const bool& isTrigger = false) :ICollider(globalPosition, localPosition, Enums::ColliderType::CapsuleCollider, isTrigger), m_radius(radius), m_height(height) {}
		CapsuleCollider(const CapsuleCollider& capCollider) :ICollider(capCollider.GlobalPosition(), capCollider.LocalPosition(), Enums::ColliderType::CapsuleCollider, capCollider.IsTrigger()), m_radius(capCollider.m_radius), m_height(capCollider.m_radius) {}
		CapsuleCollider(const ICollider& collider, const float& radius = 1.0f, const float& height = 1.0f) :ICollider(collider, Enums::ColliderType::CapsuleCollider), m_radius(radius), m_height(height) {}

		float GetRadius() const { m_radius; }
		float GetHeight() const { m_height; }
	};
}