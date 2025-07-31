#pragma once
#include <vector>
#include <memory>
#include <type_traits>

namespace viper {
	class Actor;
	class Renderer;

	class Scene {
	public:
		Scene() = default;
		void Update(float dt);
		void Draw(Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);

		// Return first actor of type T
		template<typename T>
		T* GetActor() {
			for (auto& actor : m_actors) {
				if (T* t = dynamic_cast<T*>(actor.get())) {
					return t;
				}
			}
			return nullptr;
		}

		// Return all actors of type T
		template<typename T>
		std::vector<T*> GetActors() {
			std::vector<T*> result;
			for (auto& actor : m_actors) {
				if (T* t = dynamic_cast<T*>(actor.get())) {
					result.push_back(t);
				}
			}
			return result;
		}

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
	};
}
