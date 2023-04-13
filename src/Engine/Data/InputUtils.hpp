#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Input {

	static MouseButton MapMouseButton(std::string button)
	{
		if (button == "LEFT")
			return MouseButton::MOUSE_BUTTON_LEFT;
		else if (button == "RIGHT")
			return MouseButton::MOUSE_BUTTON_RIGHT;
		else if (button == "MIDDLE")
			return MouseButton::MOUSE_BUTTON_MIDDLE;
		else if (button == "1")
			return MouseButton::MOUSE_BUTTON_1;
		else if (button == "2")
			return MouseButton::MOUSE_BUTTON_2;
		else if (button == "3")
			return MouseButton::MOUSE_BUTTON_3;
		else if (button == "4")
			return MouseButton::MOUSE_BUTTON_4;
		else if (button == "5")
			return MouseButton::MOUSE_BUTTON_5;
		else if (button == "6")
			return MouseButton::MOUSE_BUTTON_6;
		else if (button == "7")
			return MouseButton::MOUSE_BUTTON_7;
		else if (button == "8")
			return MouseButton::MOUSE_BUTTON_8;

		Debug::Logging::Log(
			"Failed to map MouseButton with value " + button + " instead the default value MOUSE_BUTTON_LEFT will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return MouseButton::MOUSE_BUTTON_LEFT;
	}

	static std::string MapInputAction(InputAction action)
	{
		switch (action)
		{
		case BoxEngine::Input::InputAction::RELEASE:
			return "RELEASE";
		case BoxEngine::Input::InputAction::PRESS:
			return "PRESS";
		case BoxEngine::Input::InputAction::REPEAT:
			return "REPEAT";
		case BoxEngine::Input::InputAction::NONE:
			return "NONE";
		}
	}

	static KeyModifier MapMod(std::string key)
	{
		if (key == "ALT")
			return BoxEngine::Input::KeyModifier::ALT;
		else if (key == "CAPS_LOCK")
			return BoxEngine::Input::KeyModifier::CAPS_LOCK;
		else if (key == "CONTROL")
			return BoxEngine::Input::KeyModifier::CONTROL;
		else if (key == "NUM_LOCK")
			return BoxEngine::Input::KeyModifier::NUM_LOCK;
		else if (key == "SHIFT")
			return BoxEngine::Input::KeyModifier::SHIFT;
		else if (key == "SHIFT")
			return BoxEngine::Input::KeyModifier::SHIFT;

		Debug::Logging::Log(
			"Failed to map KeyModifier with value " + key + " instead the default value UNKNOWN will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return KeyModifier::UNKNOWN;
	}

	static KeyboardKey MapKey(std::string key)
	{
		if (key == "SPACE")
			return BoxEngine::Input::KeyboardKey::KEY_SPACE;
		else if (key == "APOSTROPHE")
			return BoxEngine::Input::KeyboardKey::KEY_APOSTROPHE;
		else if (key == "COMMA")
			return BoxEngine::Input::KeyboardKey::KEY_COMMA;
		else if (key == "MINUS")
			return BoxEngine::Input::KeyboardKey::KEY_MINUS;
		else if (key == "PERIOD")
			return BoxEngine::Input::KeyboardKey::KEY_PERIOD;
		else if (key == "SLASH")
			return BoxEngine::Input::KeyboardKey::KEY_SLASH;
		else if (key == "0")
			return BoxEngine::Input::KeyboardKey::KEY_0;
		else if (key == "1")
			return BoxEngine::Input::KeyboardKey::KEY_1;
		else if (key == "2")
			return BoxEngine::Input::KeyboardKey::KEY_2;
		else if (key == "3")
			return BoxEngine::Input::KeyboardKey::KEY_3;
		else if (key == "4")
			return BoxEngine::Input::KeyboardKey::KEY_4;
		else if (key == "5")
			return BoxEngine::Input::KeyboardKey::KEY_5;
		else if (key == "6")
			return BoxEngine::Input::KeyboardKey::KEY_6;
		else if (key == "7")
			return BoxEngine::Input::KeyboardKey::KEY_7;
		else if (key == "8")
			return BoxEngine::Input::KeyboardKey::KEY_8;
		else if (key == "9")
			return BoxEngine::Input::KeyboardKey::KEY_9;
		else if (key == "SEMICOLON")
			return BoxEngine::Input::KeyboardKey::KEY_SEMICOLON;
		else if (key == "EQUAL")
			return BoxEngine::Input::KeyboardKey::KEY_EQUAL;
		else if (key == "A")
			return BoxEngine::Input::KeyboardKey::KEY_A;
		else if (key == "B")
			return BoxEngine::Input::KeyboardKey::KEY_B;
		else if (key == "C")
			return BoxEngine::Input::KeyboardKey::KEY_C;
		else if (key == "D")
			return BoxEngine::Input::KeyboardKey::KEY_D;
		else if (key == "E")
			return BoxEngine::Input::KeyboardKey::KEY_E;
		else if (key == "F")
			return BoxEngine::Input::KeyboardKey::KEY_F;
		else if (key == "G")
			return BoxEngine::Input::KeyboardKey::KEY_G;
		else if (key == "H")
			return BoxEngine::Input::KeyboardKey::KEY_H;
		else if (key == "I")
			return BoxEngine::Input::KeyboardKey::KEY_I;
		else if (key == "J")
			return BoxEngine::Input::KeyboardKey::KEY_J;
		else if (key == "K")
			return BoxEngine::Input::KeyboardKey::KEY_K;
		else if (key == "L")
			return BoxEngine::Input::KeyboardKey::KEY_L;
		else if (key == "M")
			return BoxEngine::Input::KeyboardKey::KEY_M;
		else if (key == "N")
			return BoxEngine::Input::KeyboardKey::KEY_N;
		else if (key == "O")
			return BoxEngine::Input::KeyboardKey::KEY_O;
		else if (key == "P")
			return BoxEngine::Input::KeyboardKey::KEY_P;
		else if (key == "Q")
			return BoxEngine::Input::KeyboardKey::KEY_Q;
		else if (key == "R")
			return BoxEngine::Input::KeyboardKey::KEY_R;
		else if (key == "S")
			return BoxEngine::Input::KeyboardKey::KEY_S;
		else if (key == "T")
			return BoxEngine::Input::KeyboardKey::KEY_T;
		else if (key == "U")
			return BoxEngine::Input::KeyboardKey::KEY_U;
		else if (key == "V")
			return BoxEngine::Input::KeyboardKey::KEY_V;
		else if (key == "W")
			return BoxEngine::Input::KeyboardKey::KEY_W;
		else if (key == "X")
			return BoxEngine::Input::KeyboardKey::KEY_X;
		else if (key == "Y")
			return BoxEngine::Input::KeyboardKey::KEY_Y;
		else if (key == "Z")
			return BoxEngine::Input::KeyboardKey::KEY_Z;
		else if (key == "LEFT_BRACKET")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT_BRACKET;
		else if (key == "KEY_BACKSLASH")
			return BoxEngine::Input::KeyboardKey::KEY_BACKSLASH;
		else if (key == "RIGHT_BRACKET")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT_BRACKET;
		else if (key == "GRAVE_ACCENT")
			return BoxEngine::Input::KeyboardKey::KEY_GRAVE_ACCENT;
		else if (key == "WORLD_1")
			return BoxEngine::Input::KeyboardKey::KEY_WORLD_1;
		else if (key == "WORLD_2")
			return BoxEngine::Input::KeyboardKey::KEY_WORLD_2;
		else if (key == "ESCAPE")
			return BoxEngine::Input::KeyboardKey::KEY_ESCAPE;
		else if (key == "ENTER")
			return BoxEngine::Input::KeyboardKey::KEY_ENTER;
		else if (key == "TAB")
			return BoxEngine::Input::KeyboardKey::KEY_TAB;
		else if (key == "BACKSPACE")
			return BoxEngine::Input::KeyboardKey::KEY_BACKSPACE;
		else if (key == "INSERT")
			return BoxEngine::Input::KeyboardKey::KEY_INSERT;
		else if (key == "DELETE")
			return BoxEngine::Input::KeyboardKey::KEY_DELETE;
		else if (key == "RIGHT")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT;
		else if (key == "LEFT")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT;
		else if (key == "DOWN")
			return BoxEngine::Input::KeyboardKey::KEY_DOWN;
		else if (key == "UP")
			return BoxEngine::Input::KeyboardKey::KEY_UP;
		else if (key == "PAGE_UP")
			return BoxEngine::Input::KeyboardKey::KEY_PAGE_UP;
		else if (key == "PAGE_DOWN")
			return BoxEngine::Input::KeyboardKey::KEY_PAGE_DOWN;
		else if (key == "HOME")
			return BoxEngine::Input::KeyboardKey::KEY_HOME;
		else if (key == "END")
			return BoxEngine::Input::KeyboardKey::KEY_END;
		else if (key == "CAPS_LOCK")
			return BoxEngine::Input::KeyboardKey::KEY_CAPS_LOCK;
		else if (key == "SCROLL_LOCK")
			return BoxEngine::Input::KeyboardKey::KEY_SCROLL_LOCK;
		else if (key == "NUM_LOCK")
			return BoxEngine::Input::KeyboardKey::KEY_NUM_LOCK;
		else if (key == "PRINT_SCREEN")
			return BoxEngine::Input::KeyboardKey::KEY_PRINT_SCREEN;
		else if (key == "PAUSE")
			return BoxEngine::Input::KeyboardKey::KEY_PAUSE;
		else if (key == "F1")
			return BoxEngine::Input::KeyboardKey::KEY_F1;
		else if (key == "F2")
			return BoxEngine::Input::KeyboardKey::KEY_F2;
		else if (key == "F3")
			return BoxEngine::Input::KeyboardKey::KEY_F3;
		else if (key == "F4")
			return BoxEngine::Input::KeyboardKey::KEY_F4;
		else if (key == "F5")
			return BoxEngine::Input::KeyboardKey::KEY_F5;
		else if (key == "F6")
			return BoxEngine::Input::KeyboardKey::KEY_F6;
		else if (key == "F7")
			return BoxEngine::Input::KeyboardKey::KEY_F7;
		else if (key == "F8")
			return BoxEngine::Input::KeyboardKey::KEY_F8;
		else if (key == "F9")
			return BoxEngine::Input::KeyboardKey::KEY_F9;
		else if (key == "F10")
			return BoxEngine::Input::KeyboardKey::KEY_F10;
		else if (key == "F11")
			return BoxEngine::Input::KeyboardKey::KEY_F11;
		else if (key == "F12")
			return BoxEngine::Input::KeyboardKey::KEY_F12;
		else if (key == "F13")
			return BoxEngine::Input::KeyboardKey::KEY_F13;
		else if (key == "F14")
			return BoxEngine::Input::KeyboardKey::KEY_F14;
		else if (key == "F15")
			return BoxEngine::Input::KeyboardKey::KEY_F15;
		else if (key == "F16")
			return BoxEngine::Input::KeyboardKey::KEY_F16;
		else if (key == "F17")
			return BoxEngine::Input::KeyboardKey::KEY_F17;
		else if (key == "F18")
			return BoxEngine::Input::KeyboardKey::KEY_F18;
		else if (key == "F19")
			return BoxEngine::Input::KeyboardKey::KEY_F19;
		else if (key == "F20")
			return BoxEngine::Input::KeyboardKey::KEY_F20;
		else if (key == "F21")
			return BoxEngine::Input::KeyboardKey::KEY_F21;
		else if (key == "F22")
			return BoxEngine::Input::KeyboardKey::KEY_F22;
		else if (key == "F23")
			return BoxEngine::Input::KeyboardKey::KEY_F23;
		else if (key == "F24")
			return BoxEngine::Input::KeyboardKey::KEY_F24;
		else if (key == "F25")
			return BoxEngine::Input::KeyboardKey::KEY_F25;
		else if (key == "KP_0")
			return BoxEngine::Input::KeyboardKey::KEY_KP_0;
		else if (key == "KP_1")
			return BoxEngine::Input::KeyboardKey::KEY_KP_1;
		else if (key == "KP_2")
			return BoxEngine::Input::KeyboardKey::KEY_KP_2;
		else if (key == "KP_3")
			return BoxEngine::Input::KeyboardKey::KEY_KP_3;
		else if (key == "KP_4")
			return BoxEngine::Input::KeyboardKey::KEY_KP_4;
		else if (key == "KP_5")
			return BoxEngine::Input::KeyboardKey::KEY_KP_5;
		else if (key == "KP_6")
			return BoxEngine::Input::KeyboardKey::KEY_KP_6;
		else if (key == "KP_7")
			return BoxEngine::Input::KeyboardKey::KEY_KP_7;
		else if (key == "KP_8")
			return BoxEngine::Input::KeyboardKey::KEY_KP_8;
		else if (key == "KP_9")
			return BoxEngine::Input::KeyboardKey::KEY_KP_9;
		else if (key == "KP_DECIMAL")
			return BoxEngine::Input::KeyboardKey::KEY_KP_DECIMAL;
		else if (key == "KP_DIVIDE")
			return BoxEngine::Input::KeyboardKey::KEY_KP_DIVIDE;
		else if (key == "KP_MULTIPLY")
			return BoxEngine::Input::KeyboardKey::KEY_KP_MULTIPLY;
		else if (key == "KP_SUBTRACT")
			return BoxEngine::Input::KeyboardKey::KEY_KP_SUBTRACT;
		else if (key == "KP_ADD")
			return BoxEngine::Input::KeyboardKey::KEY_KP_ADD;
		else if (key == "KP_ENTER")
			return BoxEngine::Input::KeyboardKey::KEY_KP_ENTER;
		else if (key == "KP_EQUAL")
			return BoxEngine::Input::KeyboardKey::KEY_KP_EQUAL;
		else if (key == "LEFT_SHIFT")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT_SHIFT;
		else if (key == "LEFT_CONTROL")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT_CONTROL;
		else if (key == "LEFT_ALT")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT_ALT;
		else if (key == "LEFT_SUPER")
			return BoxEngine::Input::KeyboardKey::KEY_LEFT_SUPER;
		else if (key == "RIGHT_SHIFT")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT_SHIFT;
		else if (key == "RIGHT_CONTROL")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT_CONTROL;
		else if (key == "RIGHT_ALT")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT_ALT;
		else if (key == "RIGHT_SUPER")
			return BoxEngine::Input::KeyboardKey::KEY_RIGHT_SUPER;
		else if (key == "MENU")
			return BoxEngine::Input::KeyboardKey::KEY_MENU;

		Debug::Logging::Log(
			"Failed to map KeyboardKey with value " + key + " instead the default value KEY_UNKNOWN will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return KeyboardKey::KEY_UNKNOWN;
	}
}}