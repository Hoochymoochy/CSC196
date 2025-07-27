#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace viper {
	bool InputSystem::Initialize() {
		int numKey;
		const bool* keyboardState = SDL_GetKeyboardState(&numKey);
		m_keyboardState.resize(numKey);
		std::copy(keyboardState, keyboardState + numKey, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_prevMousePosition = m_mousePosition;
		return true;
	}

	void InputSystem::Shutdown() {

	}

	void InputSystem::Update() {
		// KEYBOARD INPUT
		m_prevKeyboardState = m_keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		//// MOUSE INPUT
		m_prevMousePosition = m_mousePosition;
		m_prevMouseButtonState = m_mouseButtonState;

		uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

		m_mouseButtonState[(uint8_t)MouseButton::LEFT] = mouseButtonState & SDL_BUTTON_LMASK;
		m_mouseButtonState[(uint8_t)MouseButton::MIDDLE] = mouseButtonState & SDL_BUTTON_MMASK;
		m_mouseButtonState[(uint8_t)MouseButton::RIGHT] = mouseButtonState & SDL_BUTTON_RMASK;
	}
}