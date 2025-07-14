#include "AudioSystem.h"
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
	}

	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}
		void* extradriverdata = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	};
	void Shutdown() {
	};

	void Update() {
	};
}