#pragma once
#include "../Engine/Source/Game/Actor.h"

class Bullet : public viper::Actor {
public:
    Bullet(const viper::Transform& transform, std::shared_ptr<viper::Model> model, const viper::vec2& velocity)
        : Actor(transform, model), m_velocity(velocity) {
    }

    void Update(float dt) override {
        m_transform.position += m_velocity * dt;

        // Simple kill if off screen
        if (m_transform.position.x < 0 || m_transform.position.x > 1280 ||
            m_transform.position.y < 0 || m_transform.position.y > 1024) {
            m_health = 0;
        }
    }

    float GetRadius() const {
        return m_radius;
	}

    void SetHealth(int health) {
        m_health = health;
	}

    int GetHealth() const {
        return m_health;
    }

private:
    viper::vec2 m_velocity;
	int m_health = 1;
	float m_radius = 10.0f;
};
