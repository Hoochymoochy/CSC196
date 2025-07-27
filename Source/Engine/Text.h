#pragma once
#include "Font.h"
#include "Render/Renderer.h"
#include "Math/Vector3.h"

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, float x, float y);
	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}