#pragma once
#include "internal\Defines.h"


namespace Nash
{
	NASHEXPORT class Enums
	{
	public:
		enum class ColliderType
		{
			BoxCollider = 0, 
			CapsuleCollider, 
			SphereCollider
		};
	};
}