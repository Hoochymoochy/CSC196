#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>  

#include "Source/Core/Random.h"
#include "Source/Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"

#include "Render/Renderer.h"
#include "Source/Render/Renderer.h"
#include "Source/Game/Scene.h"
#include "Source/Game/Actor.h"
#include "../Engine/Render/Model.h"
#include "../Engine/Engine.h"
#include "../Engine/Render/Font.h"
#include "../Engine/Render/Text.h"

#include "../game/Player.h"
#include "../game/SpaceGame.h"

#include "../Engine/Core/File.h"
using namespace viper;


int main(int argc, char* argv[]) {

    // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << viper::file::GetCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    viper::file::SetCurrentDirectory("Assets");
    std::cout << "New directory: " << viper::file::GetCurrentDirectory() << "\n\n";

    // Get filenames in the current directory
    std::cout << "Files in Directory:\n";
    auto filenames = viper::file::GetFilesInDirectory(viper::file::GetCurrentDirectory());
    for (const auto& filename : filenames) {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // Get filename (filename.extension) only
    if (!filenames.empty()) {
        std::cout << "Path Analysis:\n";
        std::string filename = viper::file::GetFilename(filenames[0]);
        std::cout << "Filename only: " << filename << "\n";

        // Get extension only
        std::string ext = viper::file::GetExtension(filenames[0]);
        std::cout << "Extension: " << ext << "\n\n";
    }

    // Read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    bool success = viper::file::ReadTextFile("test.txt", str);
    if (success) {
        std::cout << "Contents of test.txt:\n";
        std::cout << str << "\n";
    }
    else {
        std::cout << "Failed to read test.txt\n";
    }



    std::cout << "Integer Functions:\n";
    std::cout << "getInt(): " << viper::random::getInt() << "\n";
    std::cout << "getInt(): " << viper::random::getInt() << "\n";
    std::cout << "getInt(10): " << viper::random::getInt(10) << "\n";
    std::cout << "getInt(10): " << viper::random::getInt(10) << "\n";
    std::cout << "getInt(5, 15): " << viper::random::getInt(5, 15) << "\n";
    std::cout << "getInt(5, 15): " << viper::random::getInt(5, 15) << "\n";
    std::cout << "getInt(-10, 10): " << viper::random::getInt(-10, 10) << "\n\n";

    // Test getReal() variants with float
    std::cout << "Float Functions:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "getReal<float>(): " << viper::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(): " << viper::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(5.0f): " << viper::random::getReal<float>(5.0f) << "\n";
    std::cout << "getReal<float>(2.5f, 7.5f): " << viper::random::getReal<float>(2.5f, 7.5f) << "\n";
    std::cout << "getReal<float>(-1.0f, 1.0f): " << viper::random::getReal<float>(-1.0f, 1.0f) << "\n\n";

    // Test getReal() variants with double
    std::cout << "Double Functions:\n";
    std::cout << std::setprecision(10);
    std::cout << "getReal<double>(): " << viper::random::getReal<double>() << "\n";
    std::cout << "getReal<double>(100.0): " << viper::random::getReal<double>(100.0) << "\n";
    std::cout << "getReal<double>(0.0, 2.0): " << viper::random::getReal<double>(0.0, 2.0) << "\n\n";

    // Test getBool()
    std::cout << "Boolean Functions:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "getBool(): " << std::boolalpha << viper::random::getBool() << "\n";
    }
    std::cout << "\n";



    // Initialize the engine
    viper::GetEngine().Initialize();

    // Initialize the game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    Font* font = new Font();
    bool fontLoaded = font->Load("os.ttf", 20);
    //if (!fontLoaded) {
    //    std::cerr << "Could not load font. Aborting.\n";
    //    return -1;
    //}


    Text* text = new Text(font);
    text->Create(GetEngine().GetRenderer(), "Hello World", vec3{5, 5, 5});

    SDL_Event e;
    bool quit = false;

    std::vector<viper::vec2> stars;


    for (int i = 0; i < 100; ++i) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        viper::GetEngine().Update();
        game->Update();

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        game->Draw();
        text->Draw(GetEngine().GetRenderer(), 40.0f, 40.0f);


        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
            star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getReal(256.0f), (uint8_t)viper::random::getReal(256.0f), (uint8_t)viper::random::getReal(256.0f));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);

        }

        viper::GetEngine().GetRenderer().Present();

    } 
    viper::GetEngine().Shutdown();
    return 0;
}