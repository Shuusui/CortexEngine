#pragma once
#pragma region Internal Includes
#include "ICollider.h"
#pragma endregion 

namespace Nash
{
	class __declspec(dllexport) BoxCollider : public ICollider
	{
	private:
		FVector3 m_bounds; 

	public: 
		BoxCollider() = delete; 
		BoxCollider(const FVector3& globalPosition, const FVector3& localPosition, const FVector3& bounds = FVector3(1.0f,1.0f,1.0f), const bool& isTrigger = false) :ICollider(globalPosition, localPosition, Enums::ColliderType::BoxCollider, isTrigger), m_bounds(bounds) {};
		BoxCollider(const BoxCollider& boxCollider) :ICollider(boxCollider.GlobalPosition(), boxCollider.LocalPosition(), Enums::ColliderType::BoxCollider, boxCollider.IsTrigger()), m_bounds(boxCollider.m_bounds) {}
		BoxCollider(const ICollider& collider, const FVector3& bounds = FVector3(1.0f,1.0f,1.0f)) :ICollider(collider, Enums::ColliderType::BoxCollider), m_bounds(bounds) {}

		FVector3 GetBounds() const { return m_bounds; }

		bool EnterCollision(ICollider* (*obj)()); 

	private: 
		void DeltaUpdate() final; 
		void Update() final;
	};
}