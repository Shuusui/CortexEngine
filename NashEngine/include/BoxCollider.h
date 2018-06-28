#pragma once
#pragma region Internal Includes
#include "ICollider.h"
#pragma endregion 

namespace Nash
{
	
	class NASHEXPORT BoxCollider : public ICollider
	{
	private:
		FVector3 m_bounds;
	public: 

		BoxCollider() = delete; 
		BoxCollider(const FVector3& globalPosition, const FVector3& localPosition, const FVector3& bounds = FVector3(1,1,1), const bool& isTrigger = false) :ICollider(globalPosition, localPosition, Enums::EColliderType::BoxCollider, isTrigger), m_bounds(bounds) {};
		BoxCollider(const BoxCollider& boxCollider) 
			:ICollider(boxCollider.GlobalPosition()
				, boxCollider.LocalPosition()
				, Enums::EColliderType::BoxCollider
				, boxCollider.IsTrigger())
				, m_bounds(boxCollider.m_bounds)
		{}
		BoxCollider(const ICollider& collider, const FVector3& bounds = FVector3(1, 1, 1))
			:ICollider(collider
				, Enums::EColliderType::BoxCollider)
			, m_bounds(bounds)
		{}

		FVector3 inline GetSize() const { return m_bounds; }
		FVector3 inline GetExtents() const { return m_bounds / 2; }
		
	private: 
		void IntersectDynamic() final;
		void IntersectStatic() final;
		bool CheckIntersection(ICollider* coll) final;

		void DeltaUpdate() final; 
		void Update() final;
		void Start() final;
	};
}