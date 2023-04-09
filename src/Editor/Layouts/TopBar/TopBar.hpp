#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	class TopBar : public Layout
	{
	private:
		bool reset = true;
	public:
		void Reset();
		void Update();
	};	
}}