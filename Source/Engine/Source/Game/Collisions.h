#pragma
#include "../../Math/Transform.h"  
#include "../Render/Renderer.h"  
#include <memory>
#include "../../Render/Model.h"


namespace viper {
    class Collisions {
    private:
        Collisions() = default;

    public:
        static bool CheckCollision(const Transform& transform1, float radius1,
            const Transform& transform2, float radius2);
    };
}
