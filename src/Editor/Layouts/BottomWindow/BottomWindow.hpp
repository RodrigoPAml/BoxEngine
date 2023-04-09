#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Editor {

	/// <summary>
	/// Represents the bottom window of the engine.
	/// </summary>
	class BottomWindow : public Layout
	{
	private:
		/// <summary>
		/// The log tab of this window.
		/// </summary>
		LogTab logTab;

		/// <summary>
		/// The file manager of this window.
		/// </summary>
		FilesTab filesTab;

		/// <summary>
		/// The info tab of this window.
		/// </summary>
		InfoTab infoTab;

		bool reset = false;

		float minY = 0;
	public:
		BottomWindow() = default;
		~BottomWindow() = default;

		void Awake();
		void Start();
		void Update();
		void Destroy();
		void Reset();
		void ClearLogs();

		float GetMinY() const;
	};
}}