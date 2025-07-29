#pragma once

#include "../Engine/Source/Game/Actor.h"
#include "../Engine/Math/Vector2.h"
#include "../Engine/Math/Transform.h"
#include "../Engine/Render/Model.h"
#include <memory>

class Bullet : public viper::Actor {
public:
    Bullet(const viper::Transform& transform, std::shared_ptr<viper::Model> model, float speed = 600.0f);

    void Update(float dt) override;

private:
    float m_speed = 600.0f;
};
