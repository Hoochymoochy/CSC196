#include "Scene.h"
#include "Actor.h"
#include "../Render/Renderer.h"

namespace viper {

	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			if (actor) actor->Update(dt);
		}

		// Optional: remove dead actors
		m_actors.erase(
			std::remove_if(m_actors.begin(), m_actors.end(),
				[](const std::unique_ptr<Actor>& actor) {
					return actor && actor->IsDestroyed(); // Or use health check
				}),
			m_actors.end()
		);
	}

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor) actor->Draw(renderer);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		m_actors.push_back(std::move(actor));
	}
}
