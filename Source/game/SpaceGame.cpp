#include "SpaceGame.h"
#include "../Engine/Source/Game/Scene.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Render/Model.h"
#include "Source/Core/Random.h"
#include "Player.h"

#include <vector>

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>();

    std::vector<viper::vec2> points = {
       viper::vec2{ 0, 0 },     // Tip of the pointer
       viper::vec2{ -20, -10 }, // Left back
       viper::vec2{ -10, 0 },   // Inner left
       viper::vec2{ -20, 10 },  // Left bottom
       viper::vec2{ 0, 0 }      // Back to tip (close shape)
    };


    std::shared_ptr<viper::Model> model = std::make_shared < viper::Model>(points, viper::vec3{ 1, 1, 1 });

    //viper::Model* model = new viper::Model(points, viper::vec3{ 0, 0, 1 });

    viper::Transform transform{ viper::vec2{ 640, 512 }, 0, 20 };

    std::vector<std::unique_ptr<viper::Actor>> actors;
    for (int i = 0; i < 10; ++i) {
        viper::Transform transform{ viper::vec2 {viper::random::getReal() * 1024, viper::random::getReal() * 1024} };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        m_scene->AddActor(std::move(player));
    }
	return true;
}	

void SpaceGame::Update() {
    //if (m_scene) m_scene->Update();
}

void SpaceGame::Draw() {
    //if (m_scene) m_scene->Draw();
}

void SpaceGame::Shutdown() {
    //m_scene.reset();
}