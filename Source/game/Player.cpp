#include "Player.h"
#include "../Engine/Engine.h"
#include "../Engine/Input/InputSystem.h"

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