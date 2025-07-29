#pragma once
#include "Source/Game/Actor.h"
#include <memory>

class Health : public viper::Actor {
public:
	Health() = default;

	Health(const viper::Transform& transform, std::shared_ptr<viper::Model> health)
		: Actor{ transform, health } {
	}

	void Update(float dt) override;

private:
};
