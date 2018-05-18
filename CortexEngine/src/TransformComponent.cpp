#include "include\TransformComponent.h"

CortexEngine::Core::TransformComponent::TransformComponent(const Transform & transform)
	:m_matrix()
{	
	m_matrix.Translate(transform.Position);
	
	m_matrix.Scale(transform.Scale);
}



CortexEngine::Core::TransformComponent::~TransformComponent()
{
}
