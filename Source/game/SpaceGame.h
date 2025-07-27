#pragma once
#include "../Engine/Game.h"

class SpaceGame : public viper::Game {
public:
	SpaceGame() = default;
	bool Initialize() override;
	void Update() override;
	void Shutdown() override;
	void Draw() override;
private:
};