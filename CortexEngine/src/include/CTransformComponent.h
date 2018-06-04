#pragma once
#pragma region Internal Includes
#include "ICComponent.h"
#include "CortexStructs.h"
#include "Matrix.h"
#include "NamespaceAlias.h"
#include "Enums.h"
#include "Vector3.h"
#pragma endregion
#pragma region External Includes
#pragma endregion 

namespace CE
{
	namespace Components
	{
		class CTransformComponent : public CECORE::ICComponent
		{
		private: 
			Physics::Transform m_transform;
			Nash::FMatrix m_matrix;
		public: 
			CTransformComponent(const Physics::Transform & transform, const uint_fast32_t& id);

			inline Nash::FVector3 GetPosition() const;
		
			inline Nash::FVector3 GetScale() const;

			void Update();

			~CTransformComponent();
		};
		inline Nash::FVector3 CTransformComponent::GetPosition() const
		{
			return m_transform.Position;
		}		
		inline Nash::FVector3 CTransformComponent::GetScale() const
		{
			return m_transform.Scale; 
		}
		inline void CTransformComponent::Update()
		{
		}
	}
}