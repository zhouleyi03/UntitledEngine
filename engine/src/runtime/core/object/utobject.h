#pragma once
#include "core/base/uuid.h"

namespace Untitled
{
	class UTObject
	{
	public:
		virtual ~UTObject() = 0 {}
	protected:
		UUID uuid;
	};
}
