#pragma once

#include "IManager.h"

namespace CE
{
	class RenderManager : public IManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		RenderManager();

		virtual ~RenderManager() override;

		// FUNCTIONS
	public:
		void StartUp() override;

		void ShutDown() override;

		void Render();
	};
}
