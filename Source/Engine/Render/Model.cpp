#include "Model.h"  
#include "Renderer.h"

namespace viper  
{  
	void Model::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale)
	{  
		if (m_points.empty())  
			return;  
		renderer.SetColor(m_color.r, m_color.g, m_color.b);  

		for (int i = 0; i < m_points.size() - 1; ++i)  
		{  
			vec2 point = m_points[i].Rotate(rotation) + position;
			vec2 nextPoint = m_points[i + 1].Rotate(rotation) + position;

			renderer.DrawLine(point.x, point.y, nextPoint.x, nextPoint.y);  
		}  
	}  

	void Model::Draw(class Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
}