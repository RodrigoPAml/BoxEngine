#pragma once
#include <BoxEngine.hpp>

namespace BoxEngine {
namespace Modules {
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
		case Input::InputAction::RELEASE:
			return "RELEASE";
		case Input::InputAction::PRESS:
			return "PRESS";
		case Input::InputAction::REPEAT:
			return "REPEAT";
		case Input::InputAction::NONE:
			return "NONE";
		}
	}

	static KeyModifier MapMod(std::string key)
	{
		if (key == "ALT")
			return Input::KeyModifier::ALT;
		else if (key == "CAPS_LOCK")
			return Input::KeyModifier::CAPS_LOCK;
		else if (key == "CONTROL")
			return Input::KeyModifier::CONTROL;
		else if (key == "NUM_LOCK")
			return Input::KeyModifier::NUM_LOCK;
		else if (key == "SHIFT")
			return Input::KeyModifier::SHIFT;
		else if (key == "SHIFT")
			return  Input::KeyModifier::SHIFT;

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
			return Input::KeyboardKey::KEY_SPACE;
		else if (key == "APOSTROPHE")
			return Input::KeyboardKey::KEY_APOSTROPHE;
		else if (key == "COMMA")
			return Input::KeyboardKey::KEY_COMMA;
		else if (key == "MINUS")
			return Input::KeyboardKey::KEY_MINUS;
		else if (key == "PERIOD")
			return Input::KeyboardKey::KEY_PERIOD;
		else if (key == "SLASH")
			return Input::KeyboardKey::KEY_SLASH;
		else if (key == "0")
			return Input::KeyboardKey::KEY_0;
		else if (key == "1")
			return Input::KeyboardKey::KEY_1;
		else if (key == "2")
			return Input::KeyboardKey::KEY_2;
		else if (key == "3")
			return Input::KeyboardKey::KEY_3;
		else if (key == "4")
			return Input::KeyboardKey::KEY_4;
		else if (key == "5")
			return Input::KeyboardKey::KEY_5;
		else if (key == "6")
			return Input::KeyboardKey::KEY_6;
		else if (key == "7")
			return Input::KeyboardKey::KEY_7;
		else if (key == "8")
			return Input::KeyboardKey::KEY_8;
		else if (key == "9")
			return Input::KeyboardKey::KEY_9;
		else if (key == "SEMICOLON")
			return Input::KeyboardKey::KEY_SEMICOLON;
		else if (key == "EQUAL")
			return Input::KeyboardKey::KEY_EQUAL;
		else if (key == "A")
			return Input::KeyboardKey::KEY_A;
		else if (key == "B")
			return Input::KeyboardKey::KEY_B;
		else if (key == "C")
			return Input::KeyboardKey::KEY_C;
		else if (key == "D")
			return Input::KeyboardKey::KEY_D;
		else if (key == "E")
			return Input::KeyboardKey::KEY_E;
		else if (key == "F")
			return Input::KeyboardKey::KEY_F;
		else if (key == "G")
			return Input::KeyboardKey::KEY_G;
		else if (key == "H")
			return Input::KeyboardKey::KEY_H;
		else if (key == "I")
			return Input::KeyboardKey::KEY_I;
		else if (key == "J")
			return Input::KeyboardKey::KEY_J;
		else if (key == "K")
			return Input::KeyboardKey::KEY_K;
		else if (key == "L")
			return Input::KeyboardKey::KEY_L;
		else if (key == "M")
			return Input::KeyboardKey::KEY_M;
		else if (key == "N")
			return Input::KeyboardKey::KEY_N;
		else if (key == "O")
			return Input::KeyboardKey::KEY_O;
		else if (key == "P")
			return Input::KeyboardKey::KEY_P;
		else if (key == "Q")
			return Input::KeyboardKey::KEY_Q;
		else if (key == "R")
			return Input::KeyboardKey::KEY_R;
		else if (key == "S")
			return Input::KeyboardKey::KEY_S;
		else if (key == "T")
			return Input::KeyboardKey::KEY_T;
		else if (key == "U")
			return Input::KeyboardKey::KEY_U;
		else if (key == "V")
			return Input::KeyboardKey::KEY_V;
		else if (key == "W")
			return Input::KeyboardKey::KEY_W;
		else if (key == "X")
			return Input::KeyboardKey::KEY_X;
		else if (key == "Y")
			return Input::KeyboardKey::KEY_Y;
		else if (key == "Z")
			return Input::KeyboardKey::KEY_Z;
		else if (key == "LEFT_BRACKET")
			return Input::KeyboardKey::KEY_LEFT_BRACKET;
		else if (key == "KEY_BACKSLASH")
			return Input::KeyboardKey::KEY_BACKSLASH;
		else if (key == "RIGHT_BRACKET")
			return Input::KeyboardKey::KEY_RIGHT_BRACKET;
		else if (key == "GRAVE_ACCENT")
			return Input::KeyboardKey::KEY_GRAVE_ACCENT;
		else if (key == "WORLD_1")
			return Input::KeyboardKey::KEY_WORLD_1;
		else if (key == "WORLD_2")
			return Input::KeyboardKey::KEY_WORLD_2;
		else if (key == "ESCAPE")
			return Input::KeyboardKey::KEY_ESCAPE;
		else if (key == "ENTER")
			return Input::KeyboardKey::KEY_ENTER;
		else if (key == "TAB")
			return Input::KeyboardKey::KEY_TAB;
		else if (key == "BACKSPACE")
			return Input::KeyboardKey::KEY_BACKSPACE;
		else if (key == "INSERT")
			return Input::KeyboardKey::KEY_INSERT;
		else if (key == "DELETE")
			return Input::KeyboardKey::KEY_DELETE;
		else if (key == "RIGHT")
			return Input::KeyboardKey::KEY_RIGHT;
		else if (key == "LEFT")
			return Input::KeyboardKey::KEY_LEFT;
		else if (key == "DOWN")
			return Input::KeyboardKey::KEY_DOWN;
		else if (key == "UP")
			return Input::KeyboardKey::KEY_UP;
		else if (key == "PAGE_UP")
			return Input::KeyboardKey::KEY_PAGE_UP;
		else if (key == "PAGE_DOWN")
			return Input::KeyboardKey::KEY_PAGE_DOWN;
		else if (key == "HOME")
			return Input::KeyboardKey::KEY_HOME;
		else if (key == "END")
			return Input::KeyboardKey::KEY_END;
		else if (key == "CAPS_LOCK")
			return Input::KeyboardKey::KEY_CAPS_LOCK;
		else if (key == "SCROLL_LOCK")
			return Input::KeyboardKey::KEY_SCROLL_LOCK;
		else if (key == "NUM_LOCK")
			return Input::KeyboardKey::KEY_NUM_LOCK;
		else if (key == "PRINT_SCREEN")
			return Input::KeyboardKey::KEY_PRINT_SCREEN;
		else if (key == "PAUSE")
			return Input::KeyboardKey::KEY_PAUSE;
		else if (key == "F1")
			return Input::KeyboardKey::KEY_F1;
		else if (key == "F2")
			return Input::KeyboardKey::KEY_F2;
		else if (key == "F3")
			return Input::KeyboardKey::KEY_F3;
		else if (key == "F4")
			return Input::KeyboardKey::KEY_F4;
		else if (key == "F5")
			return Input::KeyboardKey::KEY_F5;
		else if (key == "F6")
			return Input::KeyboardKey::KEY_F6;
		else if (key == "F7")
			return Input::KeyboardKey::KEY_F7;
		else if (key == "F8")
			return Input::KeyboardKey::KEY_F8;
		else if (key == "F9")
			return Input::KeyboardKey::KEY_F9;
		else if (key == "F10")
			return Input::KeyboardKey::KEY_F10;
		else if (key == "F11")
			return Input::KeyboardKey::KEY_F11;
		else if (key == "F12")
			return Input::KeyboardKey::KEY_F12;
		else if (key == "F13")
			return Input::KeyboardKey::KEY_F13;
		else if (key == "F14")
			return Input::KeyboardKey::KEY_F14;
		else if (key == "F15")
			return Input::KeyboardKey::KEY_F15;
		else if (key == "F16")
			return Input::KeyboardKey::KEY_F16;
		else if (key == "F17")
			return Input::KeyboardKey::KEY_F17;
		else if (key == "F18")
			return Input::KeyboardKey::KEY_F18;
		else if (key == "F19")
			return Input::KeyboardKey::KEY_F19;
		else if (key == "F20")
			return Input::KeyboardKey::KEY_F20;
		else if (key == "F21")
			return Input::KeyboardKey::KEY_F21;
		else if (key == "F22")
			return Input::KeyboardKey::KEY_F22;
		else if (key == "F23")
			return Input::KeyboardKey::KEY_F23;
		else if (key == "F24")
			return Input::KeyboardKey::KEY_F24;
		else if (key == "F25")
			return Input::KeyboardKey::KEY_F25;
		else if (key == "KP_0")
			return Input::KeyboardKey::KEY_KP_0;
		else if (key == "KP_1")
			return Input::KeyboardKey::KEY_KP_1;
		else if (key == "KP_2")
			return Input::KeyboardKey::KEY_KP_2;
		else if (key == "KP_3")
			return Input::KeyboardKey::KEY_KP_3;
		else if (key == "KP_4")
			return Input::KeyboardKey::KEY_KP_4;
		else if (key == "KP_5")
			return Input::KeyboardKey::KEY_KP_5;
		else if (key == "KP_6")
			return Input::KeyboardKey::KEY_KP_6;
		else if (key == "KP_7")
			return Input::KeyboardKey::KEY_KP_7;
		else if (key == "KP_8")
			return Input::KeyboardKey::KEY_KP_8;
		else if (key == "KP_9")
			return Input::KeyboardKey::KEY_KP_9;
		else if (key == "KP_DECIMAL")
			return Input::KeyboardKey::KEY_KP_DECIMAL;
		else if (key == "KP_DIVIDE")
			return Input::KeyboardKey::KEY_KP_DIVIDE;
		else if (key == "KP_MULTIPLY")
			return Input::KeyboardKey::KEY_KP_MULTIPLY;
		else if (key == "KP_SUBTRACT")
			return Input::KeyboardKey::KEY_KP_SUBTRACT;
		else if (key == "KP_ADD")
			return Input::KeyboardKey::KEY_KP_ADD;
		else if (key == "KP_ENTER")
			return Input::KeyboardKey::KEY_KP_ENTER;
		else if (key == "KP_EQUAL")
			return Input::KeyboardKey::KEY_KP_EQUAL;
		else if (key == "LEFT_SHIFT")
			return Input::KeyboardKey::KEY_LEFT_SHIFT;
		else if (key == "LEFT_CONTROL")
			return Input::KeyboardKey::KEY_LEFT_CONTROL;
		else if (key == "LEFT_ALT")
			return Input::KeyboardKey::KEY_LEFT_ALT;
		else if (key == "LEFT_SUPER")
			return Input::KeyboardKey::KEY_LEFT_SUPER;
		else if (key == "RIGHT_SHIFT")
			return Input::KeyboardKey::KEY_RIGHT_SHIFT;
		else if (key == "RIGHT_CONTROL")
			return Input::KeyboardKey::KEY_RIGHT_CONTROL;
		else if (key == "RIGHT_ALT")
			return Input::KeyboardKey::KEY_RIGHT_ALT;
		else if (key == "RIGHT_SUPER")
			return Input::KeyboardKey::KEY_RIGHT_SUPER;
		else if (key == "MENU")
			return Input::KeyboardKey::KEY_MENU;

		Debug::Logging::Log(
			"Failed to map KeyboardKey with value " + key + " instead the default value KEY_UNKNOWN will be used",
			Debug::LogSeverity::Warning,
			Debug::LogOrigin::Engine
		);

		return KeyboardKey::KEY_UNKNOWN;
	}
}}}