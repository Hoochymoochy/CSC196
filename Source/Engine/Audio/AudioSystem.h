#pragma once  
#include <fmod.hpp>  
#include <string>
#include <map>

namespace viper {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "");
		bool PlaySound(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT reslut);
	private:
		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}