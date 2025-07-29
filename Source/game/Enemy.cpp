#include "Enemy.h"
#include "../Engine/Engine.h"

void Enemy::Update(float dt) {
    m_transform.position += m_velocity * dt;

    // Bounce off edges (basic world bounds)
    if (m_transform.position.x < 0 || m_transform.position.x > 1280) m_velocity.x *= -1;
    if (m_transform.position.y < 0 || m_transform.position.y > 1024) m_velocity.y *= -1;
}
