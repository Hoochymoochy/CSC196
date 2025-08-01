#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>

#include "../Engine/Core/Random.h"
#include "Source/Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Render/Renderer.h"
#include "Source/Render/Renderer.h"
#include "Source/Game/Scene.h"
#include "Source/Game/Actor.h"
#include "../Engine/Render/Model.h"
#include "../Engine/Engine.h"
#include "../Engine/Render/Font.h"
#include "../Engine/Render/Text.h"

#include "../game/Player.h"
#include "../game/SpaceGame.h"

#include "../Engine/Core/File.h"
#include "../Engine/Core/Time.h"

using namespace viper;

int main(int argc, char* argv[]) {
    // Initialize the engine
    viper::GetEngine().Initialize();

    // Initialize the game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    Time* time = &viper::GetEngine().GetTime();

    // Load font
    Font* font = new Font();
    bool fontLoaded = font->Load("os.ttf", 20);
    if (!fontLoaded) {
        std::cerr << "Could not load font. Aborting.\n";
        return -1;
    }
	viper::GetEngine().GetAudio().AddSound("ms.mp3", "ms");
	viper::GetEngine().GetAudio().PlayMusic("ms");

    Text* text = new Text(font);

    SDL_Event e;
    bool quit = false;

    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();
        game->Update();

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        viper::vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw();

        std::ostringstream timeStream;
        timeStream << std::fixed << std::setprecision(2) << "Time: " << time->GetTime() << "s";
        text->Create(GetEngine().GetRenderer(), timeStream.str(), vec3{ 1, 1, 1 });
        text->Draw(GetEngine().GetRenderer(), 40.0f, 40.0f);

        viper::vec2 speedz{ -140.0f, 0.0f };
        for (auto& star : stars) {
            star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0)    star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor(
                static_cast<uint8_t>(viper::random::getReal(256.0f)),
                static_cast<uint8_t>(viper::random::getReal(256.0f)),
                static_cast<uint8_t>(viper::random::getReal(256.0f))
            );

            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        viper::GetEngine().GetRenderer().Present();
    }

    viper::GetEngine().Shutdown();
    return 0;
}
