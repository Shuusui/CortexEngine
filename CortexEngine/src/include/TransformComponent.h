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
	namespace Physics
	{
		class TransformComponent : public CECORE::ICComponent
		{
		private: 
			Transform m_transform;
			Nash::FMatrix m_matrix;
		public: 
			TransformComponent(const Transform & transform, const uint_fast32_t& id);

			inline Nash::FVector3 GetPosition() const;
		
			inline Nash::FVector3 GetScale() const;

			~TransformComponent();
		};
		inline Nash::FVector3 TransformComponent::GetPosition() const
		{
			return m_transform.Position;
		}		
		inline Nash::FVector3 TransformComponent::GetScale() const
		{
			return m_transform.Scale; 
		}
	}
}