#pragma once
#include "Source/Game/Actor.h"

class Enemy : public viper::Actor {
	Enemy() = default;
	Enemy(const viper::Transform& transform, std::shared_ptr<viper::Model> player) :
		Actor{ transform, player }
	{
	}

	void Update(float dt) override;
private:
};