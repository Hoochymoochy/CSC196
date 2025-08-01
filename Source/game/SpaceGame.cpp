﻿#include "SpaceGame.h"
#include "../Engine/Source/Game/Scene.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Render/Model.h"
#include "../Engine/Core/Random.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "../Engine/Source/Game/Collisions.h"
#include "Input/InputSystem.h"

#include <vector>
#include <Engine.h>
#include <iostream>
#include "Bullet.h"

bool SpaceGame::Initialize() {
    m_scene = std::make_unique<viper::Scene>();

    std::vector<viper::vec2> points = {
       { 0, 0 }, { -20, -10 }, { -10, 0 }, { -20, 10 }, { 0, 0 }
    };

    std::vector<viper::vec2> asteroid_large = {
        { 0, -40 }, { 25, -35 }, { 45, -20 }, { 50, -5 }, { 38, 15 },
        { 42, 30 }, { 20, 45 }, { -5, 42 }, { -28, 38 }, { -45, 25 },
        { -48, 5 }, { -40, -15 }, { -30, -32 }, { -15, -38 }, { 0, -40 }
    };

    std::vector<viper::vec2> asteroid_medium = {
        { 0, -25 }, { 18, -22 }, { 30, -12 }, { 28, 5 }, { 35, 18 },
        { 15, 28 }, { -8, 30 }, { -25, 20 }, { -32, 8 }, { -28, -10 },
        { -20, -20 }, { 0, -25 }
    };

    std::vector<viper::vec2> asteroid_small = {
        { 0, -15 }, { 12, -12 }, { 18, -5 }, { 15, 8 }, { 8, 15 },
        { -5, 18 }, { -15, 10 }, { -18, -2 }, { -12, -12 }, { 0, -15 }
    };

    std::vector<viper::vec2> asteroid_elongated = {
        { 0, -20 }, { 15, -18 }, { 35, -10 }, { 45, 0 }, { 40, 12 },
        { 25, 18 }, { 5, 15 }, { -20, 12 }, { -38, 5 }, { -42, -8 },
        { -30, -15 }, { -15, -18 }, { 0, -20 }
    };

    std::vector<viper::vec2> asteroid_spiky = {
        { 0, -30 }, { 10, -25 }, { 25, -28 }, { 30, -15 }, { 22, -8 },
        { 35, 5 }, { 25, 15 }, { 12, 25 }, { 0, 20 }, { -15, 28 },
        { -28, 18 }, { -35, 2 }, { -25, -12 }, { -32, -20 },
        { -18, -25 }, { 0, -30 }
    };

    std::vector<viper::vec2> heart_shape = {
        { 0, 25 }, { 8, 18 }, { 15, 10 }, { 20, 2 }, { 22, -6 },
        { 18, -12 }, { 12, -15 }, { 5, -16 }, { 0, -12 }, { -5, -16 },
        { -12, -15 }, { -18, -12 }, { -22, -6 }, { -20, 2 },
        { -15, 10 }, { -8, 18 }, { 0, 25 }
    };

    std::vector<viper::vec2> bulletShape = {
        { -2, -5 }, { 2, -5 }, { 2, 5 }, { -2, 5 }, { -2, -5 }
    };

    m_bulletModel = std::make_shared<viper::Model>(bulletShape, viper::vec3{ 1, 1, 1 });
    std::shared_ptr<viper::Model> player = std::make_shared<viper::Model>(points, viper::vec3{ 1, 1, 1 });

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

    viper::Transform playerTransform{ viper::vec2{640, 512}, 0, 20 };
    m_scene->AddActor(std::make_unique<Player>(playerTransform, player));

    for (int i = 0; i < 3; i++) {
        int modelIndex = viper::random::getInt(0, static_cast<int>(heartModels.size()) - 1);
        viper::Transform heartTransform{ viper::vec2{ static_cast<float>(1100 + i * 50), 30 } };
        auto health = std::make_unique<Health>(heartTransform, heartModels[modelIndex]);
        m_hearts.push_back(health.get());
        m_scene->AddActor(std::move(health));
    }

    for (int i = 0; i < 10; ++i) {
        int modelIndex = viper::random::getInt(0, static_cast<int>(asteroidModels.size()) - 1);
        viper::Transform transform{
            { viper::random::getReal() * 1024, viper::random::getReal() * 768 },
            viper::random::getReal(0.0f, 6.28f),
            viper::random::getReal(10.0f, 30.0f)
        };
        m_scene->AddActor(std::make_unique<Enemy>(transform, asteroidModels[modelIndex]));
    }

    return true;
}

void SpaceGame::Update() {
    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());

    auto player = m_scene->GetActor<Player>();
    auto enemies = m_scene->GetActors<Enemy>();
    int healthLeft = player->GetHealth();

    for (int i = 0; i < m_hearts.size(); i++) {
        if (i >= healthLeft) {
            m_hearts[i]->GetTransform().position = { -1000.0f, -1000.0f };
        }
    }

    static float fireCooldown = 0.0f;
    fireCooldown -= viper::GetEngine().GetTime().GetDeltaTime();

    if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && fireCooldown <= 0.0f) {
        fireCooldown = 0.3f;
        std::cout << "🚀 Pew pew!\n";
        std::vector<std::unique_ptr<viper::Actor>> newBullets;
        player->Shoot(newBullets, m_bulletModel);
        for (auto& bullet : newBullets) m_scene->AddActor(std::move(bullet));
    }

    for (auto& enemy : enemies) {
        if (!enemy) continue;

        if (viper::Collisions::CheckCollision(player->GetTransform(), player->GetRadius(),
            enemy->GetTransform(), enemy->GetRadius())) {
            player->SetHealth(player->GetHealth() - 1);
            enemy->SetHealth(0);
            std::cout << "💥 Collision! Player HP: " << player->GetHealth() << "\n";
        }

        auto bullets = m_scene->GetActors<Bullet>();
        for (auto& bullet : bullets) {
            if (!bullet) continue;
            if (viper::Collisions::CheckCollision(enemy->GetTransform(), enemy->GetRadius(),
                bullet->GetTransform(), bullet->GetRadius())) {
                enemy->SetHealth(enemy->GetHealth() - 1);
                bullet->SetHealth(0);
                if (bullet->GetHealth() <= 0)
                    bullet->GetTransform().position = { -100.0f, -100.0f };
            }
        }

        if (enemy->GetHealth() <= 0)
            enemy->GetTransform().position = { -100.0f, -100.0f };
    }
}

void SpaceGame::Draw() {
    if (m_scene) m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown() {
    // m_scene.reset();
}
