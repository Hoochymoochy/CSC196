#include "Player.h"
#include "../Engine/Engine.h"
#include "../Engine/Input/InputSystem.h"
#include "Bullet.h"

void Player::Update(float dt) {
    float speeds = 200;

    viper::vec2 direction{ 0, 0 };
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = +1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = +1;

    if (direction.Length() > 0) {
        direction = direction.Normalized();
		m_transform.position += (direction * speeds) * dt;
    }
}

void Player::Shoot(std::vector<std::unique_ptr<viper::Actor>>& bullets, std::shared_ptr<viper::Model> bulletModel) {
    viper::vec2 direction = { std::cos(m_transform.rotation), std::sin(m_transform.rotation) };
    viper::vec2 velocity = direction * 600.0f;

    viper::Transform bulletTransform = m_transform;
    bulletTransform.scale = 5;
    bulletTransform.position += direction * 30.0f;

    bullets.push_back(std::make_unique<Bullet>(bulletTransform, bulletModel, velocity));
}

