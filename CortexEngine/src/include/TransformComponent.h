#pragma once
#pragma region Internal Includes
#include "ICComponent.h"
#include "CortexStructs.h"
#include "Matrix.h"
#pragma endregion

#pragma region External Includes
#pragma endregion 

namespace CortexEngine
{
	namespace Core
	{
		class TransformComponent
		{
		private: 
			Transform m_transform;
			Nash::FMatrix m_matrix;
		public: 
			TransformComponent(const Transform& transform);

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