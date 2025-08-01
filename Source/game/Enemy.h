#pragma once
#include "Source/Game/Actor.h"
#include "../Engine/Core/Random.h"

class Enemy : public viper::Actor {
public:
	Enemy() = default;

	Enemy(const viper::Transform& transform, std::shared_ptr<viper::Model> model)
		: Actor{ transform, model } {
		m_velocity = viper::vec2{
			viper::random::getReal(-1.0f, 1.0f),
			viper::random::getReal(-1.0f, 1.0f)
		} *100.0f;
	}

	void Update(float dt) override;
	float GetRadius() const { return m_transform.scale; }

	int GetHealth() const { return m_health; }
	void SetHealth(int health) { m_health = health; }

private:
	viper::vec2 m_velocity;
	int m_health = 1;
};
