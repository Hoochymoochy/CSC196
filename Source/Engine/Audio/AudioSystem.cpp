#include "AudioSystem.h"
#include "../Core/CoreStringHelper.h"

#include <iostream>
#include <fmod_errors.h>

namespace viper {

	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}

	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}

	void AudioSystem::Shutdown() {
		if (m_system) {
			CheckFMODResult(m_system->release());
			m_system = nullptr;
		}
	}

	void AudioSystem::AudioSystem::Update() {
		if (m_system) {
			CheckFMODResult(m_system->update());
		}
	}

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {
		std::string key = toLower(name.empty() ? filename : name);

		if (m_sounds.find(key) != m_sounds.end()) {
			std::cerr << "Audio System: Sound name already exists: " << key << std::endl;
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &sound);
		if (!CheckFMODResult(result)) return false;

		m_sounds[key] = sound;
		return true;
	}

	bool AudioSystem::PlaySound(const std::string& name) {
		std::string key = toLower(name);

		auto it = m_sounds.find(key);
		if (it == m_sounds.end()) {
			std::cerr << "Audio System: Sound not found: " << key << std::endl;
			return false;
		}

		FMOD_RESULT result = m_system->playSound(it->second, nullptr, false, nullptr);
		return CheckFMODResult(result);
	}

}
