#pragma once

namespace CE
{
	class Enums
	{
	public:
		enum class EComponentType
		{
			Rigidbody, 
			Transform, 
			Collider, 
			Render
		};
		enum class EListenerType
		{
			Message
		};
		enum class EDirection
		{
			Forward, 
			Backward, 
			Left, 
			Right
		};
	};
}