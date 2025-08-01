#pragma once
#include "../Engine/Game.h"
#include "./Health.h"
class SpaceGame : public viper::Game {
public:
	SpaceGame() = default;
	bool Initialize() override;
	void Update() override;
	void Shutdown() override;
	void Draw() override;
private:
	std::vector<Health*> m_hearts;
	std::shared_ptr<viper::Model> m_bulletModel;
};