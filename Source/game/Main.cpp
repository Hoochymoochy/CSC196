#include "Render/Renderer.h"
#include "Math/Vector2.h"
#include "Source/Core/Time.h"
#include "Source/Core/Random.h"
#include "Source/Input/InputSystem.h"
#include "Math/Math.h"
#include <iostream>
#include <vector>


int main(int argc, char* argv[]) {
    // initialize engine system
	Renderer renderer;
	renderer.Initialized();
	renderer.CreateWindow("Viper engine", 1280, 1024);
	viper::Time time;
    viper::InputSystem input;
    input.Initialize();

    SDL_Event e;
    bool quit = false;

	std::vector<viper::vec2> stars;
    std::vector<viper::vec2> points;

    for (int i = 0; i < 100; ++i) {
		stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
	}

    while (!quit) {
		time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        input.Update();



    renderer.SetColor(0, 0, 0); 
    renderer.Clear();

    viper::vec2 speed{ 0.1f, 0.0f };
    for (viper::vec2& star : stars) {
        star += speed;
        if (star[0] > 1280) star[0] = 0;
        if (star[0] < 0) star[0] = 1280;

        renderer.SetColor(
            viper::random::getRandomInt(256),
            viper::random::getRandomInt(256),
            viper::random::getRandomInt(256)
        );
        renderer.DrawPoint(star.x, star.y);
    }        if (input.GetKeyReleased(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::LEFT)) {
            viper::vec2 position = input.GetMousePosition();

            if (points.empty()) {
                points.push_back(position);
            }
            else if ((position - points.back()).Length() > 10) {
                points.push_back(position);
            }
        }

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        viper::vec2 mouse = input.GetMousePosition();
        std::cout << mouse.x << " " << mouse.y << "\n";

		renderer.Present();
    }
	renderer.Shutdown();

    return 0;
}