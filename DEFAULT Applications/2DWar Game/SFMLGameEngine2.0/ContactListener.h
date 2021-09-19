#pragma once
#include <Box2D\Box2D.h>
#include <iostream>

namespace GESFML
{
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();

		virtual void BeginContact(b2Contact *contact);
		virtual void EndContact(b2Contact *contact);

	};
}

