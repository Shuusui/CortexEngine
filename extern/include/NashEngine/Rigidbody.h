#pragma once
#pragma region Internal Includes
#include "BaseMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "internal\Defines.h"
#pragma endregion

namespace Nash
{
	class NASHEXPORT Rigidbody
	{
	private: 
		bool m_bSimulatePhysics;
		bool m_bEnableGravity;
		FVector3 m_position;
		float m_mass;
		FVector3 m_force;
	public:
		/**
		* Default Constructor, every rigidbody needs a position to add a force to an object
		*
		* @param position The initial position of the rigidbody
		* @param mass The mass of the object in kg (Default = 50kg)
		* @param simulatePhysics activate or disable physics for this object (Default = true)
		* @param enableGravity activate or disable gravity for this object (Default = true)
		*/
		Rigidbody(const FVector3& position, const float& mass = 50,const bool& simulatePhysics = true, const bool& enableGravity = true);
		/**
		* Default constructor is disabled because every Rigidbody needs a position to enable forces
		*/
		Rigidbody() = delete;
		/**
		* Copy constructor is disabled because it shouldn't be possible to copy a rigidbody because it would be to expensive to copy all forces
		* (Maybe better to copy all changable values outside the rigidbody and insert it to the rigidbody)
		*/
		Rigidbody(const Rigidbody&) = delete; 
		/**
		* Function which should be called every delta Time and not every frame, because of physics
		* 
		*/
		void DeltaUpdate(); 
		/**
		* Basic function to add a force to an object
		* @param dir This parameter show the direction of the force and the strength, the higher the value of the X,Y,Z values are, the stronger the force.
		*/
		void AddForce(const FVector3& dir);
		/**
		* Will give the object an impulse in a direction 
		* @param dir The direction of the impulse force and the strength of it. 
		*/
		void AddImpulse(const FVector3& dir);
	};
}