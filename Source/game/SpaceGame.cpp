#include "SpaceGame.h"
#include "../Engine/Source/Game/Scene.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Render/Model.h"
#include "../Engine/Core/Random.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"

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

    // Large irregular asteroid
    std::vector<viper::vec2> asteroid_large = {
        { 0, -40 },
        { 25, -35 },
        { 45, -20 },
        { 50, -5 },
        { 38, 15 },
        { 42, 30 },
        { 20, 45 },
        { -5, 42 },
        { -28, 38 },
        { -45, 25 },
        { -48, 5 },
        { -40, -15 },
        { -30, -32 },
        { -15, -38 },
        { 0, -40 }
    };

    // Medium jagged asteroid
    std::vector<viper::vec2> asteroid_medium = {
        { 0, -25 },
        { 18, -22 },
        { 30, -12 },
        { 28, 5 },
        { 35, 18 },
        { 15, 28 },
        { -8, 30 },
        { -25, 20 },
        { -32, 8 },
        { -28, -10 },
        { -20, -20 },
        { 0, -25 }
    };

    // Small chunky asteroid
    std::vector<viper::vec2> asteroid_small = {
        { 0, -15 },
        { 12, -12 },
        { 18, -5 },
        { 15, 8 },
        { 8, 15 },
        { -5, 18 },
        { -15, 10 },
        { -18, -2 },
        { -12, -12 },
        { 0, -15 }
    };

    // Elongated asteroid (potato-shaped)
    std::vector<viper::vec2> asteroid_elongated = {
        { 0, -20 },
        { 15, -18 },
        { 35, -10 },
        { 45, 0 },
        { 40, 12 },
        { 25, 18 },
        { 5, 15 },
        { -20, 12 },
        { -38, 5 },
        { -42, -8 },
        { -30, -15 },
        { -15, -18 },
        { 0, -20 }
    };

    // Spiky asteroid with sharp edges
    std::vector<viper::vec2> asteroid_spiky = {
        { 0, -30 },
        { 10, -25 },
        { 25, -28 },
        { 30, -15 },
        { 22, -8 },
        { 35, 5 },
        { 25, 15 },
        { 12, 25 },
        { 0, 20 },
        { -15, 28 },
        { -28, 18 },
        { -35, 2 },
        { -25, -12 },
        { -32, -20 },
        { -18, -25 },
        { 0, -30 }
    };

    std::vector<viper::vec2> heart_shape = {
        { 0, 25 },       // top point (flipped Y)
        { 8, 18 },       // right top curve
        { 15, 10 },      // right side
        { 20, 2 },       // right lower curve
        { 22, -6 },      // right bottom of right lobe
        { 18, -12 },     // right dip
        { 12, -15 },     // right bottom
        { 5, -16 },      // right base
        { 0, -12 },      // center dip (now bottom)
        { -5, -16 },     // left base
        { -12, -15 },    // left bottom
        { -18, -12 },    // left dip
        { -22, -6 },     // left bottom of left lobe
        { -20, 2 },      // left lower curve
        { -15, 10 },     // left side
        { -8, 18 },      // left top curve
        { 0, 25 }        // close the shape
    };



    std::shared_ptr<viper::Model> player = std::make_shared < viper::Model>(points, viper::vec3{ 1, 1, 1 });

    std::vector<std::shared_ptr<viper::Model>> asteroidModels = {
        std::make_shared<viper::Model>(asteroid_large,     viper::vec3{ 0.8f, 0.8f, 0.8f }),
        std::make_shared<viper::Model>(asteroid_medium,    viper::vec3{ 0.6f, 0.6f, 0.6f }),
        std::make_shared<viper::Model>(asteroid_small,     viper::vec3{ 0.4f, 0.4f, 0.4f }),
        std::make_shared<viper::Model>(asteroid_elongated, viper::vec3{ 0.7f, 0.5f, 0.5f }),
        std::make_shared<viper::Model>(asteroid_spiky,     viper::vec3{ 0.9f, 0.3f, 0.3f }),
    };

    std::vector<std::shared_ptr<viper::Model>> heartModels = {
        std::make_shared<viper::Model>(heart_shape, viper::vec3{ 1, 0, 0 }), 
        std::make_shared<viper::Model>(heart_shape, viper::vec3{ 1, 0, 0 }), 
        std::make_shared<viper::Model>(heart_shape, viper::vec3{ 1, 0, 0 }) 
	};

    viper::Transform transform{ viper::vec2{ 640, 512 }, 0, 20 };

    viper::Transform playerTransform{ viper::vec2{640, 512}, 0, 20 };
    m_scene->AddActor(std::make_unique<Player>(playerTransform, player));

    for (int i = 0; i < 3; i++) {
		int modelIndex = static_cast<int>(viper::random::getInt(0, static_cast<int>(heartModels.size()) - 1));
		std::shared_ptr<viper::Model> randomHeartModel = heartModels[modelIndex];
		viper::Transform heartTransform{ viper::vec2{ static_cast<float>(1100 + i * 50), 30 }};
        std::unique_ptr<Health> health = std::make_unique<Health>(heartTransform, randomHeartModel);
		m_scene->AddActor(std::move(health));
    };



    for (int i = 0; i < 10; ++i) {
        int modelIndex = static_cast<int>(viper::random::getInt(0, static_cast<int>(asteroidModels.size()) - 1));
        std::shared_ptr<viper::Model> randomModel = asteroidModels[modelIndex];

        viper::Transform transform{
            viper::vec2{ viper::random::getReal() * 1024, viper::random::getReal() * 768 },
            viper::random::getReal(0.0f, 6.28f), // Random rotation
            viper::random::getReal(10.0f, 30.0f) // Random scale
        };

        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, randomModel);
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