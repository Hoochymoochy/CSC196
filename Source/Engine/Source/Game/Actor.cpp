#include "Actor.h"
#include "../../Render/Model.h"

namespace viper
{
	void Actor::Update(float dt)
	{

	}

	void Actor::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer,  m_transform);
	}
}