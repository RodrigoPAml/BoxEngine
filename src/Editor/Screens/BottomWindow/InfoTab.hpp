#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	using namespace Engine;

	/// <summary>
	/// Represents Info tab in bottom window.
	/// </summary>
	class InfoTab : public Layout
	{
	private:
		std::vector<float> frametimes;
		std::vector<float> fps;

		std::string guid = "";
	public:
		InfoTab() = default;
		~InfoTab() = default;

		void Awake();
		void Start();
		void Update();
	};
}}