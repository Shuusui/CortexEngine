#include "..\include\Rigidbody.h"

Nash::Rigidbody::Rigidbody(const FVector3 & position, const float& mass,const bool& simulatePhysics, const bool& enableGravity)
	:m_position(position)
	,m_mass(mass)
	,m_bSimulatePhysics(simulatePhysics)
	,m_bEnableGravity(enableGravity)
	,m_force()
{
}

void Nash::Rigidbody::DeltaUpdate()
{
	if (m_bSimulatePhysics && m_bEnableGravity)
		this->AddForce(FVector3(0, -GRAVITY, 0));

}

void Nash::Rigidbody::AddForce(const FVector3 & dir)
{
	m_force + dir;
}

void Nash::Rigidbody::AddImpulse(const FVector3 & dir)
{

}
