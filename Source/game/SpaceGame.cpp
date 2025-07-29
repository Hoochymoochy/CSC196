#include "SpaceGame.h"
#include "../Engine/Source/Game/Scene.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Render/Model.h"
#include "../Engine/Core/Random.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>
#include <Engine.h>

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>();

    std::vector<viper::vec2> points = {
       viper::vec2{ 0, 0 },     // Tip of the pointer
       viper::vec2{ -20, -10 }, // Left back
       viper::vec2{ -10, 0 },   // Inner left
       viper::vec2{ -20, 10 },  // Left bottom
       viper::vec2{ 0, 0 }      // Back to tip (close shape)
    };


    std::shared_ptr<viper::Model> player = std::make_shared < viper::Model>(points, viper::vec3{ 1, 1, 1 });
    std::shared_ptr<viper::Model> ships = std::make_shared < viper::Model>(points, viper::vec3{ 1, 1, 1 });

    //viper::Model* model = new viper::Model(points, viper::vec3{ 0, 0, 1 });

    viper::Transform transform{ viper::vec2{ 640, 512 }, 0, 20 };

    viper::Transform playerTransform{ viper::vec2{640, 512}, 0, 20 };
    m_scene->AddActor(std::make_unique<Player>(playerTransform, player));

    std::vector<std::unique_ptr<viper::Actor>> actors;
    for (int i = 0; i < 10; ++i) {
        viper::Transform transform{ viper::vec2 {viper::random::getReal() * 1024, viper::random::getReal() * 768}, 0, 20 };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, ships);
        m_scene->AddActor(std::move(enemy));
    }
	return true;
}	

void SpaceGame::Update() {
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw() {
    if (m_scene) m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown() {
    //m_scene.reset();
}