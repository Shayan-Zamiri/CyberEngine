#pragma once

namespace CE
{
	class RenderManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		RenderManager();

		~RenderManager();

		// FUNCTIONS
	public:
		void StartUp();

		void Render();

		void ShutDown();
	};
}
