#pragma once
#include <vector>
#include <memory>

namespace viper {
	class Actor;
	class Renderer;

	class Scene {
	public:
		Scene() = default;
		void Update(float dt);
		void Draw(Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);

	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
	};
}
