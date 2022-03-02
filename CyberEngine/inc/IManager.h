#pragma once

namespace CE
{
	class IManager
	{
	public:
		virtual ~IManager() = default;

		virtual void StartUp() = 0;

		virtual void ShutDown() = 0;
	};
}
