#include "Bullet.h"
#include "../Engine/Engine.h"

Bullet::Bullet(const viper::Transform& transform, std::shared_ptr<viper::Model> model, float speed)
    : Actor(transform, model), m_speed(speed)
{
}

void Bullet::Update(float dt) {
    // Move forward in facing direction
    viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * dt;

    // Optional: destroy bullet if off screen (clean up)
    auto& renderer = viper::GetEngine().GetRenderer();
    if (m_transform.position.x < 0 || m_transform.position.x > renderer.GetWidth() ||
        m_transform.position.y < 0 || m_transform.position.y > renderer.GetHeight()) {
        m_destroyed = true;
    }
}
