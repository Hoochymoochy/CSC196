#include "AudioSystem.h"
#include "../Core/CoreStringHelper.h"
#include <iostream>
#include <fmod_errors.h>
namespace Viper
{
	bool CheckFMODResult(FMOD_RESULT result) {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		return true;
	}

	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	};
	void AudioSystem::Shutdown() {
		CheckFMODResult(m_system->release());
	};

	void AudtioSystem::Update() {
		CheckFMODResult(m_system->update());
	};

	bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {
		std::string key = (name.empty()) ? filename : name;
		key = toLower(key);

		if (m_sounds.find(key) != m_sounds.end()) {
			std::cerr << "Audio System: Name already exists: " << key << std::endl;
			return false;
		};

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) return false;

		m_sounds[name] = sound;
		return true;
	}

	bool AudioSystem::PlaySound(const std::string& name) {
		std::string key = name;
		key = toLower(key);
		if (m_sounds.find(name) == m_sounds.end()) {
			std::cerr << "Audio System: name doesn't exists: " << name << std::endl;
			return false;
		}
		FMOD_RESULT result = m_system->playSound(m_sounds[name], nullptr, false, nullptr);
		if (!CheckFMODResult(result)) return false;
		return true;
	}


}