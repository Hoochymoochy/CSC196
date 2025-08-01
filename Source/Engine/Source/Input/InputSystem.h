#pragma once
#include "../../Math/Vector2.h"
#include <vector>
#include <array>

namespace viper {
	class InputSystem {
	public: InputSystem() = default;
		  enum class MouseButton : uint8_t {
			  LEFT,
			  MIDDLE,
			  RIGHT
		  };

		  bool Initialize();
		  void Shutdown();

		  void Update();

		  // KEYBOARD INPUT
		  bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		  bool GetPreviousKeyDown(uint8_t key) const { return m_prevKeyboardState[key]; }
		  bool GetKeyPressed(uint8_t key) const { return !m_prevKeyboardState[key] && m_keyboardState[key]; }
		  bool GetKeyReleased(uint8_t key) const { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		  // MOUSE INPUT
		  bool GetMouseButtonDown(MouseButton button) const { return m_mouseButtonState[(uint8_t)button]; }
		  bool GetPreviousMouseButtonDown(MouseButton button) const { return m_prevMouseButtonState[(uint8_t)button]; }
		  bool GetMouseButtonPressed(MouseButton button) const { return !m_prevMouseButtonState[(uint8_t)button] && m_mouseButtonState[(uint8_t)button]; }
		  bool GetMouseButtonReleased(MouseButton button) const { return m_prevMouseButtonState[(uint8_t)button] && !m_mouseButtonState[(uint8_t)button]; }

		  const vec2& GetMousePosition() const { return m_prevMousePosition; }
		  const vec2& GetPreviousMousePosition() const { return m_prevMousePosition; }


	private:
		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;

		viper::vec2 m_mousePosition{ 0, 0 };
		viper::vec2 m_prevMousePosition;

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool,3> m_prevMouseButtonState{ false, false, false };
	};

}