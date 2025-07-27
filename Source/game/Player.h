#pragma once
#include "Source/Game/Actor.h"
#include <memory>

class Player : public viper::Actor {
public:
	Player() = default;

	Player(const viper::Transform& transform, std::shared_ptr<viper::Model> player)
		: Actor{ transform, player } {
	}

	void Update(float dt) override;

private:
};
