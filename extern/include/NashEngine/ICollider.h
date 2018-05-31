#pragma once
#pragma region Internal Includes
#include "BaseMath.h"
#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Enums.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <vector>
#include <list>
#pragma endregion 

namespace Nash
{
	class NASHEXPORT ICollider
	{
	private:
		FVector3 m_globalPosition;
		FVector3 m_localPosition;
		bool m_bIsTrigger;
		Rigidbody* m_rigidbody;
		Enums::ColliderType m_collType;
		bool m_bIsStatic;
	protected:
		std::vector<ICollider*> m_nearStaticCollider; 
		std::list<ICollider*> m_nearDynamicCollider;
	public:
		/**
		* Default constructor deleted because every Collider needs global position, local position and isTrigger assignment. 
		*/
		ICollider() = delete; 
		/**
		* The base Interface class of the collider
		* 
		* @param globalPosition The global position of the collider depends on the position of the object and the offset to the object, which owns this collider.
		* @param localPosition The local position of the collider depends on the position to the object which own this collider. 
		* @param isTrigger Turn this on to disable collision with this object and enable trigger you can use for effects. (Default = false)
		*/
		ICollider(const FVector3& globalPosition, const FVector3& localPosition, const Enums::ColliderType& collType, const bool& isTrigger = false, const bool& isStatic = false) 
			:m_globalPosition(globalPosition)
			, m_localPosition(localPosition)
			, m_bIsTrigger(isTrigger)
			, m_collType(collType) 
			, m_bIsStatic(isStatic)
		{};
		/**
		* Copy constructor
		* 
		* @param collider The collider which should be copied in this collider
		*/
		ICollider(const ICollider& collider, const Enums::ColliderType& collType)
			:m_globalPosition(collider.m_globalPosition)
			, m_localPosition(collider.m_localPosition)
			, m_bIsTrigger(collider.m_bIsTrigger)
			, m_collType(collType)
			, m_bIsStatic(collider.m_bIsStatic)

		{};

		ICollider(const ICollider& collider) = delete;

		bool IsTrigger() const { return m_bIsTrigger; }
		bool IsStatic() const { return m_bIsStatic; }
		FVector3 GlobalPosition() const { return m_globalPosition; }
		FVector3 LocalPosition() const { return m_localPosition; }
		Enums::ColliderType Type() const { return m_collType; }

		void SetIsTrigger(const bool& isTrigger) { m_bIsTrigger = isTrigger; }
		void SetRigidbody(Rigidbody* rigidbody) { m_rigidbody = rigidbody; }
		void SetIsStatic(const bool& isStatic) { m_bIsStatic = isStatic; }

		virtual ~ICollider() { delete m_rigidbody; };
		inline void AddNearCollider(ICollider* coll);
		void RemoveNearCollider(ICollider* coll);

	protected:
		virtual void DeltaUpdate() = 0;
		virtual void Update() = 0;
		virtual void Start();
		virtual void IntersectDynamic() = 0;
		virtual void IntersectStatic() = 0;
		virtual bool CheckIntersection(ICollider* coll) = 0;
	private: 
	};


	inline void ICollider::Start()
	{
		IntersectStatic();
	}

	inline void ICollider::AddNearCollider(ICollider* coll)
	{
		if (coll->IsStatic())
			m_nearStaticCollider.push_back(coll);
		else
			m_nearDynamicCollider.push_back(coll);
	}
	void ICollider::RemoveNearCollider(ICollider* coll)
	{
		if (coll->IsStatic())
		{
			for (std::vector<ICollider*>::iterator it; it != m_nearStaticCollider.end(); ++it)
			{
				if (*it == coll)
				{
					m_nearStaticCollider.erase(it);
				}
			}
		}
		else
		{
			for (std::list<ICollider*>::iterator it; it != m_nearDynamicCollider.end(); ++it)
			{
				if (*it == coll)
				{
					m_nearDynamicCollider.erase(it);
				}
			}
		}
	}
}