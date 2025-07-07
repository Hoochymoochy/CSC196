#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 100; ++i) {
            float x1 = static_cast<float>(rand() % 1280);
            float y1 = static_cast<float>(rand() % 1024);
            float x2 = static_cast<float>(rand() % 1280);
            float y2 = static_cast<float>(rand() % 1024);

            Uint8 r = rand() % 256;
            Uint8 g = rand() % 256;
            Uint8 b = rand() % 256;

			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderLine(renderer, x1, y1, x2, y2);
			SDL_RenderPoint(renderer, x1, y1);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}