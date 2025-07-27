#include "Engine.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include <memory>
namespace viper {
	Engine& GetEngine() {
		static Engine engine;
		return engine;
	}

	bool Engine::Initialize() {
		m_renderer = std::make_unique<viper::Renderer>();
		m_renderer->Initialized();
		m_renderer->CreateWindow("Viper engine", 1280, 1024);

		m_input = std::make_unique<viper::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<viper::AudioSystem>();
		m_audio->Initialize();

		return true;
	}

	void Engine::Shutdown() {
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}
	void Engine::Update() {
		m_time.Tick();
		m_input->Update();
		m_audio->Update();
	}

	void Engine::Draw() {

	}
}