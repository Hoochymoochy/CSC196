#pragma once  
#include "../../Math/Transform.h"  
#include "../Render/Renderer.h"  
#include <memory>
#include "../../Render/Model.h"

namespace viper {
	class Renderer;

	class Actor {
	public:
		Actor() = default;


		Actor(const Transform& transform, std::shared_ptr<Model> model)
			: m_transform{ transform }, m_model{ model } {
		}

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);
		virtual bool IsDestroyed() const { return false; }


		Transform& GetTransform() { return m_transform; }


	protected:
		Transform m_transform;
		std::shared_ptr<viper::Model> m_model;
	};
}
