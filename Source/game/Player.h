#pragma once
#include "Source/Game/Actor.h"
#include "./Health.h"
#include <memory>

class Player : public viper::Actor {
public:
	Player() = default;

	Player(const viper::Transform& transform, std::shared_ptr<viper::Model> player)
		: Actor{ transform, player } {
	}

	void Update(float dt) override;
	float GetRadius() const { return 10.0f; }

	int GetHealth() const { return m_health; }
	void SetHealth(int health) { m_health = health; }
	void TakeDamage(int amount) { m_health -= amount; }


private:
	int m_health = 3;
};
