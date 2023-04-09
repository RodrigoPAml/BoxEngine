#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	/// <summary>
	/// Represents Info tab in bottom window.
	/// </summary>
	class InfoTab : public Layout
	{
	private:
		std::vector<float> frametimes;
		std::vector<float> fps;
	public:
		InfoTab() = default;
		~InfoTab() = default;

		void Awake();
		void Start();
		void Update();
		void Destroy();
	};
}}