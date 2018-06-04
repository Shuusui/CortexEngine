#pragma once
#include "internal\Defines.h"


namespace Nash
{
	NASHEXPORT class Enums
	{
	public:
		enum class EColliderType
		{
			BoxCollider = 0, 
			CapsuleCollider, 
			SphereCollider
		};
	};
}