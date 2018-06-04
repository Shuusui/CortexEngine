#pragma once
#pragma region Internal Includes
#include "ICollider.h"
#pragma endregion 

namespace Nash
{
	class NASHEXPORT SphereCollider : public ICollider
	{
	private: 
		float m_radius;
	public:
		SphereCollider() = delete;
		SphereCollider(const FVector3& globalPosition, const FVector3& localPosition, const float& radius = 1.0f, const bool& isTrigger = false) : ICollider(globalPosition, localPosition, Enums::EColliderType::SphereCollider, isTrigger), m_radius(radius) {}
		SphereCollider(const SphereCollider& sphereCollider) :ICollider(sphereCollider.GlobalPosition(), sphereCollider.LocalPosition(), Enums::EColliderType::SphereCollider, sphereCollider.IsTrigger()), m_radius(sphereCollider.m_radius) {}
		SphereCollider(const ICollider& collider, const float& radius = 1.0f) :ICollider(collider, Enums::EColliderType::SphereCollider), m_radius(radius) {}

		float GetRadius() const { return m_radius; }

	private:
		void IntersectDynamic() final;
		void IntersectStatic() final;
		bool CheckIntersection(ICollider* coll) final;

		void DeltaUpdate() final;
		void Update() final;
		void Start() final;
	};
}